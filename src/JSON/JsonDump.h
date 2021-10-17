#ifndef SERIALIZER_JSON_DUMP
#define SERIALIZER_JSON_DUMP

#include"../Object.h"
#include<fstream>

namespace Serializer
{
    void dumpJson(const Object& obj, const std::string& filename);
    void dumpJson(const Object& obj,std::ostream& output , int indent=0 );
}

#endif