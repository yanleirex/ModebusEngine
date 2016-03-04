#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T14:11:33
#
#-------------------------------------------------

QT       += core

QT       -= gui
QT       -= core

TARGET = ModbusEngine
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    modbusdriver/modbusconnection.cpp \
    modbusdriver/modbustcp2rtu.cpp \
    modbusdriver/modbusdriver.cpp \
    modbusdriver/modbusdevice.cpp \
    modbusdriver/modbusblock.cpp \
    modbusproject.cpp \
#    sqldriver/mysqldriver.cpp \
#    sqldriver/sqlconnection.cpp \
    test/test.cpp \
    synchronizer/synchronizer.cpp \
    core/log4z/log4z.cpp \
#    core/mysql-cpp/MySql.cpp \
#    core/mysql-cpp/MySqlException.cpp \
#    core/mysql-cpp/MySqlPreparedStatement.cpp \
#    core/mysql-cpp/OutputBinder.cpp

HEADERS += \
    modbusdriver/modbusconnection.h \
    modbusdriver/modbustcp2rtu.h \
    modbusdriver/modbusdriver.h \
    modbusdriver/modbusdevice.h \
    core/thread.hpp \
    core/parm.hpp \
    core/type.hpp \
    modbusdriver/modbusblock.h \
    modbusproject.h \
    core/lib/rapidxml/rapidxml.hpp \
    core/lib/rapidxml/rapidxml_iterators.hpp \
    core/lib/rapidxml/rapidxml_print.hpp \
    core/lib/rapidxml/rapidxml_utils.hpp \
    core/conversion.hpp \
#    sqldriver/mysqldriver.h \
#    sqldriver/sqldriverexception.hpp \
#    sqldriver/sqlresult.hpp \
#    sqldriver/sqldriverinterface.h \
#    sqldriver/sqlconnection.h \
    synchronizer/synchronizer.h \
    core/log4z/log4z.h \
#    core/mysql-cpp/InputBinder.hpp \
#    core/mysql-cpp/MySql.hpp \
#    core/mysql-cpp/MySqlException.hpp \
#    core/mysql-cpp/MySqlPreparedStatement.hpp \
#    core/mysql-cpp/OutputBinder.hpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libmodbus    #modbus libmodbus
#LIBS += -libmodbus

QMAKE_CXXFLAGS += -std=c++11
LIBS += -pthread            #thread lib
LIBS += -lmysqlcppconn      #mysqlcppconn lib
