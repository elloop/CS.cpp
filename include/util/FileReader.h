#pragma once

#include "inc.h"
#include <string>

NS_BEGIN(elloop);

class FileReader
{
public:
    unsigned char*      getFileData(const std::string& fileName, const char* mode, unsigned long * pSize);
    static FileReader*  getInstance();
    void purege();
private:
    FileReader() {}
    ~FileReader() {}
    static FileReader* instance_;
};


NS_END(elloop);