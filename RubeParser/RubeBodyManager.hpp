#pragma once

#include "cocos2d.h"
#include "RubeObject.hpp"
class RubeObject;
#include "RubeBody.hpp"
class RubeBody;

USING_NS_CC;


class RubeBodyManager
{
    CC_SYNTHESIZE(RubeObject*, rubeObject, RubeObject);
private:
    std::vector<RubeBody*> bodies;
    // jointを繋げるために利用するポインタを持っておく
    std::vector<cocos2d::Node*> bodyNodes;
public:
    
    int size();
    
    void add(RubeBody* body);
    
    RubeBody* getAt(int index);
    
    cocos2d::Node* getNodeAt(int index);
    
    cocos2d::Node* createNodeAt(int index);
    
    cocos2d::Node* createNodeWithSpriteAt(int index);
    
    ~RubeBodyManager();
};
