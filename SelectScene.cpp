#include "SelectScene.h"
#include "GameScene.h"
#include "LoadingScene.h"

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

	auto spdifficult = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto itemdiffcult = MenuItemSprite::create(spdifficult, spdifficult, [=](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemdiffcult->setPositionY(-100);

	


	auto menu = Menu::create(itemsimple,itemordinary,itemdiffcult, nullptr);
	this->addChild(menu);
	//scheduleUpdate();
	return true;
}

void SelectScene::update(float delta) {

}