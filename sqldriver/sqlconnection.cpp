#include "sqlconnection.h"

SQLConnection::SQLConnection(std::string url, std::string port, std::string dbName, std::string user, std::string pass)
{
    this->url = url;
    this->port = port;
    this->dbName = dbName;
    this->user = user;
    this->pass = pass;
    this->conn = NULL;

    try
    {
        //this->mysql = get_driver_instance();
        //this->mysql = sql::Connection::;
        this->mysql = sql::mysql::get_mysql_driver_instance();
    }
    catch (sql::SQLException& ex)
    {
        //
        ex.what();
    }
}

void SQLConnection::connect() throw(SQLDriverException)
{
    try
    {
        std::stringstream ss;
        ss << "tcp://" <<this->url << ":" <<this->port;
        this->conn = this->mysql->connect(ss.str(),this->user,this->pass);
        std::cout<<this->conn->getClientInfo()<<std::endl;
        conn->setSchema( this->dbName );
    }
    catch(sql::SQLException& ex)
    {
        SQLDriverException e("connect_error",ex.what());
        throw e;
    }
}

void SQLConnection::close() throw(SQLDriverException)
{
    if(this->conn != NULL)
    {
        this->conn->close();
        delete this->conn;
        this->conn = NULL;
    }
    else
    {
        SQLDriverException e("close_error","...");
        throw e;
    }
}

void SQLConnection::execute(std::string sql) throw (SQLDriverException)
{
    sql::Statement* stmt = NULL;
    try
    {
        stmt = this->conn->createStatement();
        stmt->execute( sql );
        stmt->close();
        delete stmt;
    }
    catch(sql::SQLException& ex)
    {
        if(stmt != NULL)
        {
            delete stmt;
        }

        SQLDriverException e("execute error",ex.what());
        throw e;
    }
}

void SQLConnection::changeDatabase(std::string dbName)
{
    this->dbName = dbName;
    this->conn->setSchema(this->dbName);
}

//SQLResult SQLConnection::executeQuery(std::string sql)
//{
//    sql::Statement* stmt = NULL;
//    sql::ResultSet* rs = NULL;
//    sql::ResultSetMetaData* meta_data = NULL;

//    try
//    {
//        stmt = this->conn->createStatement();
//        rs = stmt->executeQuery(sql);
//        meta_data = rs->getMetaData();
//        unsigned int colnum = meta_data->getColumnCount();
//        std::map<int,SQLRow> rows;
//        int k = 0;

//        while(rs->next())
//        {
//            std::map<std::string,std::string> row;

//            for(unsigned int i = 1;i <= colnum; i++)
//            {
//                std::pair<std::string,std::string> p;
//                p.first = meta_data->getColumnName(i);

//                if(meta_data->getColumnType(i) == "INT")
//                {
//                    int val = rs->getInt(p.first);
//                    std::stringstream ss;
//                    ss << val;
//                    p.second = ss.str();
//                }
//                else if(meta_data->getColumnType(i) == "VARCH")
//                {
//                    std::string val = rs->getString(p.first);
//                    p.second = val;
//                }

//                row.insert(p);
//            }

//            std::pair<int,SQLRow> p;
//            p.first = k;
//            p.second = row;
//            row.insert(p);
//            k++;
//        }

//        stmt->close();
//        delete rs;
//        delete stmt;

//        SQLResult res(rows);
//        return res;
//    }
//    catch(sql::SQLException& ex)
//    {
//        if(stmt != NULL)
//        {
//            delete stmt;
//        }

//        if(rs != NULL)
//        {
//            delete rs;
//        }

//        SQLDriverInterface e("execute_error",ex.what());
//        throw e;
//    }
//}
