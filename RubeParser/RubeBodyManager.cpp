#include "RubeBodyManager.hpp"
#include "RubeBody.hpp"
#include "RubeObject.hpp"

cocos2d::Node* RubeBodyManager::createNodeAt(int index)
{
    auto body = this->bodies[index];
    body->setScale(rubeObject->getScale());
    body->setOffset(rubeObject->getOffset());
    auto node = body->createNode();
    node->addComponent(body->createPhysicsBody());
    node->setName(body->getName());
    bodyNodes[index] = node;
    return node;
}

cocos2d::Node* RubeBodyManager::createNodeWithSpriteAt(int index)
{
    auto imageManager = this->getRubeObject()->getImageManager();
    auto body = this->bodies[index];
    body->setScale(rubeObject->getScale());
    body->setOffset(rubeObject->getOffset());
    auto node = body->createNodeWithSprite(imageManager);
    node->addComponent(body->createPhysicsBody());
    node->setName(body->getName());
    bodyNodes[index] = node;
    return node;
}

int RubeBodyManager::size() {
    return bodies.size();
}

void RubeBodyManager::add(RubeBody* body) {
    // bodyのNode*を格納するために vectorのサイズを拡張
    bodyNodes.resize((int)bodies.size() + 1);
    bodyNodes[(int)bodies.size()] = nullptr;
    body->setIndexBody(bodies.size());
    bodies.push_back(body);
}

RubeBody* RubeBodyManager::getAt(int index) {
    return this->bodies[index];
}

cocos2d::Node* RubeBodyManager::getNodeAt(int index) {
    return this->bodyNodes[index];
}

RubeBodyManager::~RubeBodyManager() {
    for (auto body : bodies) {
        delete body;
    }
    bodies.clear();
}