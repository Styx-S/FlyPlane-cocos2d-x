#pragma once
#include "cocos2d.h"
USING_NS_CC;


class SelectScene : public Scene {
public:
	static SelectScene* createScene();
	bool init() override;
	CREATE_FUNC(SelectScene);

};
