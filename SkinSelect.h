#pragma once
#include "cocos2d.h"
USING_NS_CC;


class SkinSelect : public Scene {
public:
	static SkinSelect* createScene();
	bool init() override;
	CREATE_FUNC(SkinSelect);

};
