#ifndef MODBUSDEVICE_H
#define MODBUSDEVICE_H

#include "modbusdriver/modbustcp2rtu.h"
#include "modbusdriver/modbusblock.h"
#include "core/parm.hpp"


/**
 * @brief The ModbusDevice class
 * 每一个下位设备看成一个modbustcp2rtuconnection，modbusdevice管理这些连接,
 * and ModbusBlock
 */
class ModbusDevice
{
private:
    std::string deviceName;
    ModbusTCP2RTU *connection;
    //ModbusBlock *block;
    int slaveId;
    void addModbusBlock(ModbusBlock* block);
    bool Running;
public:
    ModbusDevice(std::string deviceName,TcpParm *tcpParm,RtuParm *rtuParm,int slaveId,ModbusBlock *block);
    void startDevice();
    void stopDevice();
    int getDeviceSlaveId();
    std::string getDeviceName();
    bool isRunning();
    //bool isConnected();
};

#endif // MODBUSDEVICE_H
