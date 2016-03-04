#include "modbusblock.h"

ModbusBlock::ModbusBlock()
{
    //
}

ModbusBlock::ModbusBlock(int nbCoils, int addrCoils, int nbInputCoils, int addrInputCoils,
                         int nbRegister, int addrRegister, int nbInputRegister, int addrInputRegister)
{
    this->modbusMapping = modbus_mapping_new(nbCoils + addrCoils,nbInputCoils + addrInputCoils,nbRegister + addrRegister,
                                             nbInputRegister + addrInputRegister);
}

ModbusBlock::~ModbusBlock()
{
    modbus_mapping_free(this->modbusMapping);
}

modbus_mapping_t *ModbusBlock::getMapping()
{
    return this->modbusMapping;
}

void ModbusBlock::addCoils(Coils *coils)
{
    //std::pair p = pair(coils->name,coils->address);
    this->coilsMap.insert(std::map<std::string,int>::value_type(coils->name,coils->address));
    this->nbCoils = this->coilsMap.size();
}

uint8_t ModbusBlock::getCoilsValue(Coils *coils)
{
    return this->modbusMapping->tab_bits[coils->address];
}

void ModbusBlock::addInputCoils(InputCoils *inputCoils)
{
    this->inputCoilsMap.insert(std::map<std::string,int>::value_type(inputCoils->name,inputCoils->address));
    this->nbInputCoils = this->inputCoilsMap.size();
}

uint8_t ModbusBlock::getInputCoils(InputCoils *inputCoils)
{
    return this->modbusMapping->tab_input_bits[inputCoils->address];
}

void ModbusBlock::addRegister(Register *regi)
{
    this->registerMap.insert(std::map<std::string,int>::value_type(regi->name,regi->address));
    this->nbRegister = this->registerMap.size();
}

uint16_t ModbusBlock::getRegister(Register *regi)
{
    return this->modbusMapping->tab_registers[regi->address];
}

void ModbusBlock::addInputRegister(InputRegister *inputRegister)
{
    this->inputRegisterMap.insert(std::map<std::string,int>::value_type(inputRegister->name,inputRegister->address));
    this->nbInputRegister = this->inputRegisterMap.size();
}

uint16_t ModbusBlock::getInputRegister(InputRegister *inputRegister)
{
    return this->modbusMapping->tab_input_registers[inputRegister->address];
}

