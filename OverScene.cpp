#include "OverScene.h"
#include "Constant.h"
#include "GameScene.h"

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
	
	// ÖØÆôÓÎÏ·
	auto spRestart = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto itemRestart = MenuItemSprite::create(spRestart, spRestart, [](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemRestart->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	itemRestart->setPosition(SIZE.width - 20, 20);

	auto menu = Menu::create(itemRestart, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, UI_ZORDER);
	return true;
}