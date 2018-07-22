#pragma once

#include "cocos2d.h"
USING_NS_CC;

class LoadingScene : public Scene {
public:
	static Scene* createScene();
	bool init() override;
	CREATE_FUNC(LoadingScene);
private:
	static Animation* getLoopAnimation(int startIndex, int frameNums, const std::string& formatString = "example%d.png", bool putFirstInEnd = false);
};