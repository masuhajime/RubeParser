#pragma once

#include <stdio.h>

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include "RubeObject.hpp"
#include "RubeJointRevolute.hpp"

USING_NS_CC;

class RubeParser
{
public:
    static void parseTo(RubeObject* rubeObject, std::string filename);
    
private:
    static void parseBodiesTo(RubeObject* rubeObject, rapidjson::Document& d);
    
    static void parseBodyTo(RubeObject* rubeObject, rapidjson::Value& value);
    
    /**
     * density, restitution, friction の parser
     */
    static void parseFixtureMaterial(RubeFixture* fixture, rapidjson::Value& value);
    
    static void parseFixturePolygonTo(RubeBody* rubeBody, rapidjson::Value& value);
    
    static void parseFixtureCircleTo(RubeBody* rubeBody, rapidjson::Value& value);
    
    static void parseJointsTo(RubeObject* rubeObject, rapidjson::Document& d);
    
    static void parseJointTo(RubeObject* rubeObject, const rapidjson::Value& value);
    
    static void parseJointRevoluteTo(RubeJointRevolute* joint, const rapidjson::Value& d);
    
    static void parseImagesTo(RubeObject* rubeObject, rapidjson::Document& d);
    
    static void parseImageTo(RubeObject* rubeObject, rapidjson::Value& value);
    
    static void setImageIndexToBody(RubeObject* rubeObject);
    
    static cocos2d::Vec2 parseVectorToVec2(const rapidjson::Value& value);
};