#ifndef MODBUSDRIVER_H
#define MODBUSDRIVER_H

/**
 * @brief The ModbusDriver class
 * 管理所有modbusdevice与网络服务器的连接，停止，以及数据传输
 */

#include <map>
#include "modbusdevice.h"

class ModbusDriver
{
private:
    std::map<std::string,ModbusDevice*> devices;
    int nbDevice;
public:
    ModbusDriver();
    void addModbusDevice(std::string name,ModbusDevice *device);
    ModbusDevice *getDevice(std::string name);
    void deleteDevice(std::string deviceName);
    void startModbusDriver();
    void stopModbusDriver();
    bool isRunning(std::string name);
    bool isAllRunning();
    //bool isConnected(std::string name);
};

#endif // MODBUSDRIVER_H
