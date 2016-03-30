#include "RubeBody.hpp"

RubeBody::RubeBody():
offset(Vec2::ZERO),
scale(1),
indexBody(-1),
name(""),
angle(0),
position(Vec2::ZERO),
bodyType(0),
rotationEnable(true),
angularDamping(0.0f),
linearDamping(0.0f)
{};

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

void RubeBody::createSpriteInto(cocos2d::Node* node, RubeImageManager* rubeImageManager) {
    for (auto imageIndex : imageIndexes) {
        auto sprite = rubeImageManager->createSpriteAt(imageIndex);
        node->addChild(sprite);
    }
}

bool RubeBody::isName(const char* name) {
    return 0 == this->name.compare(name);
}

cocos2d::Vec2 RubeBody::getPositionScaledAndOffset() {
    return (this->position * scale) + offset;
}

void RubeBody::addImageIndex(int imageIndex) {
    this->imageIndexes.push_back(imageIndex);
}

cocos2d::PhysicsBody* RubeBody::createPhysicsBody() {
    if (0 == fixtures.size()) {
        return nullptr;
    }
    auto pb = cocos2d::PhysicsBody::create();
    pb->setRotationEnable(this->getRotationEnable());
    if (this->getBodyType() == 0) { //0 = static, 1 = kinematic, 2 = dynamic
        pb->setDynamic(false);
    }
    for (auto fixture: fixtures) {
        auto shape = fixture->getShape(this->scale);
        pb->addShape(shape);
    }
    pb->setLinearDamping(this->getLinearDamping());
    pb->setAngularDamping(this->getAngularDamping());
    //pb->setCollisionBitmask(1);
    //pb->setCategoryBitmask(1);
    
    return pb;
}

RubeBody::~RubeBody() {
    for (auto fixture: fixtures) {
        delete fixture;
    }
    fixtures.clear();
}