#include "modbusdevice.h"

ModbusDevice::ModbusDevice(std::string deviceName , TcpParm *tcpParm, RtuParm *rtuParm , int slaveId, ModbusBlock *block)
{
    this->slaveId = slaveId;    
    this->connection = new ModbusTCP2RTU(tcpParm,rtuParm,this->slaveId,5);
    //this->addModbusBlock(block);
    this->deviceName = deviceName;
    this->connection->setDebug(true);
}

void ModbusDevice::startDevice()
{
    this->connection->startThread();
    this->Running = true;
}

void ModbusDevice::stopDevice()
{
    this->connection->killThread();
    this->Running = false;
}

int ModbusDevice::getDeviceSlaveId()
{
    return this->slaveId;
}

std::string ModbusDevice::getDeviceName()
{
    return this->deviceName;
}

bool ModbusDevice::isRunning()
{
    return this->Running;
}

void ModbusDevice::addModbusBlock(ModbusBlock *block)
{
    this->connection->addBlock(block);
}



