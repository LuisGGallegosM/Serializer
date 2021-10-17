#ifndef SERIALIZER_JSON_PARSER
#define SERIALIZER_JSON_PARSER

#include"../Object.h"
#include<fstream>

namespace Serializer
{
    Object parseJson(const std::string& filename);

    class JsonParser
    {
        std::istream* input;
        char c;
        int linenum;
        bool error;

        void advanceWhitespace();
        bool advance();
        std::string advanceUpTo(char limit);
        std::invalid_argument getError();
        KeyValuePair parseKeyValuePair();

        Object parseObject();
        Object parseArray();
        Object parseValue();

        public:

        JsonParser(std::istream* in);

        Object parse();
    };







}

#endif