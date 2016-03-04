#include "modbustcp2rtu.h"
#include <sstream>
#include <stdio.h>
#include <errno.h>
#include <memory.h>
ModbusTCP2RTU::ModbusTCP2RTU(TcpParm *tcpParm, RtuParm *rtuParm,int slaveId,int timeOut)
{
    this->tcpConnection = new ModbusConnection(tcpParm);
    this->rtuConnection = new ModbusConnection(rtuParm);
    this->tcpConnection->setSlaveId(slaveId);
    this->rtuConnection->setSlaveId(slaveId);
    this->tcpConnection->setResponseTimeout(timeOut);
    this->rtuConnection->setResponseTimeout(timeOut);
    this->mapping = modbus_mapping_new(100,100,100,100);
    initMapping(100,100,100,100);
}

ModbusTCP2RTU::~ModbusTCP2RTU()
{
    this->rtuConnection->disconnect();
    this->connected = false;
    modbus_mapping_free(mapping);
}

void ModbusTCP2RTU::addBlock(ModbusBlock *block)
{
    this->block = block;
}

bool ModbusTCP2RTU::isConnected()
{
    return this->connected;
}

void ModbusTCP2RTU::run()
{
    this->isStopped = false;
    listen(10);
}

void ModbusTCP2RTU::halt()
{
    this->isStopped = true;
    this->rtuConnection->disconnect();
    this->connected = false;
}

void ModbusTCP2RTU::initMapping(int nb_bit, int nb_input_bit, int nb_register, int nb_input_register)
{
    tab_bit = (uint8_t *)malloc(nb_bit*sizeof(uint8_t));
    memset(tab_bit,0,nb_bit*sizeof(uint8_t));

    tab_input_bit = (uint8_t *)malloc(nb_input_bit*sizeof(uint8_t));
    memset(tab_input_bit,0,nb_input_bit*sizeof(uint8_t));

    tab_register = (uint16_t *)malloc(nb_register*sizeof(uint16_t));
    memset(tab_register,0,nb_register*sizeof(uint16_t));

    tab_input_register = (uint16_t *)malloc(nb_input_register*sizeof(uint16_t));
    memset(tab_input_register,0,nb_input_register*sizeof(uint16_t));
}

void ModbusTCP2RTU::updateMapping()
{
    this->mapping->tab_bits = tab_bit;
    this->mapping->tab_input_bits = tab_input_bit;
    this->mapping->tab_input_registers = tab_input_register;
    this->mapping->tab_registers = tab_register;
}

int ModbusTCP2RTU::readBit(int address, int nb)
{
    return modbus_read_bits(this->rtuConnection->getContext(),address,nb,this->tab_bit);
}

int ModbusTCP2RTU::readInputBit(int address, int nb)
{
    return modbus_read_input_bits(this->rtuConnection->getContext(),address,nb,this->tab_input_bit);
}

int ModbusTCP2RTU::readRegister(int address, int nb)
{
    return modbus_read_registers(this->rtuConnection->getContext(),address,nb,this->tab_register);
}

int ModbusTCP2RTU::readInputRegister(int address, int nb)
{

    return modbus_read_input_registers(this->rtuConnection->getContext(),address,nb,this->tab_input_register);
}

int ModbusTCP2RTU::writeBit(int address, int nb)
{
    int status = modbus_write_bit(this->rtuConnection->getContext(),address,nb);
    if( status!= -1)
    {
        this->block->getMapping()->tab_bits[address] = nb;
    }
    return status;
}

int ModbusTCP2RTU::writeBits(int address, int nb ,const uint8_t *data)
{
    int status = modbus_write_bits(this->rtuConnection->getContext(),address,nb,data);
    if( status!= -1)
    {
        modbus_set_bits_from_bytes(this->block->getMapping()->tab_bits,address,nb,data);
    }
    return status;
}

int ModbusTCP2RTU::writeRegister(int address, int nb)
{
    int status = modbus_write_register(this->rtuConnection->getContext(),address,nb);
    if( status!= -1)
    {
        this->block->getMapping()->tab_registers[address] = nb;
    }
    return status;
}

int ModbusTCP2RTU::writeRegisters(uint8_t *req, int offset, int address, int nb)
{
    int i,j;
    for(i = address,j = 6;i<address + nb;i++ ,j +=2 )
    {
        this->block->getMapping()->tab_registers[i] = (req[offset + j] << 8) + req[offset + j + 1];
    }
    int status = modbus_write_registers(this->rtuConnection->getContext(),address,nb,&this->block->getMapping()->tab_registers[address]);
    return status;
}

