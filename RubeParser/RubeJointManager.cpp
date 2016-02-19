#include "RubeJointManager.hpp"
#include "RubeObject.hpp"

std::vector<cocos2d::PhysicsJoint*> RubeJointManager::createJointAt(int index)
{
    auto joint = this->joints[index];
    return joint->createJoint(
                              this->getRubeObject()->getBodyManager(),
                              this->getRubeObject()->getScale()
                              );
    /*
    std::vector<cocos2d::PhysicsJoint*> joints;
    auto joint = this->joints[index];
    auto bodyManager = this->getRubeObject()->getBodyManager();
    float scale = this->getRubeObject()->getScale();
    auto nodeA = bodyManager->getNodeAt(joint->getBodyA());
    auto nodeB = bodyManager->getNodeAt(joint->getBodyB());
    auto createdJoint = PhysicsJointPin::construct(
                               nodeA->getPhysicsBody(),
                               nodeB->getPhysicsBody(),
                               joint->getAnchorA() * scale,
                               joint->getAnchorB() * scale);
    createdJoint->setCollisionEnable(false);
    createdJoint->setEnable(true);
    joints.push_back(createdJoint);
    return joints;
     */
}

int RubeJointManager::size() {
    return joints.size();
}

RubeJoint* RubeJointManager::getAt(int index) {
    return this->joints[index];
}

void RubeJointManager::add(RubeJoint* joint) {
    joints.push_back(joint);
}

RubeJointManager::~RubeJointManager() {
    for (auto joint : joints) {
        delete joint;
    }
    joints.clear();
}