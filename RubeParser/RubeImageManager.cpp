#include "RubeImageManager.hpp"

USING_NS_CC;

cocos2d::Sprite* RubeImageManager::createSpriteAt(int index)
{
    auto rubeImage = images[index];
    auto rubeObjectScale = this->getRubeObject()->getScale();
    auto imagePath = pathDirectoryRubeJson + rubeImage->getFile();
    //log("imagePath: %s", imagePath.c_str());
    auto sprite = Sprite::create(imagePath);
    float rubeScaledPixel = rubeImage->getScale() * rubeObjectScale;
    auto size = sprite->getTexture()->getContentSize();
    float height = size.height;
    float baseScale = 1/(height/rubeScaledPixel);
    sprite->setScaleX(rubeImage->getAspectScale() * baseScale);
    sprite->setScaleY(baseScale);
    sprite->setRotation(CC_RADIANS_TO_DEGREES(-rubeImage->getAngle()));
    sprite->setPosition(rubeImage->getPosition() * rubeObjectScale);
    return sprite;
}

int RubeImageManager::size() {
    return images.size();
}

RubeImage* RubeImageManager::getAt(int index) {
    return this->images[index];
}

void RubeImageManager::add(RubeImage* image) {
    images.push_back(image);
}

RubeImageManager::~RubeImageManager() {
    for (auto image : images) {
        delete image;
    }
    images.clear();
}