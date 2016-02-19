#include "RubeFixturePolygon.hpp"

void RubeFixturePolygon::addVertex(cocos2d::Vec2 vertex) {
    this->vertices.push_back(vertex);
}

RubeFixturePolygon::RubeFixture::TYPE_FIXTURE RubeFixturePolygon::getType() {
    return RubeFixture::TYPE_FIXTURE::POLYGON;
}

cocos2d::PhysicsShapePolygon* RubeFixturePolygon::getShape(float scale) {
    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        (*it) = (*it) * scale;
    }
    auto m = cocos2d::PHYSICSSHAPE_MATERIAL_DEFAULT;
    m.restitution = this->restitution;
    m.friction = this->friction;
    m.density = this->density;
    auto shape = cocos2d::PhysicsShapePolygon::create(
                                                      &vertices[0],
                                                      static_cast<int>(vertices.size()),
                                                      m
                                                      );
    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        (*it) = (*it) / scale;
    }
    return shape;
}

RubeFixturePolygon::~RubeFixturePolygon() {
}