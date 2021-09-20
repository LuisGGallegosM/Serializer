#include<iostream>
#include<sstream>
#include<fstream>
#include"../Serializer.h"
#include"Tester/Tester.h"

using std::cout;
using std::string;

const int integer=1;
const float f = 3.5f;
const char str[]= "string1";
const bool bol = true;

const char filename1[]="test/test1.json";
const char filename2[]="test/test2.json";
const char filename3[]="test/test3.json";

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
    obj["val1"]=integer;
    obj["val2"]=f;
    auto& val3 = obj["val3"];
    val3["subval1"]=str;
    val3["subval2"]=bol;
    val3["subval3"][0]=integer;
    val3["subval3"][1]=f;
    obj["subval4"][0] = val3;
    
    Serializer::dumpJson(obj,"test/test1.json");
    t->assert_true(true,"test1.json dumped");
}

void testObjParse(Tester* t)
{
    Serializer::Object obj = Serializer::parseJson(filename1);
    t->assert_true(true,"test1.json parsed");

    obj = Serializer::parseJson(filename2);
    t->assert_true(true,"test2.json parsed");
}

void testIdenpotent(Tester* t)
{
    Serializer::Object obj = Serializer::parseJson(filename1);
    Serializer::dumpJson(obj,filename3);
    std::fstream f1(filename3);
    std::fstream f2(filename1);

    std::stringstream str1;
    std::stringstream str2;
    str1 << f1.rdbuf();
    str2 << f2.rdbuf();
    t->assert_true(str1.str()==str2.str(),"parse dump identpotent"); 

}

int main()
{
    Tester t("Serializer test");
    t.test(testAdd,"add");
    t.test(testObjDump,"dump");
    t.test(testObjParse,"parse");
    t.test(testIdenpotent,"parse+dump identpotent");
    return t.returnValue();
}