#include "util/FileReader.h"
#include <cstdio>

NS_BEGIN(elloop);

FileReader* FileReader::instance_ = nullptr;

FileReader* FileReader::getInstance()
{
    if (!instance_)
    {
        instance_ = new FileReader();
    }
    return instance_;
}

unsigned  char* FileReader::getFileData(const std::string& fileName, const char* mode, unsigned long * pSize)
{
    assert(!fileName.empty());
    unsigned char* res(nullptr);
    FILE * fp(nullptr);
    do
    {
        fp = fopen(fileName.c_str(), mode);
        EL_BREAK_IF(!fp);
        fseek(fp, 0, SEEK_END);
        unsigned long fileSize(0);
        if (!pSize)
        {
            fileSize = ftell(fp);
        }
        else
        {
            fileSize = *pSize = ftell(fp);
        }
        fseek(fp, 0, SEEK_SET);
        res = new unsigned char[fileSize];
        fread(res, sizeof (unsigned char), fileSize, fp);
        fclose(fp);
    }
    while (0);

    return res;
}

void FileReader::purege()
{
    EL_SAFE_DELETE(instance_);
}

NS_END(elloop);

