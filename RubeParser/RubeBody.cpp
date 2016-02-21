#include "RubeBody.hpp"

RubeBody::RubeBody(){};

void RubeBody::addFixture(RubeFixture* fixture) {
    fixtures.push_back(fixture);
}

const std::vector<RubeFixture*>* RubeBody::getFixtures() {
    return &fixtures;
}

cocos2d::Node* RubeBody::createNode() {
    auto node = cocos2d::Node::create();
    node->setPosition((this->position * scale) + offset);
    return node;
}

cocos2d::Node* RubeBody::createNodeWithSprite(RubeImageManager* rubeImageManager) {
    auto node = this->createNode();
    for (auto imageIndex : imageIndexes) {
        auto sprite = rubeImageManager->createSpriteAt(imageIndex);
        node->addChild(sprite);
    }
    return node;
}


void RubeBody::addImageIndex(int imageIndex) {
    this->imageIndexes.push_back(imageIndex);
}


cocos2d::PhysicsBody* RubeBody::createPhysicsBody() {
    auto pb = cocos2d::PhysicsBody::create();
    pb->setRotationEnable(this->getRotationEnable());
    if (this->getBodyType() == 0) { //0 = static, 1 = kinematic, 2 = dynamic
        pb->setDynamic(false);
    }
    for (auto fixture: fixtures) {
        auto shape = fixture->getShape(this->scale);
        pb->addShape(shape);
    }
    
    return pb;
}

RubeBody::~RubeBody() {
    for (auto fixture: fixtures) {
        delete fixture;
    }
    fixtures.clear();
}