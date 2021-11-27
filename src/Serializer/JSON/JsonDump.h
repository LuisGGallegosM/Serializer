#ifndef SERIALIZER_JSON_DUMP
#define SERIALIZER_JSON_DUMP

#include"../Object.h"
#include<fstream>

namespace serializer
{
namespace json
{
    void dump(const Object& obj, const char* filename);
    void dump(const Object& obj,std::ostream& output , int indent=0 );
}
}

#endif