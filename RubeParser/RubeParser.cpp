#include "RubeParser.hpp"

#include "RubeFixturePolygon.hpp"
#include "RubeFixtureCircle.hpp"
#include "RubeJoint.hpp"
#include "RubeJointRevolute.hpp"
#include "RubeImage.hpp"

void RubeParser::parseTo(RubeObject* rubeObject, std::string filename) {
    auto filePath = FileUtils::getInstance()->fullPathForFilename(filename);
    std::string content = FileUtils::getInstance()->getStringFromFile(filePath);
    
    rapidjson::Document d;
    d.Parse<rapidjson::ParseFlag::kParseDefaultFlags>(content.c_str());
    
    RubeParser::parseBodiesTo(rubeObject, d);
    RubeParser::parseJointsTo(rubeObject, d);
    RubeParser::parseImagesTo(rubeObject, d);
    RubeParser::setImageIndexToBody(rubeObject);
};

void RubeParser::parseBodiesTo(RubeObject* rubeObject, rapidjson::Document& d) {
    if (!d.HasMember("body")) {
        return;
    }
    rapidjson::Value& bodies = d["body"];
    for (auto it = bodies.Begin(); it != bodies.End(); it++) {
        RubeParser::parseBodyTo(rubeObject, *it);
    }
}

void RubeParser::parseBodyTo(RubeObject* rubeObject, rapidjson::Value& value) {
    if (!value.HasMember("angle")
        || !value.HasMember("name")
        //|| !value.HasMember("fixture") // zero fixutre body not have fixture
        || !value.HasMember("type")
        || !value.HasMember("position")) {
        return;
    }
    RubeBody* body = new RubeBody();
    // name
    body->setName(value["name"].GetString());
    // type
    body->setBodyType(value["type"].GetInt());
    // angle
    body->setAngle(value["angle"].GetDouble());
    // rotation enable
    if (value.HasMember("fixedRotation")) {
        body->setRotationEnable(!value["fixedRotation"].GetBool());
    } else {
        body->setRotationEnable(true);
    }
    // position
    if (value.HasMember("position")) {
        body->setPosition(RubeParser::parseVectorToVec2(value["position"]));
    }
    // damping
    if (value.HasMember("angularDamping")) {
        body->setAngularDamping(value["angularDamping"].GetDouble());
    }
    if (value.HasMember("linearDamping")) {
        body->setLinearDamping(value["linearDamping"].GetDouble());
    }
    // fixtures
    if (value.HasMember("fixture")) {
        rapidjson::Value& valueFixtures = value["fixture"];
        for (auto it = valueFixtures.Begin(); it != valueFixtures.End(); it++) {
            if((*it).HasMember("polygon")) {
                RubeParser::parseFixturePolygonTo(body, (*it));
            } else if ((*it).HasMember("circle")) {
                RubeParser::parseFixtureCircleTo(body, (*it));
            }
        }
    }
    RubeParser::parseCustomPeropertyTo(body, value);
    rubeObject->addBody(body);
}

void RubeParser::parseFixtureMaterial(RubeFixture* fixture, rapidjson::Value& value) {
    if (value.HasMember("friction")) {
        fixture->setFriction(value["friction"].GetDouble());
    }
    if (value.HasMember("density")) {
        fixture->setDensity(value["density"].GetDouble());
    }
    if (value.HasMember("restitution")) {
        fixture->setRestitution(value["restitution"].GetDouble());
    }
    if (value.HasMember("filter-categoryBits")) {
        fixture->setFilterCategoryBits(value["filter-categoryBits"].GetInt());
    } else {
        fixture->setFilterCategoryBits(1);
    }
    if (value.HasMember("filter-maskBits")) {
        fixture->setFilterMaskBits(value["filter-maskBits"].GetInt());
    } else {
        fixture->setFilterMaskBits(65535);
    }
    if (value.HasMember("restitution")) {
        fixture->setRestitution(value["restitution"].GetDouble());
    }
}

void RubeParser::parseFixturePolygonTo(RubeBody* rubeBody, rapidjson::Value& value) {
    if (!value.HasMember("polygon")) {
        return;
    }
    RubeFixturePolygon* fixture = new RubeFixturePolygon();
    RubeParser::parseFixtureMaterial(fixture, value);
    rapidjson::Value& polygon = value["polygon"];
    rapidjson::Value& vertices = polygon["vertices"];
    rapidjson::Value& verticesX = vertices["x"];
    rapidjson::Value& verticesY = vertices["y"];
    if (verticesX.Size() == verticesY.Size()) {
        rapidjson::SizeType num = verticesX.Size();
        // 後ろから入れていくことにより座標が反時計回りで入る
        for(int i = num - 1; 0 <= i; i--){
            fixture->addVertex(Vec2(
                                    verticesX[i].GetDouble(),
                                    verticesY[i].GetDouble()
                                    ));
        }
    } else {
        log("vetices size not match.");
    }
    rubeBody->addFixture(fixture);
}

void RubeParser::parseFixtureCircleTo(RubeBody* rubeBody, rapidjson::Value& value) {
    if (!value.HasMember("circle")) {
        return;
    }
    RubeFixtureCircle* fixture = new RubeFixtureCircle();
    RubeParser::parseFixtureMaterial(fixture, value);
    rapidjson::Value& circle = value["circle"];
    // center
    if (circle.HasMember("center")) {
        fixture->setPosition(RubeParser::parseVectorToVec2(circle["center"]));
    }
    // radius
    if (circle.HasMember("radius")) {
        fixture->setRadius(circle["radius"].GetDouble());
    }
    rubeBody->addFixture(fixture);
}


