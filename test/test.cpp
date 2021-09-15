#include<iostream>
#include<sstream>
#include<fstream>
#include"../Serializer.h"
#include"../../Tester/Tester.h"

using std::cout;
using std::string;

const int integer=1;
const float f = 3.5f;
const char str[]= "string1";
const bool bol = true;

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

void testObjDump(Tester* t)
{
    Serializer::Object obj;
    obj.setProperty("val1").set(integer);
    obj.setProperty("val2").set(f);
    auto& val3 = obj.setProperty("val3");
    val3.setProperty("subval1").set(str);
    val3.setProperty("subval2").set(bol);
    val3.setProperty("subval3").at(0).set(integer);
    val3.setProperty("subval3").at(1).set(f);
    obj.setProperty("subval4").at(0) = val3;
    
    Serializer::dumpJson(obj,"test.json");
}

void testObjParse(Tester* t)
{
    const Serializer::Object obj = Serializer::parseJson("test.json");
    Serializer::dumpJson(obj,cout);
    t->assert_eq( obj.get("val1").get<int>(), integer,"integer retrieved" );
    t->assert_eq(obj.get("val2").get<float>(), f , "float retrieved");
    t->assert_eq(obj.get("val3").get("subval1").get<std::string>(),str , "string retrieved");
    t->assert_eq( obj.get("val3").get("subval2").get<bool>(), bol,"boolean retrieved" );
}

int main()
{
    Tester t("Serializer test");
    t.test(testAdd,"add");
    t.test(testObjDump,"dump");
    t.test(testObjParse,"parse");
    return 0;
}