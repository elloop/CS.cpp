
#include "Dictionary.h"
#include "FileReader.h"
#include "jsoncpp/json.h"

Dictionary* Dictionary::instance_ = nullptr;

void Dictionary::init( const std::string& languagefile )
{
	parseFromFile(languagefile);

// 	cocos2d::extension::CCNodeLoaderLibrary* lib = cocos2d::extension::CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
// 	lib->unregisterCCNodeLoader("CCLabelBMFont");
// 	lib->unregisterCCNodeLoader("CCLabelTTF");
// 	lib->registerCCNodeLoader("CCLabelBMFont", CCLabelBMFontLoader_Language::loader());
// 	lib->registerCCNodeLoader("CCLabelTTF", CCLabelTTFLoader_Language::loader());
}

void Dictionary::parseFromFile( const std::string& languagefile )
{
	Json::Reader jreader;
	Json::Value data;
	unsigned long filesize;

    using elloop::FileReader;
	char* pBuffer = (char*)FileReader::getInstance()->getFileData(languagefile, "rt", &filesize);

	if(!pBuffer)
	{
		char msg[256];
		sprintf(msg,"Failed open file: %s!\n",languagefile.c_str());
        LOGD(msg);
	}
	else
	{
		unsigned char* dataPtr = (unsigned char*)pBuffer;
		if (filesize >= 2 && dataPtr[0] == 0xFF && dataPtr[1] == 0xFE)
			jreader.parse(pBuffer+2,data,false);
		else if (filesize >= 3 && dataPtr[0] == 0xEF && dataPtr[1] == 0xBB && dataPtr[1] == 0xBF)
			jreader.parse(pBuffer+3,data,false);
		else
			jreader.parse(pBuffer,data,false);

		EL_SAFE_DELETE_ARRAY(pBuffer);

		if(data["version"].asInt()==1)
		{
			Json::Value files = data["strings"];
			if(!files.empty() && files.isArray())
			{
				for(int i = 0;i < files.size();++i)
				{
					Json::Value unit = files[i];
					if(unit["k"].empty()) continue;
					std::string key = unit["k"].asString();
					std::string value = unit["v"].asString();
					replaceEnter(key);
					if(mStrings.find(key)==mStrings.end()) {
                        mStrings.insert(std::make_pair(key, value));
                    }
					else
					{
                        LOGD("duplicate key found: %s\n", key.c_str());
					}
				}
			}
		}
	}
    EL_SAFE_DELETE_ARRAY(pBuffer);
}

const std::string & Dictionary::getValue( const std::string& key )
{
	auto it = mStrings.find(key);
	if(it!=mStrings.end())
		return it->second;
	else
		return key;
}

bool Dictionary::hasKey( const std::string& _key )
{
	std::map<std::string,std::string>::iterator it = mStrings.find(_key);
	return (it!=mStrings.end());
}

void Dictionary::replaceEnter( std::string &_str )
{
	if(_str.find_first_of('\r')==std::string::npos && _str.find_first_of('\n')==std::string::npos)
		return;

	std::string ret;
	for(std::string::size_type i=0;i<_str.size();++i)
	{
		if(_str[i]!='\r'&&_str[i]!='\n')
			ret+=_str[i];
	}
	_str = ret;
}

void Dictionary::clear()
{
	mStrings.clear();
}

Dictionary* Dictionary::getInstance()
{
    if (!instance_) {
        instance_ = new Dictionary();
    }
    return instance_;
}

void Dictionary::purge() {
    //TODO:  need i clear the map, before delete this object?
    clear();
    clearHash();
    clearKeys();
    clearSmartKeys();

    EL_SAFE_DELETE(instance_);
}

void Dictionary::parseFromFileWithHash(const std::string& languagefile) {
    Json::Reader    jreader;
    Json::Value     data;
    unsigned long   filesize;

    using elloop::FileReader;

    char* pBuffer = (char*)FileReader::getInstance()->getFileData(languagefile, "rt", &filesize);

    if (!pBuffer) {
        char msg[256];
        sprintf(msg, "Failed open file: %s!\n", languagefile.c_str());
        LOGD(msg);
    }
    else {
        unsigned char* dataPtr = (unsigned char*)pBuffer;
        if (filesize >= 2 && dataPtr[0] == 0xFF && dataPtr[1] == 0xFE)
            jreader.parse(pBuffer + 2, data, false);
        else if (filesize >= 3 && dataPtr[0] == 0xEF && dataPtr[1] == 0xBB && dataPtr[1] == 0xBF)
            jreader.parse(pBuffer + 3, data, false);
        else
            jreader.parse(pBuffer, data, false);

        EL_SAFE_DELETE_ARRAY(pBuffer);

        if (data["version"].asInt() == 1) {
            Json::Value files = data["strings"];
            if (!files.empty() && files.isArray()) {
                for (int i = 0; i < files.size(); ++i) {
                    Json::Value unit = files[i];
                    if (unit["k"].empty()) continue;
                    std::string key = unit["k"].asString();
                    std::string value = unit["v"].asString();
                    replaceEnter(key);
                    if (dict_.find(key) == dict_.end()) {
                        dict_.insert({key, value});
                    }
                    else {
                        LOGD("duplicate key found: %s\n", key.c_str());
                    }
                }
            }
        }
    }
    EL_SAFE_DELETE_ARRAY(pBuffer);
}

