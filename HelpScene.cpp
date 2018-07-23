#include "HelpScene.h"
#include "SelectScene.h"
#include "LoadingScene.h"
#include "Constant.h"
#include "DefaultConstant.h"
#include "ConfigUtil.h"

HelpScene* HelpScene::createScene() {
	return HelpScene::create();
}

bool HelpScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto bg = Sprite::createWithSpriteFrameName("background.png");
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(bg);

	auto Introtitle = Label::createWithTTF("A Brief Intro to the Game", "BRADHITC.TTF", 36);
	Introtitle->setColor(Color3B::BLACK);
	Introtitle->setPosition(SIZE.width / 2, SIZE.width / 2 + 300);
	this->addChild(Introtitle);

	auto Intro = Label::createWithTTF("   Hi, players! This is a very good leisure and classical game. You can get points by controlling an aircraft to shoot down enemies.Four items you can get in game have interesting effects and there are three models you can choose. Remember! Everytime you get twenty points, enemies will upgrade with extra speeds, health points and numbers.Hope you have fun!\n                                                                2018", "BRADHITC.TTF", 20);
	Intro->setDimensions(400,500);
	Intro->setColor(Color3B::BLACK);
	Intro->setPosition(SIZE.width / 2, SIZE.width / 2 );
	this->addChild(Intro);
	

	auto sphelp = Sprite::createWithSpriteFrameName("return.png");
	auto itemhelp = MenuItemSprite::create(sphelp, sphelp, [](Ref*) {
		auto scene = SelectScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemhelp->setPosition(SIZE.width / 2 - itemhelp->getContentSize().width / 2, -SIZE.height / 2 + itemhelp->getContentSize().height / 2);


	auto menu = Menu::create(itemhelp, nullptr);
	this->addChild(menu);
	return true;
}