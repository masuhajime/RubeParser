#pragma once

#include "cocos2d.h"
#include "RubeBodyManager.hpp"

USING_NS_CC;

class RubeJoint
{
    // joint properties
    CC_SYNTHESIZE(std::string, name, Name);
    CC_SYNTHESIZE(cocos2d::Vec2, anchorA, AnchorA);
    CC_SYNTHESIZE(cocos2d::Vec2, anchorB, AnchorB);
    CC_SYNTHESIZE(int, bodyA, BodyA);
    CC_SYNTHESIZE(int, bodyB, BodyB);
public:
    enum class TYPE_JOINT : int {
        REVOLUTE,// pin joint
    };
    
    virtual RubeJoint::TYPE_JOINT getType() = 0;
    
    virtual ~RubeJoint(){};
    
    virtual std::vector<cocos2d::PhysicsJoint*> createJoint(RubeBodyManager* bodyManager, float scale) = 0;
};
