#ifndef SERIALIZER_JSON_PARSER
#define SERIALIZER_JSON_PARSER

#include"../Object.h"
#include<fstream>

namespace serializer
{
namespace json
{
    Object parse(const char* filename);

    class Parser
    {
        std::istream* input;
        char c;
        int linenum;
        bool error;

        void advanceWhitespace();
        bool advance();
        std::string advanceUpTo(char limit);
        std::invalid_argument getError(const char* st);
        KeyValuePair parseKeyValuePair();

        Object parseObject();
        Object parseArray();
        Object parseValue();

        public:

        Parser(std::istream* in);

        Object parse();
    };
}
}

#endif