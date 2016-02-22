#include "RubeObject.hpp"

RubeObject::RubeObject() {
    bodyManager = new RubeBodyManager();
    bodyManager->setRubeObject(this);
    jointManager = new RubeJointManager();
    jointManager->setRubeObject(this);
    imageManager = new RubeImageManager();
    imageManager->setRubeObject(this);
};

cocos2d::Node* RubeObject::createByName(const char* name) {
    return this->bodyManager->createNodeWithSpriteByName(name);
}

void RubeObject::setPathDirectoryRubeJson(std::string directoryPath) {
    this->imageManager->setPathDirectoryRubeJson(directoryPath);
}

void RubeObject::addBody(RubeBody* body) {
    this->bodyManager->add(body);
}

void RubeObject::addJoint(RubeJoint* joint) {
    this->jointManager->add(joint);
}

void RubeObject::addImage(RubeImage* image) {
    this->imageManager->add(image);
}

RubeObject::~RubeObject() {
    delete bodyManager;
    delete jointManager;
    delete imageManager;
}

