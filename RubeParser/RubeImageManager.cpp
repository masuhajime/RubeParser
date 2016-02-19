#include "RubeImageManager.hpp"

USING_NS_CC;

cocos2d::Node* RubeImageManager::createSpriteWithNodeAt(int index) {
    auto node = Node::create();
    auto rubeImage = images[index];
    auto rubeObjectScale = this->getRubeObject()->getScale();
    auto imagePath = pathDirectoryRubeJson + rubeImage->getFile();
    auto sprite = Sprite::create(imagePath);
    float rubeScaledPixel = rubeImage->getScale() * rubeObjectScale;
    auto size = sprite->getTexture()->getContentSize();
    float max = std::max(size.width, size.height);
    sprite->setScale(1/(max/rubeScaledPixel));
    node->addChild(sprite);
    return node;
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