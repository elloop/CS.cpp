#pragma once
#include "inc.h"
#include <string>
#include <map>
#include <unordered_map>
#include <memory>

class Dictionary
{
public:
    typedef std::unordered_map<std::string, std::string> Dict;
    class StringWrapper {
    public:
        StringWrapper(const std::string& str = "") : str_(str) {
        }
        ~StringWrapper() {
            elloop::pln("~StringWrapper()");
        }

        std::string str_;
    };

	void init(const std::string& languagefile);
    void initWithHash(const std::string& languageFile);
    void parseFromFile(const std::string& languagefile);
    void parseFromFileWithHash(const std::string& languagefile);
	bool hasKey(const std::string& key);
    const std::string & getValue(const std::string& key);
    const std::string & getValueFromHash(const std::string& key);

	void clear();
    void clearHash();

	static Dictionary*              getInstance();
    void                            purge();

    void                            parseKeys(const std::string& languagefile);
    void                            parseKeysWithSmartPtr(const std::string& languagefile);
    

    void                            clearKeys();
    void                            clearSmartKeys();
    std::string**                   keys() const { return keys_; }
    std::shared_ptr<StringWrapper>* smartKeys() const { return smartKeys_; }
    int                             numOfKeys() const { return numOfKeys_;}

    

private:
    Dictionary() : 
        keys_(nullptr),
        numOfKeys_(0),
        smartKeys_(nullptr) 
    {
        //parseKeys("chinese.lang");
        parseKeysWithSmartPtr("chinese.lang");
    }
    ~Dictionary() { 
        elloop::pln("~Dictionary()");
    }


    std::map<std::string, std::string>  mStrings;
    Dict                                dict_;
    static Dictionary*                  instance_;
    std::string**                       keys_;
    int                                 numOfKeys_;
    std::shared_ptr<StringWrapper>*     smartKeys_;

    void replaceEnter(std::string &_str);
};
