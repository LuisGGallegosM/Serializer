
#ifndef SERIALIZER_OBJECT
#define SERIALIZER_OBJECT

#include<string>
#include<vector>

namespace Serializer
{
    struct KeyValuePair;

    class Object
    {
        public:
        enum class Type { Null ,Float, Int, String, Bool, Object, Array };
        private:
        union bundle
        {
            float f;
            int i;
            bool b;
        };
        Type type;
        bundle val;
        std::vector<KeyValuePair> contents;
        std::string str;

        public:

        Object(): type(Type::Null), contents(), str()
        {
            val.i=0;
        }

        Object(Type t) : Object() 
        {
            type=t;
        }

        Object(const Object& obj) = default;
        Object(Object&& obj) = default;

        void clear();
        
        template<typename T>
        T get() const;

        const Object& get(const std::string& name) const;
        Object& get(const std::string& name);

        void set(float value);
        void set(int value);
        void set(bool value);
        void set(const char* value);

        Object& setProperty(const std::string& name);
        void setProperty(const std::string& name ,const Object& value);
        void set(const std::vector<Object>& value);

        Object& at(int index);
        const Object& at(int index) const;

        Type getType() const {return type;}
        std::vector<std::string> getKeys() const;
        int size() const {return contents.size();}
    };

    template<>
    float Object::get<float>() const;

    template<>
    int Object::get<int>() const;

    struct KeyValuePair
    {
        std::string key;
        Object value;
    };
}

#endif