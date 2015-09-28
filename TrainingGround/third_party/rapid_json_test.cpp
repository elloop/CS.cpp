#include "rapid_json_test.h"
#include "rapidjson/reader.h"
#include "rapidjson/document.h"
#include "FileReader.h"
#include <fstream>
#include <iostream>

#include <string>

NS_BEGIN(elloop);
NS_BEGIN(third_party);


BEGIN_TEST(RapidJson, Read, @);


#if 1
    return;
#endif

unsigned long fileSize(0);
std::string jsonName("chinese.lang");
unsigned char * jsonData = FileReader::getInstance()->getFileData(jsonName, "rt", &fileSize);
//jsonData[fileSize - 1] = 0;
std::string jsonString((char*)(jsonData), fileSize);
//p(jsonString);

using std::ifstream;

std::string stringFromStream;
ifstream in;
in.open("chinese.lang", ifstream::in);
if (in.is_open()) {
    std::string line;
    while (in >> line) {
        stringFromStream.append(line + "\n");
    }
    in.close();
}
//p(stringFromStream);

using rapidjson::Document;

const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
printf("Original JSON:\n %s\n", json);

Document doc;

char* buff = new char[fileSize];
//memcpy(buff, stringFromStream.c_str(), stringFromStream.size());
//memcpy(buff, json, sizeof(json));

memcpy(buff, jsonData, fileSize);

auto freeMem = [&buff, &jsonData](){ 
    EL_SAFE_DELETE_ARRAY(buff);
    EL_SAFE_DELETE_ARRAY(jsonData);
};
do {
    if (doc.ParseInsitu(buff).HasParseError()) {
        break;
    }
    assertCond(doc.IsObject(),          freeMem);
    assertCond(doc.HasMember("hello"),  freeMem);
    assertCond(doc.HasMember("t"),      freeMem);
} while (0);

freeMem();



END_TEST;


//---------------------- test seperator ----------------------

BEGIN_TEST(RapidJson, SimpleReader, @);

#if 1
    return;
#endif

using std::cout;
using std::endl;
using std::boolalpha;
using rapidjson::SizeType;
using rapidjson::Reader;
using rapidjson::StringStream;

struct MyHandler {
    bool Null() { cout << "Null()" << endl; return true; }
    bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
    bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
    bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
    bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
    bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
    bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
    bool String(const char* str, SizeType length, bool copy) {
        cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool StartObject() { cout << "StartObject()" << endl; return true; }
    bool Key(const char* str, SizeType length, bool copy) {
        cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
    bool StartArray() { cout << "StartArray()" << endl; return true; }
    bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
};

unsigned long fileSize(0);
std::string jsonName("chinese.lang");
unsigned char * jsonData = FileReader::getInstance()->getFileData(jsonName, "rt", &fileSize);

MyHandler handler;
Reader reader;
StringStream ss((char*)jsonData);
reader.Parse(ss, handler);

EL_SAFE_DELETE_ARRAY(jsonData);

END_TEST;


//---------------------- test seperator ----------------------
BEGIN_TEST(RapidJson, SimpleDom, @);

using std::cout;
using std::endl;
using std::boolalpha;
using rapidjson::SizeType;
using rapidjson::Reader;
using rapidjson::StringStream;
using rapidjson::Document;
using rapidjson::Value;

unsigned long fileSize(0);
std::string jsonName("chinese.lang");
unsigned char * jsonData = FileReader::getInstance()->getFileData(jsonName, "rt", &fileSize);
EL_SAFE_DELETE_ARRAY(jsonData);


using std::ifstream;

ifstream in;
in.open("chinese.lang", ifstream::in);
std::string str;
if (in.is_open()) {
    std::string line;
    while (getline(in, line)) {
        str.append(line + "\n");
    }
    in.close();
}
psln(str);
Document d;
//d.Parse((char*)jsonData);
d.Parse(str.c_str());

Value& v = d["version"];
if (v.IsInt()) {
    psln(v.GetInt());
}

using util = RapidJsonUtil;


Value & ary = d["strings"];
if (ary.IsArray()) {
    for (size_t i=0; i<ary.Size(); ++i) {
        Value& v = ary[i];
        psln(util::getString(v, "k"));
        psln(util::getString(v, "v"));
    }
}

END_TEST;

NS_END(third_party);
NS_END(elloop);