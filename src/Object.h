
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

        Object();
        Object(int value);
        Object(float value);
        Object(bool value);
        Object(const std::string& value);
        Object(const char* value);

        Object(const Object& obj) = default;
        Object(Object&& obj) = default;

        Object& operator=(const Object& other) = default;

        void clear();
        
        template<typename T>
        T get() const;

        void set(float value);
        void set(int value);
        void set(bool value);
        void set(const char* value);
        void set(const std::string& value);
        void set();

        const Object& property(const std::string& name) const;
        Object& property(const std::string& name);

        Object* propertyExist(const std::string& name);
        const Object* propertyExist(const std::string& name) const;
        void set(const std::vector<Object>& value);

        Object& at(int index);
        const Object& at(int index) const;

        const Object& operator[] (const std::string& name) const { return property(name); }
        Object& operator[] (const std::string& name) { return property(name); }
        Object& operator[] (int index) {return at(index);}
        const Object& operator[](int index) const {return at(index);}

        Type getType() const {return type;}
        std::vector<std::string> getKeys() const;
        int size() const {return contents.size();}
    };

    struct KeyValuePair
    {
        std::string key;
        Object value;
    };
}

#endif