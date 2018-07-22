#include "SelectScene.h"
#include "GameScene.h"
#include "LoadingScene.h"
#include "Constant.h"
#include "SkinSelect.h"

#include "DefaultConstant.h"

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

	//��Ϸѡ��label
	auto gameOption = Label::createWithTTF("Game Option", "BRADHITC.TTF", 56);
	gameOption->setColor(Color3B::BLACK);
	gameOption->setPosition(SIZE.width / 2, SIZE.width / 2 + 300);
	this->addChild(gameOption);


	//ģʽѡ��˵�
	//��ѡ��
	auto spsimple = Sprite::createWithSpriteFrameName("easy.png");
	auto itemsimple = MenuItemSprite::create(spsimple, spsimple, [=](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemsimple->setPositionY(100);
	//itemsimple->setScaleX(2);
	//һ��ѡ��
	auto spordinary = Sprite::createWithSpriteFrameName("hard.png");
	auto itemordinary = MenuItemSprite::create(spordinary, spordinary, [=](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	//itemordinary->setScaleX(2);
	//����ѡ��
	auto spdifficult = Sprite::createWithSpriteFrameName("hell.png");
	auto itemdiffcult = MenuItemSprite::create(spdifficult, spdifficult, [=](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	//itemdiffcult->setScaleX(2);
	itemdiffcult->setPositionY(-100);

	//Ƥ��ѡ��,����һ���µĽ���ѡ��Ƥ��
	auto spskin = Sprite::createWithSpriteFrameName("set_skin.png");
	auto itemskin = MenuItemSprite::create(spskin, spskin, [](Ref*) {
		auto scene = SkinSelect::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemskin->setPositionY(-200);



	auto menu = Menu::create(itemsimple,itemordinary,itemdiffcult,itemskin, nullptr);
	this->addChild(menu);
	//scheduleUpdate();
	return true;
}