void Dictionary::clearHash() {
    dict_.clear();
}

void Dictionary::initWithHash(const std::string& languageFile) {
    parseFromFileWithHash(languageFile);
}

const std::string & Dictionary::getValueFromHash(const std::string& key) {
    auto it = dict_.find(key);
    if (it != dict_.end())
        return it->second;
    else
        return key;
}

void Dictionary::parseKeys(const std::string& languagefile) {
    Json::Reader jreader;
    Json::Value data;
    unsigned long filesize;

    using elloop::FileReader;
    char* pBuffer = (char*)FileReader::getInstance()->getFileData(languagefile, "rt", &filesize);

    if (!pBuffer) {
        char msg[256];
        sprintf(msg, "Failed open file: %s!\n", languagefile.c_str());
        LOGD(msg);
    }
    else {
        unsigned char* dataPtr = (unsigned char*)pBuffer;
        if (filesize >= 2 && dataPtr[0] == 0xFF && dataPtr[1] == 0xFE)
            jreader.parse(pBuffer + 2, data, false);
        else if (filesize >= 3 && dataPtr[0] == 0xEF && dataPtr[1] == 0xBB && dataPtr[1] == 0xBF)
            jreader.parse(pBuffer + 3, data, false);
        else
            jreader.parse(pBuffer, data, false);

        EL_SAFE_DELETE_ARRAY(pBuffer);

        size_t keyCount(0);
        if (data["version"].asInt() == 1) {
            Json::Value files = data["strings"];
            if (!files.empty() && files.isArray()) {
                for (int i = 0; i < files.size(); ++i) {
                    Json::Value unit = files[i];
                    if (unit["k"].empty()) continue;
                    std::string key     = unit["k"].asString();
                    std::string value   = unit["v"].asString();
                    replaceEnter(key);
                    if (!keys_) {
                        numOfKeys_  = files.size();
                        keys_       = new std::string*[numOfKeys_];
                    }
                    keys_[keyCount++]   = new std::string(key);
                    numOfKeys_          = keyCount;
                }
            }
        }
    }
    EL_SAFE_DELETE_ARRAY(pBuffer);
}

void Dictionary::clearKeys() {
    if (!keys_) {
        return;
    }
    for (size_t i = 0; i < numOfKeys_; ++i) {
        LOGD("releasing %d th string in keys_\n", i + 1);
        EL_SAFE_DELETE(keys_[i]);
    }
    EL_SAFE_DELETE_ARRAY(keys_);
}

void Dictionary::parseKeysWithSmartPtr(const std::string& languagefile) {
    Json::Reader jreader;
    Json::Value data;
    unsigned long filesize;

    using elloop::FileReader;
    char* pBuffer = (char*)FileReader::getInstance()->getFileData(languagefile, "rt", &filesize);

    if (!pBuffer) {
        char msg[256];
        sprintf(msg, "Failed open file: %s!\n", languagefile.c_str());
        LOGD(msg);
    }
    else {
        unsigned char* dataPtr = (unsigned char*)pBuffer;
        if (filesize >= 2 && dataPtr[0] == 0xFF && dataPtr[1] == 0xFE)
            jreader.parse(pBuffer + 2, data, false);
        else if (filesize >= 3 && dataPtr[0] == 0xEF && dataPtr[1] == 0xBB && dataPtr[1] == 0xBF)
            jreader.parse(pBuffer + 3, data, false);
        else
            jreader.parse(pBuffer, data, false);

        EL_SAFE_DELETE_ARRAY(pBuffer);

        size_t keyCount(0);
        if (data["version"].asInt() == 1) {
            Json::Value files = data["strings"];
            if (!files.empty() && files.isArray()) {
                for (int i = 0; i < files.size(); ++i) {
                    Json::Value unit = files[i];
                    if (unit["k"].empty()) continue;
                    std::string key = unit["k"].asString();
                    std::string value = unit["v"].asString();
                    replaceEnter(key);
                    if (!smartKeys_) {
                        numOfKeys_ = files.size();
                        smartKeys_ = new std::shared_ptr<StringWrapper>[numOfKeys_];
                        for (int i=0; i<numOfKeys_; ++i) {
                            smartKeys_[i] = nullptr;
                        }
                    }
                    smartKeys_[i] = std::make_shared<StringWrapper>(key);
                }
            }
        }
    }
    EL_SAFE_DELETE_ARRAY(pBuffer);
}

void Dictionary::clearSmartKeys() {
    if (!smartKeys_) {
        return;
    }
    EL_SAFE_DELETE_ARRAY(smartKeys_);
}

