#pragma once

#include <stdio.h>
#include <vector>
#include "cocos2d.h"

#include "RubeFixture.hpp"
#include "RubeImageManager.hpp"
#include "RubeCustomProperty.hpp"
class RubeImageManager;

class RubeBody : public RubeCustomProperty
{
    CC_SYNTHESIZE(cocos2d::Vec2, offset, Offset);
    CC_SYNTHESIZE(float, scale, Scale);
    CC_SYNTHESIZE(int, indexBody, IndexBody);
    
    // Rube properties
    CC_SYNTHESIZE(std::string, name, Name);
    CC_SYNTHESIZE(float, angle, Angle);
    CC_SYNTHESIZE(cocos2d::Vec2, position, Position);
    CC_SYNTHESIZE(int, bodyType, BodyType);
    CC_SYNTHESIZE(bool, rotationEnable, RotationEnable);
    
    CC_SYNTHESIZE(float, angularDamping, AngularDamping);
    CC_SYNTHESIZE(float, linearDamping, LinearDamping);
private:
    std::vector<RubeFixture*> fixtures;
    std::vector<int> imageIndexes;
    
public:
    RubeBody();
    
    void addImageIndex(int imageIndex);
    
    void addFixture(RubeFixture* fixture);
    
    const std::vector<RubeFixture*>* getFixtures();
    
    cocos2d::Node* createNode();
    cocos2d::Node* createNodeWithSprite(RubeImageManager* rubeImageManager);
    void createSpriteInto(cocos2d::Node* node, RubeImageManager* rubeImageManager);
    
    cocos2d::PhysicsBody* createPhysicsBody();
    
    bool isName(const char* name);
    
    cocos2d::Vec2 getPositionScaledAndOffset();
    
    ~RubeBody();
};
