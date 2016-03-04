#include <iostream>
#include "test/test.cpp"
#include "core/log4z/log4z.h"

using namespace zsummer::log4z;

int main()
{
    ILog4zManager::getRef().start();
    ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID,LOG_LEVEL_TRACE);
    LOGI("<<--This is ModbusEngine!-->>");
    //test();
    //std::cout<<"testing tcp2tru connection..."<<std::endl;
    //testTCP2RTUconnection();
    //testLog();
    LOGI("<<--Test Device-->>");
    testDevice();
    while(true)
    {

    }
    return 0;
}
