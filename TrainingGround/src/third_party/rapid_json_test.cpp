#include "rapid_json_test.h"
#include "rapidjson/reader.h"
#include "rapidjson/document.h"
#include "util/FileReader.h"
#include <string>
#include <fstream>
#include <iostream>

NS_BEGIN(elloop);
NS_BEGIN(third_party);

// test.json content:
//{
//    "dictVersion": 1,
//    "content" :
//    [   
//      { "key": "word1", "value":  "单词1" },
//      { "key": "word2", "value" : "单词2" },
//      { "key": "word3", "value" : "单词3" },
//      { "key": "word4", "value" : "单词4" },
//      { "key": "word5", "value" : "单词5" }
//    ]
//}

//---------------------- begin of new test ----------------------
BEGIN_TEST(RapidJson, SimpleDomUseStreamContent, @);
//return;
using namespace std;
string      stringFromStream;
ifstream    in;
in.open("test.json", ifstream::in);
if (in.is_open()) {
    string line;
    while (getline(in, line)) {
        stringFromStream.append(line + "\n");
    }
    in.close();
}

using rapidjson::Document;
Document doc;
//parse from string is ok.
doc.Parse<0>(stringFromStream.c_str());
// doc.ParseInsitu((char*)stringFromStream.c_str()) // 原地解析
if (doc.HasParseError()) {
    rapidjson::ParseErrorCode code = doc.GetParseError();
    psln(code);
    return;
}

EXPECT_TRUE(doc.IsObject());
EXPECT_TRUE(doc.HasMember("dictVersion") && doc["dictVersion"].IsInt());
EXPECT_TRUE(doc.HasMember("content") && doc["content"].IsArray());
EXPECT_FALSE(doc.HasMember("hello"));

auto& v = doc["dictVersion"];       // v's type is rapidjson::Value
EXPECT_TRUE(v.IsInt());
EXPECT_EQ(1, v.GetInt());

using util = RapidJsonUtil;        // defined in rapid_json_test.h
auto & contents = doc["content"];
if (contents.IsArray()) {
    for (size_t i = 0; i < contents.Size(); ++i) {
        auto & v = contents[i];
        psln(util::getString(v, "key"));
        psln(util::getString(v, "value"));
    }
}

END_TEST;


//---------------------- begin of new test ----------------------
BEGIN_TEST(RapidJson, SimpleDomUseBinaryBuffer, @);
//return;
using namespace std;
unsigned long   fileSize(0);
unsigned char * jsonData = FileReader::getInstance()->getFileData(
                                "test.json", "rb", &fileSize);
// TODO: if i don't use "rb", i will get "屯屯屯屯屯屯" at 
// the end of jsonString. why?
string jsonString((const char*)(jsonData), fileSize);
EL_SAFE_DELETE_ARRAY(jsonData);

using rapidjson::Document;
Document doc;
//parse from string is ok.
//doc.Parse<0>(jsonString.c_str());
//if (doc.HasParseError()) {
//    rapidjson::ParseErrorCode code = doc.GetParseError();
//    psln(code);
//    return;
//}


// ParseInsitu from string is ok.
if (doc.ParseInsitu((char*)jsonString.c_str()).HasParseError()) {
    rapidjson::ParseErrorCode code = doc.GetParseError();
    psln(code);
    return;
}

/* parse from binary buffer failed.
doc.Parse<0>((const char*)jsonData);
if (doc.HasParseError()) {
    rapidjson::ParseErrorCode code = doc.GetParseError();
    psln(code);
    return;
}*/

/* parseInsitu (原地解析) binary buffer failed.
if (doc.ParseInsitu((char*)jsonData).HasParseError()) {
    rapidjson::ParseErrorCode code = doc.GetParseError();
    psln(code);
    return;
}*/

EXPECT_TRUE(doc.IsObject());
EXPECT_TRUE(doc.HasMember("dictVersion") && doc["dictVersion"].IsInt());
EXPECT_TRUE(doc.HasMember("content") && doc["content"].IsArray());
EXPECT_FALSE(doc.HasMember("hello"));

auto & v = doc["dictVersion"];      // v's type is rapidjson::Value
EXPECT_TRUE(v.IsInt());
EXPECT_EQ(1, v.GetInt());

using util = RapidJsonUtil;        // defined in rapid_json_test.h
auto & contents = doc["content"];
if (contents.IsArray()) {
    for (size_t i = 0; i < contents.Size(); ++i) {
        auto & v = contents[i];
        psln(util::getString(v, "key"));
        psln(util::getString(v, "value"));
    }
}
END_TEST;


//---------------------- begin of new test ----------------------
BEGIN_TEST(RapidJson, SimpleReader, @);

return;

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

unsigned long   fileSize(0);
// TODO: is "rt" ok ?
unsigned char * jsonData = FileReader::getInstance()->getFileData(
                            "test.json", "rt", &fileSize);

MyHandler   handler;
Reader      reader;
StringStream ss((char*)jsonData);
reader.Parse(ss, handler);

EL_SAFE_DELETE_ARRAY(jsonData);

END_TEST;


NS_END(third_party);
NS_END(elloop);