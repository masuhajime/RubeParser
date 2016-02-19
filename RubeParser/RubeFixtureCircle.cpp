#include "RubeFixtureCircle.hpp"

RubeFixture::TYPE_FIXTURE RubeFixtureCircle::getType() {
    return RubeFixture::TYPE_FIXTURE::CIRCLE;
}

cocos2d::PhysicsShapeCircle* RubeFixtureCircle::getShape(float scale) {
    auto m = cocos2d::PHYSICSSHAPE_MATERIAL_DEFAULT;
    m.restitution = this->restitution;
    m.friction = this->friction;
    m.density = this->density;
    auto shape = cocos2d::PhysicsShapeCircle::create(
                                                     this->radius * scale,
                                                     m,
                                                     this->position * scale// offset
                                                     );
    return shape;
}

RubeFixtureCircle::~RubeFixtureCircle() {
}