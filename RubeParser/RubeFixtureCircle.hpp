#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "RubeFixture.hpp"

class RubeFixtureCircle : public RubeFixture
{
    CC_SYNTHESIZE(cocos2d::Vec2, position, Position);
    CC_SYNTHESIZE(float, radius, Radius);
    
public:
    virtual RubeFixture::TYPE_FIXTURE getType();
    
    cocos2d::PhysicsShapeCircle* getShape(float scale = 1.0f);
    
    virtual ~RubeFixtureCircle();
};