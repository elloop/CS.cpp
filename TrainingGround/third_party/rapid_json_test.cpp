#include "inc.h"
#include "rapidjson/reader.h"
#include "FileReader.h"

#include <string>

NS_BEGIN(elloop);

BEGIN_TEST(RapidJson, Read, @);

unsigned long fileSize(0);
std::string jsonName("chinese.lang");
unsigned char * jsonData = FileReader::getInstance()->getFileData(jsonName, "r", &fileSize);
EL_SAFE_DELETE_ARRAY(jsonData);
std::string jsonString();

END_TEST;



NS_END(elloop);