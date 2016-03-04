#ifndef SQLRESULT_HPP
#define SQLRESULT_HPP

#include <map>
#include <sstream>

/**
 * @brief The SQLRow class
 *
 * Represents a row of an SQL result. BETA.
 */
class SQLRow
{
private:
    std::map<std::string,std::string> row;

public:
    SQLRow(){}

    SQLRow( std::map<std::string,std::string> row )
    {
        this->row = row;
    }

    std::string getString( std::string name ) throw( std::string )
    {
        std::map<std::string,std::string>::iterator it;
        it = this->row.find( name );

        if( it == this->row.end() )
        {
            throw std::string( "not_found" );
        }

        std::pair<std::string,std::string> p = *it;

        return p.second;
    }

    int getInt( std::string name ) throw( std::string )
    {
        std::map<std::string,std::string>::iterator it;
        it = this->row.find( name );

        if( it == this->row.end() )
        {
            throw std::string( "not_found" );
        }

        std::pair<std::string,std::string> p = *it;

        std::stringstream ss;
        ss << p.second;
        int ret = 0;
        ss >> ret;

        return ret;
    }
};

/**
 * @brief The SQLResult class
 *
 * Represents an SQL Result. BETA.
 */
class SQLResult
{

private:
    std::map<int,SQLRow> rows;

public:
    SQLResult( std::map<int,SQLRow> rows )
    {
        this->rows = rows;
    }

    SQLRow getRow( int rowNum ) throw( std::string )
    {
        std::map<int,SQLRow>::iterator it;
        it = this->rows.find( rowNum );

        if( it == this->rows.end() )
        {
            throw std::string( "not_found" );
        }

        std::pair<int,SQLRow> p = *it;

        return p.second;
    }

    int getRowNum()
    {
        return this->rows.size();
    }

};

#endif // SQLRESULT_H
