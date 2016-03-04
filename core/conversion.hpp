#ifndef CONVERSION_HPP
#define CONVERSION_HPP

#include <sstream>
#include <stdio.h>

namespace ModbusEngine
{

/**
 * @brief The Conversion class
 *
 * Convert generic types via stringstream.
 * It is a library class.
 */
class Conversion
{
public:
    template<typename From, typename To>
    static To convert( From f )
    {
        std::stringstream ss;
        ss << f;
        To t;
        ss >> t;
        return t;
    }

    static std::string toString( float value, int precision )
    {
        std::stringstream ss;
        ss << "%." << precision << "f";
        char _string[100];
        sprintf( _string, ss.str().c_str(), value );
        std::string ret( _string );

        return ret;
    }
};

}

#endif // CONVERSION_HPP
