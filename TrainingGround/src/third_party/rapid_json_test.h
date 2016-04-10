#pragma once

#include "inc.h"
#include "rapidjson/document.h"
#include <string>

NS_BEGIN(elloop);
NS_BEGIN(third_party);


class RapidJsonUtil {
public:
    static const char * getString(rapidjson::Value& value, const std::string& key) {
        if (value.IsObject()) {
            if (value.HasMember(key.c_str()) && value[key.c_str()].IsString()) {
                return value[key.c_str()].GetString();
            }
        }
        return "";
        //return (value.HasMember(key.c_str()) && value[key.c_str()].IsString()) ? value[key.c_str()].IsString() : "";
    }

    /*static const char * getString(rapidjson::Value& value, const std::string& key) {
        return value.IsString() ? value.GetString() : "";
    }*/
};

NS_END(third_party);
NS_END(elloop);