#ifndef MODBUSTCP2RTU_H
#define MODBUSTCP2RTU_H

#include "modbusconnection.h"
#include <modbus/modbus.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include "core/thread.hpp"
#include "core/parm.hpp"
#include "core/type.hpp"
#include "modbusblock.h"
#include <mutex>
#include "core/log4z/log4z.h"

/* Function codes */
#define _FC_READ_COILS 0x01
#define _FC_READ_DISCRETE_INPUTS 0x02
#define _FC_READ_HOLDING_REGISTERS 0x03
#define _FC_READ_INPUT_REGISTERS 0x04
#define _FC_WRITE_SINGLE_COIL 0x05
#define _FC_WRITE_SINGLE_REGISTER 0x06
#define _FC_READ_EXCEPTION_STATUS 0x07
#define _FC_WRITE_MULTIPLE_COILS 0x0F
#define _FC_WRITE_MULTIPLE_REGISTERS 0x10
#define _FC_REPORT_SLAVE_ID 0x11
#define _FC_READ_AND_WRITE_REGISTERS 0x17

/**
 * @brief The ModbusTCP2RTU class
 * 将每一个modbus设备与服务器的连接看成是一个modbustcp2rtu连接
 *
 */
class ModbusTCP2RTU : public Thread
{
private:
    TcpParm *tcpParm;
    RtuParm *rtuParm;
    //connection(tcp and rtu)
    ModbusConnection *tcpConnection;
    ModbusConnection *rtuConnection;
    bool connected;
    //Register Mapping
    ModbusBlock *block;         //store registers mapping;
    modbus_mapping_t *mapping;
    uint8_t *tab_bit;
    uint8_t *tab_input_bit;
    uint16_t * tab_register;
    uint16_t *tab_input_register;
    void initMapping(int nb_bit,int nb_input_bit,int nb_register,int nb_input_register);
    void updateMapping();
    //thread
    bool isStopped;
    std::mutex blockMutex;      //lock the ModbusBlock
    //read from rtu
    int readBit(int address,int nb);
    int readInputBit(int address,int nb);
    int readRegister(int address,int nb);
    int readInputRegister(int address,int nb);
    //write to rtu
    int writeBit(int address,int nb);
    int writeBits(int address,int nb,const uint8_t *data);
    int writeRegister(int address,int nb);
    int writeRegisters(uint8_t *req,int offset,int address,int nb);

    //listen the request from host and response it
    void listen(int connectionNb);
    //
    int rtuRead(int function , uint16_t address, int nb);
    int rtuWrite(uint8_t *req,int offset,int function ,uint16_t address, int nb);
    //
    //void doTCPResponse();
    //void doRTURequest();
    int process_tcp_request(int offset);
    int doRtuReadWrite(uint8_t *req,int offset);

public:  
    ModbusTCP2RTU(TcpParm *tcpParm,RtuParm *rtuParm,int slaveId,int timeOut);
    ~ModbusTCP2RTU();
    void addBlock(ModbusBlock *block);
    bool isConnected();
    //thread function
    void run();
    void halt();
    void setDebug(bool isDebug);

};

#endif // MODBUSTCP2RTU_H
