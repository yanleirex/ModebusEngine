#include <iostream>
#include "sqldriver/sqlconnection.h"
#include "modbusdriver/modbustcp2rtu.h"
#include "core/parm.hpp"
#include "modbusdriver/modbusblock.h"
#include "core/thread.hpp"
#include "modbusdriver/modbusdevice.h"
#include "core/log4z/log4z.h"
using namespace zsummer::log4z;


#include "core/mysql-cpp/MySql.hpp"
#include "core/mysql-cpp/MySqlException.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

using std::basic_ostream;
using std::cin;
using std::cout;
using std::endl;
using std::get;
using std::ostream;
using std::string;
using std::tuple;
using std::unique_ptr;
using std::vector;

void testTCP2RTUconnection()
{
    TcpParm *tcpParm = new TcpParm("127.0.0.1",1502);
    RtuParm *rtuParm = new RtuParm("/dev/ttyUSB0", 9600, 'N', 8, 1);
    ModbusTCP2RTU *conn = new ModbusTCP2RTU(tcpParm,rtuParm,10,5);
    conn->setDebug(true);
    ModbusBlock *block = new ModbusBlock(100,0,100,0,100,0,100,0);
    conn->addBlock(block);
    conn->startThread();
}

void testDevice()
{
    ModbusBlock *block = new ModbusBlock(100,0,100,0,100,0,100,0);
    TcpParm *tcpParm = new TcpParm("192.168.137.206",1502);
    RtuParm *rtuParm = new RtuParm("/dev/ttyUSB1", 9600, 'N', 8, 1);
    TcpParm *tcpParm1 = new TcpParm("192.168.137.206",1503);
    RtuParm *rtuParm1 = new RtuParm("/dev/ttyACM0", 9600, 'N', 8, 1);
    ModbusDevice *device = new ModbusDevice("Raspberry pi",tcpParm,rtuParm,10,block);
    ModbusDevice *device1 = new ModbusDevice("Arduino1",tcpParm1,rtuParm1,10,block);
    device->startDevice();
    device1->startDevice();
}

void testLog()
{
    ILog4zManager::getRef().start();
    ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID,LOG_LEVEL_TRACE);
    //begin test stream log input....
    LOGT("stream input *** " << "LOGT LOGT LOGT LOGT" << " *** ");
    LOGD("stream input *** " << "LOGD LOGD LOGD LOGD" << " *** ");
    LOGI("stream input *** " << "LOGI LOGI LOGI LOGI" << " *** ");
    LOGW("stream input *** " << "LOGW LOGW LOGW LOGW" << " *** ");
    LOGE("stream input *** " << "LOGE LOGE LOGE LOGE" << " *** ");
    LOGA("stream input *** " << "LOGA LOGA LOGA LOGA" << " *** ");
    LOGF("stream input *** " << "LOGF LOGF LOGF LOGF" << " *** ");

    //begin test stream log all types input....
    LOGD("char:" <<'c'
         << ", unsigned char:" << (unsigned char) 'c'
         << ", short:" << (short) -1
         << ", unsigned short:" << (unsigned short) -1
         << ", int:" << (int) -1
         << ", unsigned int:" << (unsigned int) -1
         << ", long:" << (long) -1
         << ", unsigned long:" << (unsigned long) -1
         << ", long long:" << (long long) -1
         << ", unsigned long long:" << (unsigned long long) -1
         << ", float:" << (float) -1.234567
         << ", double:" << (double) -2.34566
         << ", std::string:" << std::string("fffff")
         //<< ", int *:" << ( int *) argv
         //<< ", const int *:" << (const int *) argv
         << ", constant:" << 1000
         << ", constant:" << 100.12345678
         << ", bool:" << true
         << ", show hex data:" << Log4zBinary("1234567890abcdefghigklmnopqrstuvwxyz_zyw_zsummer_log4z", 50));


    std::string str;
    str.resize(3000, 's');

    // cannot support VC6 or VS2003

    //begin test format log input....
    LOGFMTT("format input *** %s *** %d ***", "LOGFMTT", 123456);
    LOGFMTD("format input *** %s *** %d ***", "LOGFMTD", 123456);
    LOGFMTI("format input *** %s *** %d ***", "LOGFMTI", 123456);
    LOGFMTW("format input *** %s *** %d ***", "LOGFMTW", 123456);
    LOGFMTE("format input *** %s *** %d ***", "LOGFMTE", 123456);
    LOGFMTA("format input *** %s *** %d ***", "LOGFMTA", 123456);
    LOGFMTF("format input *** %s *** %d ***", "LOGFMTF", 123456);

    //begin test format log big string more than buff size input....
    LOGFMT_DEBUG(LOG4Z_MAIN_LOGGER_ID, "%s", str.c_str());

    //begin test stream log big string more than buff size input....
    LOGD(str);
    LOGA("main quit ...");
}

