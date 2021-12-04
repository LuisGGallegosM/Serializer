
#include"Serializer.h"

namespace serializer
{
    Object parse(const std::string& filename)
    {
        if(filename.find(".json")!=std::string::npos)
            return json::parse(filename.data());
        else if (filename.find(".csv")!=std::string::npos)
            return csv::parse(filename.data());
        else
            throw std::invalid_argument("Error: not valid file extension!");
    }
}