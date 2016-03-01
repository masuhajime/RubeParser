#include "RubeCustomProperty.hpp"

bool RubeCustomProperty::hasCustomPropertyKey(const char* key) {
    return 0 < this->customProperties.count(key);
};

int RubeCustomProperty::getCustomPropertyAsInt(const char* key) {
    return this->customProperties.at(key).asInt();
};

int RubeCustomProperty::getCustomPropertyAsInt(const char* key, int def) {
    if (this->hasCustomPropertyKey(key)) {
        return this->getCustomPropertyAsInt(key);
    }
    return def;
};

std::string RubeCustomProperty::getCustomPropertyAsString(const char* key) {
    return this->customProperties.at(key).asString();
};

std::string RubeCustomProperty::getCustomPropertyAsString(const char* key, std::string def) {
    if (this->hasCustomPropertyKey(key)) {
        return this->getCustomPropertyAsString(key);
    }
    return def;
};

bool RubeCustomProperty::isCustomProperty(const char* key, std::string value) {
    if (!this->hasCustomPropertyKey(key)) {
        return false;
    }
    return 0 == this->getCustomPropertyAsString(key).compare(value);
};

bool RubeCustomProperty::isCustomProperty(const char* key, int value) {
    if (!this->hasCustomPropertyKey(key)) {
        return false;
    }
    return value == this->getCustomPropertyAsInt(key);
};

void RubeCustomProperty::setCustomProperty(const char* key, cocos2d::Value value) {
    this->customProperties[key] = value;
}
