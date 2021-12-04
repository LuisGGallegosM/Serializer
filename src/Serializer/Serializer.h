#ifndef SERIALIZER
#define SERIALIZER

#include"JSON/JsonDump.h"
#include"JSON/JsonParser.h"
#include"CSV/CsvParser.h"

namespace serializer
{
    Object parse(const std::string& filename);
}

#endif