int ModbusTCP2RTU::doRtuReadWrite(uint8_t *req, int offset)
{
    int function;
    uint16_t address;
    int nb;
    function = req[offset];
    LOGD("function code:"<<function);
    address = (req[offset + 1] << 8) + req[offset + 2];
    LOGD("address:"<<address);
    nb = (req[offset + 3] << 8) + req[offset + 4];
    LOGD("nb:"<<nb);
    if(function == _FC_READ_COILS || function == _FC_READ_DISCRETE_INPUTS || function == _FC_READ_HOLDING_REGISTERS || function == _FC_READ_INPUT_REGISTERS)
    {
        return rtuRead(function,address,nb);
    }else if(function == _FC_WRITE_MULTIPLE_COILS || function == _FC_WRITE_MULTIPLE_REGISTERS || function == _FC_WRITE_SINGLE_COIL || _FC_WRITE_SINGLE_REGISTER)
    {
        //WRITE TO RTU
        return rtuWrite(req,offset,function,address,nb);
    }
}


int ModbusTCP2RTU::rtuRead(int function , uint16_t address, int nb)
{
    int status;
    switch(function)
    {
    case _FC_READ_COILS:{
        //read coils
        status = readBit(address,nb);
    }
        break;
    case _FC_READ_DISCRETE_INPUTS:{
        //
        status = readInputBit(address,nb);
    }
        break;
    case _FC_READ_HOLDING_REGISTERS:{
        //
        status = readRegister(address,nb);
    }
        break;
    case _FC_READ_INPUT_REGISTERS:{
        //
        status = readInputRegister(address,nb);
    }
        break;
    }
    return status;
}

int ModbusTCP2RTU::rtuWrite(uint8_t *req, int offset, int function, uint16_t address, int nb)
{
    int status;
    switch(function)
    {
    case _FC_WRITE_SINGLE_COIL:{
        //write signal coil
        status = writeBit(address,nb);
    }
        break;
    case _FC_WRITE_SINGLE_REGISTER:{
        //write signal register
        status = writeRegister(address,nb);
    }
        break;
    case _FC_WRITE_MULTIPLE_COILS:{
        //write multiple coils
        uint8_t *data = &req[offset + 6];
        status = writeBits(address,nb,data);
    }
        break;
    case _FC_WRITE_MULTIPLE_REGISTERS:{
        //write multiple registers
        status = writeRegisters(req,offset,address,nb);
    }
        break;
    }
    return status;
}

int ModbusTCP2RTU::process_tcp_request(int offset)
{
    int query_size;
    uint8_t *req;
    req = (uint8_t *)malloc(MODBUS_TCP_MAX_ADU_LENGTH);

    if(req == NULL)
    {
        LOGE(stderr<<"process tcp request:Filed to allocate memory.\n");
        return -2;
    }

    for(;;)
    {
        //LOGD("MODBUS RECEIVEING...");
        query_size = modbus_receive(this->tcpConnection->getContext(),req);
        if(query_size != -1)
        {
            //blockMutex.lock();

            //LOGD("do rtu read and write");
            query_size = doRtuReadWrite(req,offset);
            //blockMutex.unlock();
            //LOGD("doRtuReadWrite query_size:"<<query_size);
            if(query_size>0)
            {
                //LOGD("update mapping");
                updateMapping();
                //LOGD("modbus reply");
                modbus_reply(this->tcpConnection->getContext(),req,query_size,this->mapping);
            }
            else
            {
                fprintf(stderr,"RUT Slave errno:%s\n",modbus_strerror(errno));
                modbus_reply_exception(this->tcpConnection->getContext(),req,errno);
            }
        }
    }
    free(req);
    return query_size;
}


void ModbusTCP2RTU::listen(int connectionNb)
{
    try
    {
        this->rtuConnection->connect();
    }
    catch(std::string)
    {
        LOGE("Connection to rtu failed");
    }

    int offset = modbus_get_header_length(this->tcpConnection->getContext());
    LOGD("offset:"<<offset);
    LOGI("Listening.....");
    int tcp_socket = modbus_tcp_listen(this->tcpConnection->getContext(),connectionNb);
    if(tcp_socket == -1)
    {
        LOGE("Binding to address FAILED");
    }
    else
    {
        LOGI("Binding SUCCESS");
        while(!isStopped)
        {
            LOGI("Waiting for TCP connection...:");
            int rc = modbus_tcp_accept(this->tcpConnection->getContext(),&tcp_socket);
            if(rc == -1)
            {
                fprintf(stderr, "Modbus TCP error: %s\n",modbus_strerror(errno));
                continue;
            }
            /*
             * process tcp request
            */
            switch(fork())
            {
            case 0:
                rc = process_tcp_request(offset);
                close(tcp_socket);
                LOGFMTD("Server child PID %d died",getpid());
                break;
            case -1:
                LOGE("Error during fork\n");
            default:
                break;
            }
        }
    }
}

void ModbusTCP2RTU::setDebug(bool isDebug)
{
    if(isDebug)
    {
        modbus_set_debug(this->tcpConnection->getContext(),TRUE);
        modbus_set_debug(this->rtuConnection->getContext(),TRUE);
    }
    else
    {
        modbus_set_debug(this->tcpConnection->getContext(),FALSE);
        modbus_set_debug(this->rtuConnection->getContext(),FALSE);
    }
}