void RubeParser::parseJointsTo(RubeObject* rubeObject, rapidjson::Document& d) {
    if (!d.HasMember("joint")) {
        return;
    }
    rapidjson::Value& joints = d["joint"];
    for (auto it = joints.Begin(); it != joints.End(); it++) {
        RubeParser::parseJointTo(rubeObject, *it);
    }
}

void RubeParser::parseJointTo(RubeObject* rubeObject, const rapidjson::Value& value) {
    if (!value.HasMember("type")
        || !value.HasMember("name")
        || !value.HasMember("anchorA")
        || !value.HasMember("anchorB")
        || !value.HasMember("bodyA")
        || !value.HasMember("bodyB")) {
        return;
    }
    RubeJoint* joint;
    std::string type = value["type"].GetString();
    if (0 == type.compare("revolute")) {
        auto j = new RubeJointRevolute();
        RubeParser::parseJointRevoluteTo(j, value);
        joint = j;
    } else {
        cocos2d::log("joint type not found");
        joint = new RubeJointRevolute();
    }
    joint->setName(value["name"].GetString());
    joint->setAnchorA(RubeParser::parseVectorToVec2(value["anchorA"]));
    joint->setAnchorB(RubeParser::parseVectorToVec2(value["anchorB"]));
    joint->setBodyA(value["bodyA"].GetInt());
    joint->setBodyB(value["bodyB"].GetInt());
    rubeObject->addJoint(joint);
}

void RubeParser::parseJointRevoluteTo(RubeJointRevolute* joint, const rapidjson::Value& value) {
    joint->setEnableLimit(value["enableLimit"].GetBool());
    joint->setLowerLimit(value["lowerLimit"].GetDouble());
    joint->setUpperLimit(value["upperLimit"].GetDouble());
}

void RubeParser::parseImagesTo(RubeObject* rubeObject, rapidjson::Document& d) {
    if (!d.HasMember("image")) {
        return;
    }
    rapidjson::Value& images = d["image"];
    for (auto it = images.Begin(); it != images.End(); it++) {
        RubeParser::parseImageTo(rubeObject, *it);
    }
}

void RubeParser::parseImageTo(RubeObject* rubeObject, rapidjson::Value& value) {
    if (!value.HasMember("aspectScale")
        || !value.HasMember("body")
        || !value.HasMember("center")
        || !value.HasMember("file")
        || !value.HasMember("filter")
        || !value.HasMember("name")
        || !value.HasMember("opacity")
        || !value.HasMember("scale")
        ) {
        return;
    }
    RubeImage* image = new RubeImage();
    
    image->setAspectScale(value["aspectScale"].GetDouble());
    image->setBodyIndex(value["body"].GetInt());
    image->setPosition(RubeParser::parseVectorToVec2(value["center"]));
    if (value.HasMember("colorTint") && value["colorTint"].IsArray() && 4 == value["colorTint"].Size()) {
        image->setColorTint(cocos2d::Color4B(value["colorTint"][0].GetInt(),
                                             value["colorTint"][1].GetInt(),
                                             value["colorTint"][2].GetInt(),
                                             value["colorTint"][3].GetInt()));
    }
    if (value.HasMember("angle")) {
        image->setAngle(value["angle"].GetDouble());
    }
    if (value.HasMember("flip")) {
        image->setFlip(value["flip"].GetBool());
    }
    image->setFile(value["file"].GetString());
    image->setFilter(value["filter"].GetInt());
    image->setName(value["name"].GetString());
    image->setOpacity(value["opacity"].GetDouble());
    image->setScale(value["scale"].GetDouble());
    
    rubeObject->addImage(image);
}

void RubeParser::parseCustomPeropertyTo(RubeCustomProperty* object, rapidjson::Value& value) {
    if (!value.HasMember("customProperties")) {
        return;
    }
    rapidjson::Value& customProperties = value["customProperties"];
    if (!customProperties.IsArray()) {
        return;
    }
    for (auto it = customProperties.Begin(); it != customProperties.End(); it++) {
        rapidjson::Value& customValue = (*it);
        cocos2d::Value cocos2dValue;
        // "int", "float", "string", "vec2", "color" or "bool"
        if (customValue.HasMember("int")) {
            cocos2dValue = customValue["int"].GetInt();
        } else if (customValue.HasMember("float")) {
            cocos2dValue = customValue["float"].GetDouble();
        } else if (customValue.HasMember("string")) {
            cocos2dValue = customValue["string"].GetString();
        } else if (customValue.HasMember("bool")) {
            cocos2dValue = customValue["bool"].GetBool();
        }
        object->setCustomProperty(
                                  customValue["name"].GetString(),
                                  cocos2dValue
                                  );
    }
}

void RubeParser::setImageIndexToBody(RubeObject* rubeObject) {
    auto bodyManager = rubeObject->getBodyManager();
    auto imageManager = rubeObject->getImageManager();
    int size = imageManager->size();
    for (int i = 0; i < size; i++) {
        auto image = imageManager->getAt(i);
        int bodyIndex = image->getBodyIndex();
        if (bodyIndex < 0) {
            continue;
        }
        auto body = bodyManager->getAt(bodyIndex);
        body->addImageIndex(i);
    }
}

cocos2d::Vec2 RubeParser::parseVectorToVec2(const rapidjson::Value& value) {
    if (value.IsInt() && 0 == value.GetInt()) {
        return cocos2d::Vec2::ZERO;
    } else if (value.HasMember("x") && value.HasMember("y")) {
        return Vec2(
                    value["x"].GetDouble(),
                    value["y"].GetDouble()
                    );
    }
    log("failed parse (vector)");
    return cocos2d::Vec2::ZERO;
}
