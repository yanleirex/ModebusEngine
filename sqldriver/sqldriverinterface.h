#ifndef SQLDRIVERINTERFACE_H
#define SQLDRIVERINTERFACE_H

#include "sqldriverexception.hpp"
#include "sqlresult.hpp"
#include <mysql_driver.h>
#include <mysql_connection.h>


/**
 * @brief The SQLDriverInterface class
 *
 * Abstract SQL Driver class for access databases.
 */
class SQLDriverInterface
{

public:
    virtual void connect() throw( SQLDriverException ) = 0;
    virtual void close() throw( SQLDriverException ) = 0;

    //virtual void execute( std::string sql ) throw( SQLDriverException ) = 0;
    //virtual SQLResult executeQuery( std::string sql ) throw( SQLDriverException ) = 0;
};


#endif // SQLDRIVERINTERFACE_H
