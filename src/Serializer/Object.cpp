
#include"Serializer.h"
#include<stdexcept>

namespace serializer
{
    Object::Object(): type(Type::Null), contents(), str()
    {
        val.i=0;
    }

    Object::Object(nullptr_t n): Object()
    {}

    Object::Object(int value) :type(Type::Int), contents(), str()
    {
        val.i=value;
    }

    Object::Object(float value) :type(Type::Float), contents(), str()
    {
        val.f=value;
    }

    Object::Object(bool value) :type(Type::Bool), contents(), str()
    {
        val.b=value;
    }

    Object::Object(const char* value) :type(Type::String), contents(), str()
    {
        if(value!=nullptr) 
            str=value;
        val.i=0;
    }

    void Object::clear()
    {
        type = Type::Null;
        val.i = 0;
        str.clear();
        contents.clear();
    }

    Object::operator float() const 
    {
        if ((type!=Type::Float) && (type!=Type::Int)) throw std::invalid_argument("variable is not numeric!");
        return (type== Type::Float) ? val.f : float(val.i);
    }

    Object::operator int() const 
    {
        if ((type!=Type::Int) && (type!=Type::Float)) throw std::invalid_argument("variable is not numeric!");
        return (type== Type::Int) ? val.i : int(val.f);
    }

    Object::operator const char*() const 
    {
        if (type!=Type::String) throw std::invalid_argument("variable is not string!");
        return str.data();
    }

    Object::operator bool() const 
    {
        if (type!=Type::Bool) throw std::invalid_argument("variable is not boolean!");
        return val.b;
    }

    Object& Object::operator=(nullptr_t n)
    {
        clear();
        type = Type::Null;
        return (*this);
    }

    Object& Object::operator=(float value)
    {
        clear();
        type=Type::Float;
        val.f = value;
        return (*this);
    }

    Object& Object::operator=(int value) 
    {
        clear();
        type=Type::Int;
        val.i = value;
        return (*this);
    }

    Object& Object::operator=(bool value)
    {
        clear();
        type=Type::Bool;
        val.b = value;
        return (*this);
    }

    Object& Object::operator=(const char* value)
    {
        clear();
        type=Type::String;
        str = value;
        return (*this);
    }

    Object* Object::find(const char* name)
    {
        for(auto& v : contents)
        {
            if(v.key==name)
            {
                return &(v.value);
            }
        }
        return nullptr;
    }

    const Object* Object::find(const char* name) const
    {
        for(auto& v : contents)
        {
            if(v.key==name)
            {
                return &(v.value);
            }
        }
        return nullptr;
    }

    const Object& Object::operator[] (const char* name) const
    {
        if (type!=Type::Object) throw std::invalid_argument("variable is not object!");
        const Object* prop=find(name);
        if (prop!=nullptr) return *prop;
        throw std::invalid_argument("variable has not '"+std::string(name)+ "' key");
    }

    Object& Object::operator[] (const char* name)
    {
        if (type!=Type::Object)
        {
            clear();
            type=Type::Object;
        }
        Object* found=find(name);
        if (found==nullptr)
        {
            contents.push_back({ name , Object() });
            found= &(contents.back().value);
        }

        return *found;
    }

    Object& Object::operator[](int index)
    {
        if (index < 0) throw std::invalid_argument("negative index in array!");
        if(type!=Type::Array)
        {
            clear();
            type=Type::Array;
        }
        if (index >= contents.size())
        {
            for(int i=contents.size();i<=index;i++)
                contents.push_back({"",Object()});
        }
        return contents.at(index).value;
    }

    const Object& Object::operator[](int index) const
    {
        if (type!=Type::Array) throw std::invalid_argument("variable is not array!");
        if (index < 0) throw std::invalid_argument("negative index in array!");
        return contents.at(index).value;
    }

    void Object::push_back(const Object& o )
    {
        if(type!=Type::Array)
        {
            clear();
            type=Type::Array;
        }
        contents.push_back({"",o});
    }
    void Object::push_back(Object&& o )
    {
        if(type!=Type::Array)
        {
            clear();
            type=Type::Array;
        }
        contents.push_back({"", std::move(o)});
    }

    int tokenize(const std::string& str, char limit, std::vector<std::string>& tokens)
    {
        int numOfTokens=0;
        int i=0;
        int last=0;
        while(str[i]!=0)
        {
            if(str[i]==limit)
            {
                if((i-last)>0)
                {
                    numOfTokens++;
                    if(int(tokens.size())<=numOfTokens) tokens.push_back("");
                    tokens[numOfTokens-1].assign(str.data()+last,i-last);
                }
                last=i+1;
            }
            i++;
        }
        
        if((i-last)>0)
        {
            if(int(tokens.size())<=numOfTokens) tokens.push_back("");
            tokens[numOfTokens].assign(str.data()+last,i-last);
        }
            
        return numOfTokens;
    }
}