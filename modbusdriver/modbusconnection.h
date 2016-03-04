#ifndef MODBUSCONNECTION_H
#define MODBUSCONNECTION_H

#include <modbus/modbus.h>
#include "core/parm.hpp"

#include <string>

/**
 * @brief The ModbusConnection class
 * 处理与modbus连接相关，连接tcp rtu
 */
class ModbusConnection
{
private:
    int responseTimeout;
    int connectionTimeout;
    bool connected;
    modbus_t* context;
    void setContext(TcpParm *tcpParm);
    void setContext(RtuParm *rtuParm);
public:
    ModbusConnection(TcpParm *tcpParm);
    ModbusConnection(RtuParm *rtuParm);
    void connect() throw (std::string);
    void disconnect();
    void flush();
    bool isConnected();
    void setResponseTimeout(int responseTimeout);
    //void setConnectionTimeout(int connectionTimeout);
    void setSlaveId(int slaveId);

    modbus_t* getContext();
};


#endif // MODBUSCONNECTION_H
