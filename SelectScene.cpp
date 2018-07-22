#include "SelectScene.h"
#include "GameScene.h"
#include "LoadingScene.h"
#include "Constant.h"

SelectScene* SelectScene::createScene() {
	return SelectScene::create();
}

bool SelectScene::init() {
	if (!Scene::init())
	{
		return false;
	}


	auto bg = Sprite::createWithSpriteFrameName("background.png");
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(bg);

	//游戏选项label
	auto gameOption = Label::createWithTTF("Game Option", "BRADHITC.TTF", 56);
	gameOption->setColor(Color3B::BLACK);
	gameOption->setPosition(SIZE.width / 2, SIZE.width / 2 + 300);
	this->addChild(gameOption);


	//模式选择菜单

	//简单选项
	auto spsimple = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto itemsimple = MenuItemSprite::create(spsimple, spsimple, [=](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemsimple->setPositionY(100);
	//一般选项
	auto spordinary = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto itemordinary = MenuItemSprite::create(spordinary, spordinary, [=](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	//困难选项
	auto spdifficult = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto itemdiffcult = MenuItemSprite::create(spdifficult, spdifficult, [=](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemdiffcult->setPositionY(-100);

	//皮肤选择,进入一个新的界面选择皮肤
	auto spskin = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto itemskin = MenuItemSprite::create(spskin, spskin, [](Ref*) {});
	itemskin->setPositionY(-200);



	auto menu = Menu::create(itemsimple,itemordinary,itemdiffcult,itemskin, nullptr);
	this->addChild(menu);
	//scheduleUpdate();
	return true;
}

void SelectScene::update(float delta) {

}