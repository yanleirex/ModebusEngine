#ifndef MODBUSPROJECT_H
#define MODBUSPROJECT_H

#include <string>

//database param
class MBPro_DB
{
public:
    std::string dbType;
    std::string dbUrl;
    std::string dbPort;
    std::string dbName;
    std::string dbUser;
    std::string dbPass;
};


//project param
class MBPro_Project
{
public:
    std::string name;
};
class ModbusProject
{
public:
    ModbusProject();
};

#endif // MODBUSPROJECT_H
