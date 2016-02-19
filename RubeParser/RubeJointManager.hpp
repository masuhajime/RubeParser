#pragma once

#include "cocos2d.h"
#include "RubeObject.hpp"
class RubeObject;
#include "RubeJoint.hpp"
class RubeJoint;

USING_NS_CC;

class RubeJointManager
{
    CC_SYNTHESIZE(RubeObject*, rubeObject, RubeObject);
private:
    std::vector<RubeJoint*> joints;
public:
    
    int size();
    
    RubeJoint* getAt(int index);
    
    void add(RubeJoint* joint);
    
    std::vector<cocos2d::PhysicsJoint*> createJointAt(int index);
    
    ~RubeJointManager();
};
