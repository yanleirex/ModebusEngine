#ifndef MODBUSBLOCK_H
#define MODBUSBLOCK_H

#include <modbus/modbus.h>
#include <string>
#include <map>
/**
 * @brief The InputCoils class
 * 抽象出一个InputCoils
 */
class InputCoils
{
private:
    bool state;
public:
    std::string name;
    int address;
    InputCoils(std::string name,int address)
    {
        this->name = name;
        this->address = address;
    }
    bool getState()
    {
        return this->state;
    }

    ~InputCoils();
};

/**
 * @brief The Coils class
 * 抽象出一个Coils
 */
class Coils
{
private:
    bool state;
public:
    std::string name;
    int address;
    Coils(std::string name,int address)
    {
        this->name = name;
        this->address = address;
    }
    bool getState()
    {
        return this->state;
    }
    void setState(bool state)
    {
        this->state = state;
    }
};

/**
 * @brief The Register class
 * 抽象出一个Register
 */
class Register
{
private:
    float value;
public:
    std::string name;
    int address;
    Register(std::string name,int address)
    {
        this->name = name;
        this->address = address;
    }
    void setValue(float value)
    {
        this->value = value;
    }
    float getValue()
    {
        return this->value;
    }
};

/**
 * @brief The InputRegister class
 * 抽象出一个InputRegister
 */
class InputRegister
{
private:
    float value;
public:
    std::string name;
    int address;
    InputRegister(std::string name,int address)
    {
        this->name = name;
        this->address = address;
    }
    float getValue()
    {
        return this->value;
    }
};

/**
 * @brief The ModbusBlock class
 * store modbus mapping
 * 存储modbus mapping，并实现寄存器与modbusmapping的映射
 */
class ModbusBlock
{
private:
    //number of each register
    int nbCoils;
    int nbInputCoils;
    int nbRegister;
    int nbInputRegister;
    //modbus mapping
    modbus_mapping_t *modbusMapping;
    //register map
    std::map<std::string,int> coilsMap;
    std::map<std::string,int> inputCoilsMap;
    std::map<std::string,int> registerMap;
    std::map<std::string,int> inputRegisterMap;
public:
    ModbusBlock();
    ModbusBlock(int nbCoils,int addrCoils,int nbInputCoils,int addrInputCoils,
                int nbRegister,int addrRegister,int nbInputRegister,int addrInputRegister);
    ~ModbusBlock();
    modbus_mapping_t *getMapping();
    void addCoils(Coils* coils);
    uint8_t getCoilsValue(Coils* coils);
    void addInputCoils(InputCoils* inputCoils);
    uint8_t getInputCoils(InputCoils* inputCoils);
    void addRegister(Register* regi);
    uint16_t getRegister(Register* regi);
    void addInputRegister(InputRegister* inputRegister);
    uint16_t getInputRegister(InputRegister* inputRegister);
};

#endif // MODBUSBLOCK_H
