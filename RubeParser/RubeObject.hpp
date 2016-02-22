#pragma once

#include <stdio.h>
#include <vector>

#include "cocos2d.h"

#include "RubeBodyManager.hpp"
class RubeBodyManager;
#include "RubeJointManager.hpp"
class RubeJointManager;
#include "RubeImageManager.hpp"
class RubeImageManager;
#include "RubeBody.hpp"
#include "RubeJoint.hpp"
#include "RubeImage.hpp"

class RubeObject
{
    CC_SYNTHESIZE(float, scale, Scale);
    CC_SYNTHESIZE(cocos2d::Vec2, offset, Offset);
    CC_SYNTHESIZE(RubeBodyManager*, bodyManager, BodyManager);
    CC_SYNTHESIZE(RubeJointManager*, jointManager, JointManager);
    CC_SYNTHESIZE(RubeImageManager*, imageManager, ImageManager);
public:
    RubeObject();

    void setPathDirectoryRubeJson(std::string directoryPath);
    
    void addBody(RubeBody* body);
    
    void addJoint(RubeJoint* joint);
    
    void addImage(RubeImage* image);
    
    cocos2d::Node* createByName(const char* name);
    
    ~RubeObject();
};