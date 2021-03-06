#pragma once

#include "cocos2d.h"
#include "RubeObject.hpp"
class RubeObject;
#include "RubeImage.hpp"

USING_NS_CC;

class RubeImageManager
{
    CC_SYNTHESIZE(RubeObject*, rubeObject, RubeObject);
    CC_SYNTHESIZE(std::string, pathDirectoryRubeJson, PathDirectoryRubeJson);
private:
    std::vector<RubeImage*> images;
    
public:
    int size();
    
    RubeImage* getAt(int index);
    
    void add(RubeImage* image);
    
    cocos2d::Sprite* createSpriteAt(int index);
    
    ~RubeImageManager();
};
