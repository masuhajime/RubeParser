#include "RubeBodyManager.hpp"
#include "RubeBody.hpp"
#include "RubeObject.hpp"


void RubeBodyManager::createBodyInto(cocos2d::Node* node, const char* bodyName)
{
    auto imageManager = this->getRubeObject()->getImageManager();
    auto rubeBody = this->findBodyByName(bodyName);
    rubeBody->setScale(rubeObject->getScale());
    rubeBody->setOffset(rubeObject->getOffset());
    rubeBody->createSpriteInto(node, imageManager);
    node->addComponent(rubeBody->createPhysicsBody());
    node->setName(rubeBody->getName());
    bodyNodes[rubeBody->getIndexBody()] = node;
}

cocos2d::Node* RubeBodyManager::createNodeFromBody(RubeBody* rubeBody)
{
    auto imageManager = this->getRubeObject()->getImageManager();
    rubeBody->setScale(rubeObject->getScale());
    rubeBody->setOffset(rubeObject->getOffset());
    auto node = rubeBody->createNodeWithSprite(imageManager);
    PhysicsBody* physicsBody = rubeBody->createPhysicsBody();
    if (nullptr != physicsBody) {
        node->addComponent(physicsBody);
    }
    node->setName(rubeBody->getName());
    bodyNodes[rubeBody->getIndexBody()] = node;
    return node;
}

cocos2d::Node* RubeBodyManager::createNodeWithSpriteAt(int index)
{
    return this->createNodeFromBody(this->bodies[index]);
}

int RubeBodyManager::size() {
    return (int)bodies.size();
}

cocos2d::Node* RubeBodyManager::getNodeAt(int index) {
    return this->bodyNodes[index];
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

RubeBody* RubeBodyManager::findBodyByName(const char* bodyName)
{
    int size = this->size();
    for (int i = 0; i < size; i++) {
        auto body = this->bodies[i];
        if (body->isName(bodyName)) {
            return body;
        }
    }
    log("body name:%s not found", bodyName);
    return nullptr;
}


void RubeBodyManager::each(std::function<void(RubeBody* body, cocos2d::Node* node)> function) {
    int countBodies = this->bodies.size();
    int countBodyNodes = this->bodyNodes.size();
    if (countBodies != countBodyNodes) {
        log("count mismatch on RubeBodyManager::each(%d != %d)", countBodies, countBodyNodes);
        return;
    }
    for (int i = 0; i < countBodies; ++i) {
        function(
             this->bodies[i],
             this->bodyNodes[i]
        );
    }
}

cocos2d::Node* RubeBodyManager::createNodeWithSpriteByName(const char* bodyName)
{
    auto body = this->findBodyByName(bodyName);
    if (nullptr == body) {
        return nullptr;
    }
    return this->createNodeFromBody(body);
}

RubeBodyManager::~RubeBodyManager() {
    for (auto body : bodies) {
        delete body;
    }
    bodies.clear();
}