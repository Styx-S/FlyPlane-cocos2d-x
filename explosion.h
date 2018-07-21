#pragma once
#include"cocos2d.h"
USING_NS_CC;

class explosion : public Animation {
public:
	bool initWithSpriteFrameName(const std::string& spriteFrameName);

	static explosion* creat(const std::string& spriteFrameName);
};


//Animation* Animation::create()
//{
//	Animation *animation = new (std::nothrow) Animation();
//	animation->init();
//	animation->autorelease();
//
//	return animation;
//}