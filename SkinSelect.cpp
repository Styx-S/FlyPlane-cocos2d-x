#include "SelectScene.h"
#include "Constant.h"
#include "SkinSelect.h"


SkinSelect* SkinSelect::createScene() {
	return SkinSelect::create();
}

bool SkinSelect::init() {
	if (!Scene::init())
	{
		return false;
	}

	auto bg = Sprite::createWithSpriteFrameName("background.png");
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(bg);

	//游戏选项label
	auto gameOption = Label::createWithTTF("Skin Option", "BRADHITC.TTF", 56);
	gameOption->setColor(Color3B::BLACK);
	gameOption->setPosition(SIZE.width / 2, SIZE.width / 2 + 300);
	this->addChild(gameOption);


	//模式选择菜单

	//皮肤1
	auto spskinOne = Sprite::createWithSpriteFrameName("hero1.png");
	auto skinOne = MenuItemSprite::create(spskinOne, spskinOne, [=](Ref*) {
		auto scene = SelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));
	});
	skinOne->setPosition(-150,0);
	//红色皮肤
	auto spskinTwo = Sprite::createWithSpriteFrameName("hero1.png");
	spskinTwo->setColor(Color3B::RED);
	auto skinTwo = MenuItemSprite::create(spskinTwo, spskinTwo, [=](Ref*) {
		auto scene = SelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));
	});

	//蓝色皮肤
	auto spskinThree = Sprite::createWithSpriteFrameName("hero1.png");
	spskinThree->setColor(Color3B::BLUE);
	auto skinThree = MenuItemSprite::create(spskinThree, spskinThree, [=](Ref*) {
		auto scene = SelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));
	});
	skinThree->setPosition(150,0);

	//回到主菜单
	auto spback = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto itemBcak = MenuItemSprite::create(spback, spback, [](Ref*) {
		auto scene = SelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1, scene));
	});
	itemBcak->setPositionY(-200);



	auto menu = Menu::create(skinOne, skinTwo, skinThree ,itemBcak, nullptr);
	this->addChild(menu);


	return true;
}