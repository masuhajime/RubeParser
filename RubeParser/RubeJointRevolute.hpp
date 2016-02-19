#pragma once

#include "cocos2d.h"
#include "RubeJoint.hpp"
#include "RubeBodyManager.hpp"

USING_NS_CC;

class RubeJointRevolute : public RubeJoint
{
    CC_SYNTHESIZE(bool, enableLimit, EnableLimit);
    CC_SYNTHESIZE(float, lowerLimit, LowerLimit);
    CC_SYNTHESIZE(float, upperLimit, UpperLimit);
public:
    virtual RubeJoint::TYPE_JOINT getType() {
        return RubeJoint::TYPE_JOINT::REVOLUTE;
    }
    
    virtual std::vector<cocos2d::PhysicsJoint*> createJoint(RubeBodyManager* bodyManager, float scale);
};
