#ifndef PARM_HPP
#define PARM_HPP

#include <string>

class RtuParm
{
private:

public:
    const char *device;
    int baud;
    char parity;
    int data_bit;
    int stop_bit;
    int slaveId;
    RtuParm(const char *device,int baud,char parity,int data_bit,int stop_bit)
    {
        this->device = device;
        this->baud = baud;
        this->parity = parity;
        this->data_bit = data_bit;
        this->stop_bit = stop_bit;
    }
};

class TcpParm
{
private:

public:
    std::string ip;
    int port;
    TcpParm(std::string ip,int port)
    {
        this->ip = ip;
        this->port = port;
    }
};

#endif // PARM_HPP

