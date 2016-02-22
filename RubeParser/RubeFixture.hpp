#pragma once

#include "cocos2d.h"

class RubeFixture
{
    CC_SYNTHESIZE(float, scale, Scale);
    
    CC_SYNTHESIZE(float, friction, Friction);
    CC_SYNTHESIZE(float, restitution, Restitution);
    CC_SYNTHESIZE(float, density, Density);
    
    CC_SYNTHESIZE(int, filterCategoryBits, FilterCategoryBits);
    CC_SYNTHESIZE(int, filterMaskBits, FilterMaskBits);
public:
    enum class TYPE_FIXTURE : int {
        CIRCLE,
        POLYGON,
    };
    
public:
    
    virtual cocos2d::PhysicsShape* getShape(float scale = 1.0f) = 0;
    
    virtual ~RubeFixture(){};
    
    virtual RubeFixture::TYPE_FIXTURE getType() = 0;
};