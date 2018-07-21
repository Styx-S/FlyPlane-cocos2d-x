#pragma once

#include "cocos2d.h"
#include "Constant.h"
USING_NS_CC;

class OverScene : public Scene {
public:
	static Scene* createScene(int score);
	bool init(int score)override;

};