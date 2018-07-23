#pragma once
#include "cocos2d.h"
USING_NS_CC;


class HelpScene : public Scene {
public:
	static HelpScene* createScene();
	bool init() override;
	CREATE_FUNC(HelpScene);

};
