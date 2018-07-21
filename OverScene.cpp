#include "OverScene.h"
#include "Constant.h"
#include "Constant.h"

Scene* OverScene::createScene(int score) {
	auto scene = new OverScene();
	if (scene && scene->init(score)) {
		scene->autorelease();
		return scene;
	}
	delete scene;
	scene = nullptr;
	return scene;
}

bool OverScene::init(int score) {
	if (!Scene::init())
		return false;
	auto spBackground = Sprite::createWithSpriteFrameName("gameover.png");
	spBackground->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	spBackground->setPosition(0, ORIGIN.y + SIZE.height);
	this->addChild(spBackground, BACKGROUND_ZORDER);

	auto lbCurrentScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", score));
	auto highScore = UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE_KEY, 0);
	if (score > highScore) {
		highScore = score;
	}
	auto lbHighScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", highScore));
	return true;
}