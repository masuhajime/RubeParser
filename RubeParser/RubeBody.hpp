#pragma once

#include <stdio.h>
#include <vector>
#include "cocos2d.h"

#include "RubeFixture.hpp"
#include "RubeImageManager.hpp"
class RubeImageManager;

class RubeBody
{
    CC_SYNTHESIZE(cocos2d::Vec2, offset, Offset);
    CC_SYNTHESIZE(float, scale, Scale);
    CC_SYNTHESIZE(int, indexBody, IndexBody);
    CC_SYNTHESIZE(int, indexImage, IndexImage);
    
    // Rube properties
    CC_SYNTHESIZE(std::string, name, Name);
    CC_SYNTHESIZE(float, angle, Angle);
    CC_SYNTHESIZE(cocos2d::Vec2, position, Position);
    CC_SYNTHESIZE(int, bodyType, BodyType);
    CC_SYNTHESIZE(bool, rotationEnable, RotationEnable);
private:
    std::vector<RubeFixture*> fixtures;
    
public:
    RubeBody();
    
    void addFixture(RubeFixture* fixture);
    
    const std::vector<RubeFixture*>* getFixtures();
    
    cocos2d::Node* createNode();
    
    cocos2d::Node* createNodeSprite(RubeImageManager* rubeImageManager);
    
    cocos2d::Node* createSpriteIfHasImage(RubeImageManager* rubeImageManager);
    
    cocos2d::PhysicsBody* createPhysicsBody();
    
    ~RubeBody();
};
