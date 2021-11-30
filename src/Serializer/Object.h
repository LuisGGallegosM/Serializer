
#ifndef SERIALIZER_OBJECT
#define SERIALIZER_OBJECT

#include<vector>
#include<string>

namespace serializer
{
    struct KeyValuePair;

    class Object
    {
        public:
        enum class Type { Null ,Float, Int, String, Bool, Object, Array };
        class PropertyIterable
        {
            public:
            using const_iterator= std::vector<KeyValuePair>::const_iterator;

            PropertyIterable(const_iterator b, const_iterator e):
                i0(b), i1(e) {}
            const_iterator begin() const { return i0; }
            const_iterator end() const { return i1; }
            private:
            const_iterator i0;
            const_iterator i1;
        };

        Object();
        Object(const Object& obj) = default;
        Object(Object&& obj) = default;
        Object& operator=(const Object& other) = default;
        void clear();

        //accesors
        Type getType() const {return type;}
        int size() const {return contents.size();}

        //simple variable access
        Object(int value);
        Object(float value);
        Object(bool value);
        Object(const char* value);
        Object(const std::string& value) : Object(value.data()) {};
        Object(nullptr_t n);

        Object& operator=(int val);
        Object& operator=(float val);
        Object& operator=(bool val);
        Object& operator=(const char* val);
        Object& operator=(const std::string& val) { return (*this)=val.data(); }
        Object& operator=(nullptr_t n);

        operator float() const;
        operator int() const;
        operator const char*() const;
        operator bool() const;

        //object type access
        const Object& operator[] (const char* name) const;
        Object& operator[] (const char* name);
        
        Object* find(const char* name);
        const Object* find(const char* name) const;

        const Object& operator[] (const std::string& name) const {return (*this)[name.data()];}
        Object& operator[] (const std::string& name) {return (*this)[name.data()];}
        
        Object* find(const std::string& name) {return find(name.data());}
        const Object* find(const std::string& name) const {return find(name.data());}

        PropertyIterable getPropertyIterable() const 
            { return PropertyIterable(contents.begin(), contents.end());}

        //array type access
        Object& operator[] (int index);
        const Object& operator[](int index) const;
        void push_back(const Object& o );
        void push_back(Object&& o );

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
    };

    struct KeyValuePair
    {
        std::string key;
        Object value;
    };

    int tokenize(const std::string& str, char limit, std::vector<std::string>& tokens);
}

#endif