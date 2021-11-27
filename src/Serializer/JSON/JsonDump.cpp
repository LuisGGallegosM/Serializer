
#include"JsonDump.h"

namespace serializer
{
namespace json
{
    struct state
    {
        char c;
        int linenum;
        bool error;
    };
    
    void dump(const Object& obj, const char* filename)
    {
        std::ofstream file(filename,std::ios_base::trunc);

        if (file.good())
            dump(obj,file);
        else
            throw std::runtime_error("ERROR: cannot create file:"+std::string(filename) + ".\n");

    }

    void dumpObj(const Object& obj,std::ostream& output, int indent)
    {
        std::string ind;
        ind.resize(indent*2,' ');

        output << ind << "{\n";
        auto props=obj.getPropertyIterable();
        bool firstComma =false;
        for(auto prop : props)
            {
                if(firstComma) output << ",\n";
                output << ind << "\"" << prop.key << "\" : ";
                dump( prop.value, output, indent+1 );
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
                dump( obj[i], output, indent+1 );
                firstComma=true;
            }
        output << '\n' << ind << "]";
    }

    void dump(const Object& obj,std::ostream& output , int indent )
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
            output << float(obj);
            break;

            case Object::Type::Int:
            output << int(obj);
            break;

            case Object::Type::Null:
            output << "null";
            break;

            case Object::Type::Bool:
            output << ( bool(obj) ? "true" : "false");
            break;

            case Object::Type::String:
            output << '"' << (const char*)(obj) << '"';
            break;
        }
    }
}
}