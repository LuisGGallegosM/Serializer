#include<iostream>
#include<sstream>
#include<fstream>
#include"../Serializer.h"
#include"../../Tester/Tester.h"

using std::cout;
using std::string;

void testAdd(Tester* t)
{
    int val_int=3;
    float val_float=2.0f;
    Serializer::Object obj;

    obj.set(val_int);

    int obtained= obj.get<int>();

    t->assert_eq(val_int,obtained,"set integer");

    obj.set(2.0f);

    float obtained_f= obj.get<float>();
    t->assert_eq(obtained_f,val_float,"set float");

}

void testObj(Tester* t)
{
    int integer=1;
    float f = 3.5f;
    Serializer::Object obj;
    obj.setProperty("val1").set(integer);
    obj.setProperty("val2").set(f);
    auto& val3 = obj.setProperty("val3");
    val3.setProperty("subval1").set("a");
    val3.setProperty("subval2").set("b");
    
    Serializer::dumpJson(obj,"test.json");
}

int main()
{
    Tester t("Serializer test");
    t.test(testAdd,"add");
    t.test(testObj,"output parse");
    return 0;
}