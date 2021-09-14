#ifndef SERIALIZER_JSON
#define SERIALIZER_JSON

#include"Serializer.h"
#include<fstream>

namespace Serializer
{
    void dumpJson(const Object& obj, const std::string& filename);
    void dumpJson(const Object& obj,std::ostream& output , int indent=0 );
}

#endif