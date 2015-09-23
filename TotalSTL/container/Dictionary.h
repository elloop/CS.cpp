#pragma once
#include "inc.h"
#include <string>
#include <map>
#include <unordered_map>

class Dictionary
{
public:
    typedef std::unordered_map<std::string, std::string> Dict;

	void init(const std::string& languagefile);
    void initWithHash(const std::string& languageFile);
    void parseFromFile(const std::string& languagefile);
    void parseFromFileWithHash(const std::string& languagefile);
	bool hasKey(const std::string& key);
    const std::string & getValue(const std::string& key);
    const std::string & getValueFromHash(const std::string& key);

	void clear();
    void clearHash();

	static Dictionary* getInstance();
    void purge();

    void saveKeys(const std::string& languagefile);
    void clearKeys();
    std::string** keys() const { return keys_;}
    int numOfKeys() const { return numOfKeys_;}

private:
    Dictionary() : 
        keys_(nullptr),
        numOfKeys_(0) {
        saveKeys("chinese.lang");
    }
    ~Dictionary() { 
        elloop::pln("~Dictionary()");
    }


    std::map<std::string, std::string>  mStrings;
    Dict                                dict_;
    static Dictionary*                  instance_;
    std::string**                       keys_;
    int                                 numOfKeys_;

    void replaceEnter(std::string &_str);
};
