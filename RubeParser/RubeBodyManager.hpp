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
    
    cocos2d::Node* createNodeFromBody(RubeBody* rubeBody);
    
    /**
     * RubeParse内で std::vector<int> RubeBody::imageIndexes に
     * indexを追加するために利用する
     */
    RubeBody* getAt(int index);
    
    /**
     * RubeJointに Node* を渡す為に利用する
     */
    cocos2d::Node* getNodeAt(int index);
    
    /**
     *
     */
    cocos2d::Node* createNodeWithSpriteAt(int index);
    
    /**
     *
     */
    cocos2d::Node* createNodeWithSpriteByName(const char* bodyName);
    
    void createBodyInto(cocos2d::Node* node, const char* bodyName);
    RubeBody* findBodyByName(const char* bodyName);
    
    ~RubeBodyManager();
};
