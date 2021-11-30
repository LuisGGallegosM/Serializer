
#include"JsonParser.h"

namespace serializer
{
namespace json
{
    Parser::Parser(std::istream* in): c(0), linenum(1), error(false), input(in)
    {
        advance();
    }

    Object Parser::parse()
    {
        Object output;
        advanceWhitespace();
        if (c=='{')
        {
            output=parseObject();
        } else if (c=='[')
        {
            output=parseArray();
        }
        else throw getError("parse, expected [ or {");
        return output;
    }

    bool Parser::advance()
    {
        bool cont= bool(input->get(c));
        if(c=='\n') linenum++;
        return cont;
    }

    void Parser::advanceWhitespace()
    {
        do 
        {
            if(!std::isspace(c)) break;
        } while(advance());
    }

    std::string Parser::advanceUpTo(char limit)
    {
        std::string output;
        do 
        {
            if(c==limit) break;
            output.push_back(c);
        } while(input->get(c));
        advance();
        return output;
    }

    Object Parser::parseObject()
    {
        Object output;
        if (c!='{') throw getError("parse, expected {");
        advance();
        do 
        {
            //capture key
            advanceWhitespace();
            if (c!= '"') throw getError("parse, expected \"");
            advance();
            std::string key = advanceUpTo('"');
            advanceWhitespace();
            if (c!=':') throw getError("parse, expected :");
            advance();

            //capture value
            advanceWhitespace();
            Object value = parseValue();

            const char* name=key.data();

            output[name] =value;
            advanceWhitespace();
            if (c=='}') break;
            if (c!=',') throw getError("parse, expected ,");
        } while(advance());
        advance();
        return output;
    }

    Object Parser::parseArray()
    {
        Object output;
        int index=0;
        if (c!='[') throw getError("parse, expected [");
        advance();
        do
        {
            advanceWhitespace();
            output[index]=parseValue();
            advanceWhitespace();
            index++;
            if (c==']') break;
            if (c!=',') throw getError("parse, expected ,");
        } while (advance());
        advance();
        return output;
    }

    Object Parser::parseValue()
    {
        Object output;
        if (std::isdigit(c))
        {
            std::string value;
            value.push_back(c);
            while(advance())
            {
                if ((!std::isdigit(c)) && (c!='e') && (c!='.') && (c!='E'))
                    break;
                value.push_back(c);
            }
            if(value.find('.')==std::string::npos)
            {
                output=(std::stoi(value));
            }
            else
            {
                output=(std::stof(value));
            }
        }
        else if (c=='"')
        {
            advance();
            std::string value=advanceUpTo('"');
            output=(value.data());
        }
        else if (c=='{')
        {
            output =parseObject();
        }
        else if (c=='[')
        {
            output = parseArray();
        }
        else if ((c=='t') || (c=='f') || (c=='n'))
        {
            std::string val;
            do
            {
                if (!std::isalpha(c)) break;
                val.push_back(c);
            } while (advance());
            if (val=="true")
                output=(true);
            else if (val=="false")
                output=(false);
            else if (val!="null")
                throw std::invalid_argument("value '"+ val +" not recognized.\n" );
        }
        else throw getError("parse, invalid value");
        return output;
    }

    std::invalid_argument Parser::getError(const char* st)
    {
        std::string err="ERROR: in "+std::string(st)+" at line " +std::to_string(linenum) + ": '";
        if ( isgraph(c) )
        {
            err.push_back(c);
        }
        err+="' : "+std::to_string(int(c));
        err+=" .\n";
        return std::invalid_argument(err);
    }

    Object parse(const char* filename)
    {
        std::fstream file(filename);
        if (file.is_open())
        {
            Parser parser(&file);
            return parser.parse();
        }
        else
        {
            throw std::runtime_error("ERROR: cannot open file:"+std::string(filename) + ".\n");
        }
    }    
}
}