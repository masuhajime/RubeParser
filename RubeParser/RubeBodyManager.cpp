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
    return (int)bodies.size();
}

void RubeBodyManager::add(RubeBody* body) {
    // bodyのNode*を格納するために vectorのサイズを拡張
    bodyNodes.resize((int)bodies.size() + 1);
    bodyNodes[(int)bodies.size()] = nullptr;
    body->setIndexBody(this->size());
    bodies.push_back(body);
}

RubeBody* RubeBodyManager::getAt(int index) {
    return this->bodies[index];
}

cocos2d::Node* RubeBodyManager::getNodeAt(int index) {
    return this->bodyNodes[index];
}

cocos2d::Node* RubeBodyManager::createNodeWithSpriteByName(const char* bodyName)
{
    int size = this->size();
    for (int i = 0; i < size; i++) {
        auto body = this->bodies[i];
        if (body->isName(bodyName)) {
            //return body->createNodeWithSprite(this->getRubeObject()->getImageManager());
            return this->createNodeWithSpriteAt(body->getIndexBody());
        }
    }
    log("body name:%s not found", bodyName);
    return nullptr;
}

RubeBodyManager::~RubeBodyManager() {
    for (auto body : bodies) {
        delete body;
    }
    bodies.clear();
}