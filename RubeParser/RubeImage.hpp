#pragma once

#include "cocos2d.h"

USING_NS_CC;

class RubeImage
{
    // rube image parameter
    CC_SYNTHESIZE(float, aspectScale, AspectScale);// 縦横比
    CC_SYNTHESIZE(int, bodyIndex, BodyIndex);
    CC_SYNTHESIZE(cocos2d::Vec2, position, Position);
    CC_SYNTHESIZE(cocos2d::Color4B, colorTint, ColorTint);
    CC_SYNTHESIZE(std::string, file, File);
    CC_SYNTHESIZE(int, filter, Filter);
    CC_SYNTHESIZE(std::string, name, Name);
    CC_SYNTHESIZE(float, opacity, Opacity);
    CC_SYNTHESIZE(float, scale, Scale);// 画像の拡大率
    CC_SYNTHESIZE(float, angle, Angle);
};
