#include<iostream>
#include<sstream>
#include<fstream>
#include"Serializer/Serializer.h"
#include"Tester/Tester.h"

using std::cout;
using std::string;

const int integer=1;
const float f = 3.5f;
const char str[]= "string1";
const bool bol = true;

const char filename1[]="./tests/output/test1.json";
const char filename2[]="./tests/input/testIn1.json";
const char filename3[]="./tests/output/test3.json";
const char filename4[]="./tests/input/test4.csv";
const char filename5[]="./tests/output/test4.json";

void testAdd(Tester* t)
{
    int val_int=3;
    float val_float=2.0f;
    serializer::Object obj;

    obj=val_int;

    int obtained= obj;

    t->assert_eq(val_int,obtained,"set integer");

    obj=2.0f;

    float obtained_f= obj;
    t->assert_eq(obtained_f,val_float,"set float");

}

void testObjDump(Tester* t)
{
    serializer::Object obj;
    obj["val1"]=integer;
    obj["val2"]=f;
    auto& val3 = obj["val3"];
    val3["subval1"]=str;
    val3["subval2"]=bol;
    val3["subval3"][0]=integer;
    val3["subval3"][1]=f;
    obj["subval4"][0] = val3;
    
    serializer::json::dump(obj,filename1);
    t->assert_true(true,"test1.json dumped");
}

void testObjParse(Tester* t)
{
    serializer::Object obj = serializer::json::parse(filename1);
    t->assert_true(true,"test1.json parsed");

    obj = serializer::json::parse(filename2);
    t->assert_true(true,"test2.json parsed");
}

void testIdenpotent(Tester* t)
{
    serializer::Object obj = serializer::json::parse(filename1);
    serializer::json::dump(obj,filename3);
    std::fstream f1(filename3);
    std::fstream f2(filename1);

    std::stringstream str1;
    std::stringstream str2;
    str1 << f1.rdbuf();
    str2 << f2.rdbuf();
    t->assert_true(str1.str()==str2.str(),"parse dump identpotent"); 

}

void testCsv(Tester* t)
{
    serializer::Object obj = serializer::csv::parse(filename4);

    serializer::json::dump(obj,filename5);
    t->assert_true(true, "changed csv to json correctly");
}

int main()
{
    Tester t("Serializer test");
    t.test(testAdd,"add");
    t.test(testObjDump,"dump");
    t.test(testObjParse,"parse");
    t.test(testIdenpotent,"parse+dump identpotent");
    t.test(testCsv,"csv");
    return t.returnValue();
}