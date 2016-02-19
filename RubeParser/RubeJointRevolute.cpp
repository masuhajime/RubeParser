#include "RubeJointRevolute.hpp"

std::vector<cocos2d::PhysicsJoint*> RubeJointRevolute::createJoint(RubeBodyManager* bodyManager, float scale)
{
    std::vector<cocos2d::PhysicsJoint*> joints;
    auto nodeA = bodyManager->getNodeAt(this->getBodyA());
    auto nodeB = bodyManager->getNodeAt(this->getBodyB());
    {
        // pin joint
        auto createdJoint = PhysicsJointPin::construct(
                                                       nodeA->getPhysicsBody(),
                                                       nodeB->getPhysicsBody(),
                                                       this->getAnchorA() * scale,
                                                       this->getAnchorB() * scale);
        createdJoint->setCollisionEnable(false);
        joints.push_back(createdJoint);
    }
    if (this->getEnableLimit()) {
        // rotate limit joint
        auto createdJoint = PhysicsJointRotaryLimit::construct(
                                                            nodeA->getPhysicsBody(),
                                                            nodeB->getPhysicsBody(),
                                                            this->getLowerLimit(),
                                                            this->getUpperLimit()
        );
        createdJoint->setCollisionEnable(false);
        joints.push_back(createdJoint);
    }
    return joints;
}
