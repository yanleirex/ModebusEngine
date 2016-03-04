#include "modbusdriver.h"

ModbusDriver::ModbusDriver()
{

}

void ModbusDriver::addModbusDevice(std::string name, ModbusDevice *device)
{
   //this->deviceList.insert(name,device);
    this->devices[name] = device;
   //this->devices.insert(std::map<std::string,ModbusDevice*>::value_type(name,device));
    this->nbDevice = this->devices.size();
}

ModbusDevice *ModbusDriver::getDevice(std::string name)
{
    return this->devices[name];
}

void ModbusDriver::deleteDevice(std::string deviceName)
{
    this->devices.erase(deviceName);
}

void ModbusDriver::startModbusDriver()
{
    //start all devices
    std::map<std::string,ModbusDevice*>::iterator _it = this->devices.begin();
    for(;_it!=this->devices.end();_it++)
    {
        std::pair<std::string,ModbusDevice*> _p = *_it;
        ModbusDevice* _device = _p.second;
        _device->startDevice();
    }
}

void ModbusDriver::stopModbusDriver()
{
    //stop all device
    std::map<std::string,ModbusDevice*>::iterator _it = this->devices.begin();
    for(;_it!=this->devices.end();_it++)
    {
        std::pair<std::string,ModbusDevice*> _p = *_it;
        ModbusDevice* _device = _p.second;
        _device->stopDevice();
    }
}

bool ModbusDriver::isRunning(std::string name)
{
    ModbusDevice* _device = this->devices[name];
    return _device->isRunning();
}

bool ModbusDriver::isAllRunning()
{
    std::map<std::string,ModbusDevice*>::iterator _it = this->devices.begin();
    for(;_it!=this->devices.end();_it++)
    {
        std::pair<std::string,ModbusDevice*> _p = *_it;
        ModbusDevice* _device = _p.second;
        if(!_device->isRunning())
        {
            return false;
            break;
        }
    }
    return true;
}

//bool ModbusDriver::isConnected(std::string name)
//{
//    ModbusDevice* _device = this->devices[name];
//    return _device->isConnected();
//}


