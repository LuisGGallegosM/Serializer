
#include"JsonParser.h"

namespace Serializer
{

    JsonParser::JsonParser(std::istream* in): c(0), linenum(1), error(false), input(in)
    {
        advance();
    }

    Object JsonParser::parse()
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
        else throw getError();
        return output;
    }

    bool JsonParser::advance()
    {
        bool cont= bool(input->get(c));
        if(c=='\n') linenum++;
        return cont;
    }

    void JsonParser::advanceWhitespace()
    {
        do 
        {
            if(!std::isspace(c)) break;
        } while(advance());
    }

    std::string JsonParser::advanceUpTo(char limit)
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

    Object JsonParser::parseObject()
    {
        Object output;
        if (c!='{') throw getError();
        advance();
        do 
        {
            //capture key
            advanceWhitespace();
            if (c!= '"') throw getError();
            advance();
            std::string key = advanceUpTo('"');
            advanceWhitespace();
            if (c!=':') throw getError();
            advance();

            //capture value
            advanceWhitespace();
            Object value = parseValue();

            output.property(key) =value;
            advanceWhitespace();
            if (c=='}') break;
            if (c!=',') throw getError();
        } while(advance());
        advance();
        return output;
    }

    Object JsonParser::parseArray()
    {
        Object output;
        int index=0;
        if (c!='[') throw getError();
        advance();
        do
        {
            advanceWhitespace();
            output.at(index)=parseValue();
            advanceWhitespace();
            index++;
            if (c==']') break;
            if (c!=',') throw getError();
        } while (advance());
        advance();
        return output;
    }

    Object JsonParser::parseValue()
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
                output.set(std::stoi(value));
            }
            else
            {
                output.set(std::stof(value));
            }
        }
        else if (c=='"')
        {
            advance();
            std::string value=advanceUpTo('"');
            output.set(value);
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
                output.set(true);
            else if (val=="false")
                output.set(false);
            else if (val!="null")
                throw std::invalid_argument("value '"+ val +" not recognized.\n" );
        }
        else throw getError();
        return output;
    }

    std::invalid_argument JsonParser::getError()
    {
        std::string err="unexpected character '";
        err+=c;
        err+= "' at line "+std::to_string(linenum)+".\n";
        return std::invalid_argument(err);
    }

    Object parseJson(const std::string& filename)
    {
        std::fstream file(filename);
        JsonParser parser(&file);
        return parser.parse();
    }    

}