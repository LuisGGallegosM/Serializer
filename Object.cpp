
#include"Serializer.h"
#include<stdexcept>

namespace Serializer
{
    void Object::clear()
    {
        type = Type::Null;
        val.i = 0;
        str.clear();
        contents.clear();
    }

    template<>
    float Object::get<float>() const
    {
        if (type!=Type::Float && type!=Type::Int) throw std::invalid_argument("variable is not float!");
        return val.f;
    }

    template<>
    int Object::get<int>() const
    {
        if (type!=Type::Float && type!=Type::Int) throw std::invalid_argument("variable is not int!");
        return val.i;
    }

    template<>
    std::string Object::get<std::string>() const
    {
        if (type!=Type::String) throw std::invalid_argument("variable is not string!");
        return str;
    }

    template<>
    bool Object::get<bool>() const
    {
        if (type!=Type::Bool) throw std::invalid_argument("variable is not boolean!");
        return val.b;
    }

    const Object& Object::get(const std::string& name) const
    {
        if (type!=Type::Object) throw std::invalid_argument("variable is not object!");
        for(const KeyValuePair& v : contents)
        {
            if(v.key==name) return v.value;
        }
        throw std::invalid_argument("variable has not '"+name+ "' key");
    }

    Object& Object::get(const std::string& name)
    {
        if (type!=Type::Object && type!=Type::Null) throw std::invalid_argument("variable is not object!");
        Object* found=propertyExist(name);
        if (found!=nullptr)
        {
            return *found;
        }
        throw std::invalid_argument("variable has not '"+name+ "' key");
    }

    void Object::set()
    {
        clear();
        type = Type::Null;
    }

    void Object::set(float value)
    {
        clear();
        type=Type::Float;
        val.f = value;
    }

    void Object::set(int value)
    {
        clear();
        type=Type::Int;
        val.i = value;
    }

    void Object::set(bool value)
    {
        clear();
        type=Type::Bool;
        val.b = value;
    }

    void Object::set(const char* value)
    {
        clear();
        type=Type::String;
        str = value;
    }

    void Object::set(const std::string& value)
    {
        set(value.data());
    }

    Object* Object::propertyExist(const std::string& name)
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

    Object& Object::setProperty(const std::string& name)
    {
        if (type!=Type::Object)
        {
            clear();
            type=Type::Object;
        }
        Object* prop= propertyExist(name);
        if (prop==nullptr)
        {
            contents.push_back({name,Object()});
            prop=&(contents.back().value);
        }
            
        return *prop;
    }  

    void Object::setProperty(const std::string& name, const Object& value )
    {
        if (type!=Type::Object)
        {
            clear();
            type=Type::Object;
        }
        contents.push_back({name,value});
    }

    void Object::set(const std::vector<Object>& value)
    {
        clear();
        type=Type::Array;
        int index=0;
        for(auto val : value)
        {
            contents.push_back({ std::to_string(index) , val});
            index++;
        }
    }

    std::vector<std::string> Object::getKeys() const
    {
        if (type!=Type::Object) throw std::invalid_argument("variable is not object!");
        std::vector<std::string> out;
        for(auto val : contents)
            out.push_back(val.key);
        return out;
    }

    Object& Object::at(int index)
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

    const Object& Object::at(int index) const
    {
        if (type!=Type::Array) throw std::invalid_argument("variable is not array!");
        if (index < 0) throw std::invalid_argument("negative index in array!");
        return contents.at(index).value;
    }
}