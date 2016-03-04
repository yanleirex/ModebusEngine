#ifndef SQLDRIVEREXCEPTION_HPP
#define SQLDRIVEREXCEPTION_HPP

#include <string>

class SQLDriverException
{

public:
    std::string type;
    std::string description;

public:
    SQLDriverException( std::string type, std::string description )
    {
        this->type = type;
        this->description = description;
    }

};


#endif // SQLDRIVEREXCEPTION_H
