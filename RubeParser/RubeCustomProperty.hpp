#pragma once

#include <unordered_map>

#include "cocos2d.h"
USING_NS_CC;

class RubeCustomProperty
{
private:
    std::unordered_map<std::string, cocos2d::Value> customProperties;
public:
    bool hasCustomPropertyKey(const char* key);
    
    int getCustomPropertyAsInt(const char* key);
    int getCustomPropertyAsInt(const char* key, int def);
    
    std::string getCustomPropertyAsString(const char* key);
    std::string getCustomPropertyAsString(const char* key, std::string def);
    
    bool isCustomProperty(const char* key, std::string value);
    bool isCustomProperty(const char* key, int value);
    
    void setCustomProperty(const char* key, cocos2d::Value value);
};
