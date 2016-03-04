#include "modbusconnection.h"

void ModbusConnection::connect() throw (std::string)
{
    if(modbus_connect(this->context) == -1)
    {
        throw std::string("connection_host_failed");
    }
    this->connected = true;
}

void ModbusConnection::disconnect()
{
    modbus_close(this->context);
    this->connected = false;
}

void ModbusConnection::flush()
{
    modbus_flush(this->context);
}

bool ModbusConnection::isConnected()
{
    return this->connected;
}

void ModbusConnection::setResponseTimeout(int responseTimeout)
{
    modbus_set_response_timeout(this->context,responseTimeout/1000,(responseTimeout%1000)*1000);
}

void ModbusConnection::setSlaveId(int slaveId)
{
    modbus_set_slave(this->context,slaveId);
}

void ModbusConnection::setContext(TcpParm *tcpParm)
{
    this->context = modbus_new_tcp(tcpParm->ip.c_str(),tcpParm->port);
}

void ModbusConnection::setContext(RtuParm *rtuParm)
{
    this->context = modbus_new_rtu(rtuParm->device,rtuParm->baud,rtuParm->parity,rtuParm->data_bit,rtuParm->stop_bit);
}

ModbusConnection::ModbusConnection(TcpParm *tcpParm)
{
    setContext(tcpParm);
}

ModbusConnection::ModbusConnection(RtuParm *rtuParm)
{
    setContext(rtuParm);
}

modbus_t *ModbusConnection::getContext()
{
    return this->context;
}


