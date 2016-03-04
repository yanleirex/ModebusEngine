#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

/**
  * 处理与数据库连接相关
 */
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include "sqldriverinterface.h"
#include <string>
#include <sstream>

class SQLConnection : public SQLDriverInterface
{
private:
    sql::Driver* mysql;
    sql::Connection* conn;

    //connection parameters
    std::string url;
    std::string port;
    std::string dbName;
    std::string user;
    std::string pass;
public:
    SQLConnection(std::string url,
                  std::string port,
                  std::string dbName,
                  std::string user,
                  std::string pass);
    void connect() throw( SQLDriverException );
    void close() throw( SQLDriverException );
    void execute( std::string sql ) throw( SQLDriverException );
    //SQLResult executeQuery( std::string sql ) throw( SQLDriverException );
    void changeDatabase(std::string dbName);
    void createTable(std::string tableName);
    void createDatabase(std::string dbName);
};

#endif // SQLCONNECTION_H
