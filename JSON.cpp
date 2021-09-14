
#include"JSON.h"

namespace Serializer
{
    void dumpJson(const Object& obj, const std::string& filename)
    {
        std::ofstream file(filename,std::ios_base::trunc);
        dumpJson(obj,file);

    }

    void dumpObj(const Object& obj,std::ostream& output, int indent)
    {
        std::string ind;
        ind.resize(indent*2,' ');

        output << ind << "{\n";
        auto keys=obj.getKeys();
        bool firstComma =false;
        for(auto key : keys)
            {
                if(firstComma) output << ",\n";
                output << ind << "\"" << key << "\" : ";
                dumpJson( obj.get(key), output, indent+1 );
                firstComma=true;
            }
        output << '\n' << ind << "}";
    }

    void dumpArray(const Object& obj,std::ostream& output, int indent)
    {
        std::string ind;
        ind.resize(indent*2,' ');

        output << ind << "[\n";
        int length = obj.size();
        bool firstComma =false;
        for(int i=0;i<length;i++)
            {
                if(firstComma) output << ",\n";
                output << ind << "  " ;
                dumpJson( obj.at(i), output, indent+1 );
                firstComma=true;
            }
        output << '\n' << ind << "]";
    }

    void dumpJson(const Object& obj,std::ostream& output , int indent )
    {

        Object::Type type= obj.getType();
        switch(type)
        {
            case Object::Type::Object:
                dumpObj(obj,output,indent);
            break;
                
            case Object::Type::Array:
                dumpArray(obj,output,indent);
            break;

            case Object::Type::Float:
            output << obj.get<float>();
            break;

            case Object::Type::Int:
            output << obj.get<int>();
            break;

            case Object::Type::Null:
            output << "null";
            break;

            case Object::Type::Bool:
            output << (obj.get<bool>() ? "true" : "false");
            break;

            case Object::Type::String:
            output << '"' << obj.get<std::string>() << '"';
            break;
        }
    }

}