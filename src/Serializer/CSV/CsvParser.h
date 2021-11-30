#ifndef SERIALIZER_CSV_PARSER
#define SERIALIZER_CSV_PARSER

#include"../Object.h"

namespace serializer
{
namespace csv
{
    Object parse(const char* filename);
    
}
}

#endif