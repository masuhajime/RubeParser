#pragma once

#include <stdio.h>
#include <vector>
#include "cocos2d.h"
#include "RubeFixture.hpp"

class RubeFixturePolygon : public RubeFixture
{
    CC_SYNTHESIZE(std::vector<cocos2d::Vec2>, vertices, Vertices);
public:
    
    void addVertex(cocos2d::Vec2 vertex);
    
    virtual RubeFixture::TYPE_FIXTURE getType();
    
    cocos2d::PhysicsShapePolygon* getShape(float scale = 1.0f);
    
    virtual ~RubeFixturePolygon();
};