#include "SelectScene.h"
#include "GameScene.h"
#include "LoadingScene.h"
#include "Constant.h"
#include "SkinSelect.h"
#include "DefaultConstant.h"
#include "ConfigUtil.h"
#include "HelpScene.h"
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
	gameOption->setPosition(SIZE.width / 2, SIZE.height / 2 + 200);
	this->addChild(gameOption);


	ConfigUtil::getInstance()->setFloat("SMALL_ENEMY_SPEED_DEFAULT", SMALL_ENEMY_SPEED_DEFAULT);
	ConfigUtil::getInstance()->setFloat("MIDDLE_ENEMY_SPEED_DEFAULT", MIDDLE_ENEMY_SPEED_DEFAULT);
	ConfigUtil::getInstance()->setFloat("BIG_ENEMY_SPEED_DEFAULT", BIG_ENEMY_SPEED_DEFAULT);
	ConfigUtil::getInstance()->setFloat("SMALL_ENEMY_HEALTH_DEFAULT", SMALL_ENEMY_HEALTH_DEFAULT);
	ConfigUtil::getInstance()->setFloat("MIDDLE_ENEMY_HEALTH_DEFAULT", MIDDLE_ENEMY_HEALTH_DEFAULT);
	ConfigUtil::getInstance()->setFloat("BIG_ENEMY_HEALTH_DEFAULT", BIG_ENEMY_HEALTH_DEFAULT);
	ConfigUtil::getInstance()->setFloat("CREATE_SMALLENEMY_INTERVAL_DEFAULT", CREATE_SMALLENEMY_INTERVAL_DEFAULT);
	ConfigUtil::getInstance()->setFloat("CREATE_MIDDLEENEMY_INTERVAL_DEFAULT", CREATE_MIDDLEENEMY_INTERVAL_DEFAULT);
	ConfigUtil::getInstance()->setFloat("CREATE_BIGENEMY_INTERVAL_DEFAULT", CREATE_BIGENEMY_INTERVAL_DEFAULT);
	//模式选择菜单
	//简单选项
	auto spsimple = Sprite::createWithSpriteFrameName("easy.png");
	auto itemsimple = MenuItemSprite::create(spsimple, spsimple, [=](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemsimple->setPositionY(100);
	//一般选项
	auto spordinary = Sprite::createWithSpriteFrameName("hard.png");
	auto itemordinary = MenuItemSprite::create(spordinary, spordinary, [=](Ref*) {
		auto scene = GameScene::createScene();
		ConfigUtil::getInstance()->setFloat("SMALL_ENEMY_SPEED_DEFAULT", SMALL_ENEMY_SPEED_DEFAULT + 2.5f);
		ConfigUtil::getInstance()->setFloat("MIDDLE_ENEMY_SPEED_DEFAULT", MIDDLE_ENEMY_SPEED_DEFAULT + 1.5f);
		ConfigUtil::getInstance()->setFloat("BIG_ENEMY_SPEED_DEFAULT", BIG_ENEMY_SPEED_DEFAULT + 1.0f);
		ConfigUtil::getInstance()->setFloat("SMALL_ENEMY_HEALTH_DEFAULT", SMALL_ENEMY_HEALTH_DEFAULT + 100);
		ConfigUtil::getInstance()->setFloat("MIDDLE_ENEMY_HEALTH_DEFAULT", MIDDLE_ENEMY_HEALTH_DEFAULT + 100);
		ConfigUtil::getInstance()->setFloat("BIG_ENEMY_HEALTH_DEFAULT", BIG_ENEMY_HEALTH_DEFAULT + 200);
		ConfigUtil::getInstance()->setFloat("CREATE_SMALLENEMY_INTERVAL_DEFAULT", CREATE_SMALLENEMY_INTERVAL_DEFAULT - 0.5f);
		ConfigUtil::getInstance()->setFloat("CREATE_MIDDLEENEMY_INTERVAL_DEFAULT", CREATE_MIDDLEENEMY_INTERVAL_DEFAULT - 3.0f);
		ConfigUtil::getInstance()->setFloat("CREATE_BIGENEMY_INTERVAL_DEFAULT", CREATE_BIGENEMY_INTERVAL_DEFAULT - 6);
		Director::getInstance()->replaceScene(scene);
	});
	//困难选项
	auto spdifficult = Sprite::createWithSpriteFrameName("hell.png");
	auto itemdiffcult = MenuItemSprite::create(spdifficult, spdifficult, [=](Ref*) {
		ConfigUtil::getInstance()->setFloat("SMALL_ENEMY_SPEED_DEFAULT", SMALL_ENEMY_SPEED_DEFAULT + 2.5f);
		ConfigUtil::getInstance()->setFloat("MIDDLE_ENEMY_SPEED_DEFAULT", MIDDLE_ENEMY_SPEED_DEFAULT + 1.5f);
		ConfigUtil::getInstance()->setFloat("BIG_ENEMY_SPEED_DEFAULT", BIG_ENEMY_SPEED_DEFAULT + 1.0f);
		ConfigUtil::getInstance()->setFloat("SMALL_ENEMY_HEALTH_DEFAULT", SMALL_ENEMY_HEALTH_DEFAULT + 100);
		ConfigUtil::getInstance()->setFloat("MIDDLE_ENEMY_HEALTH_DEFAULT", MIDDLE_ENEMY_HEALTH_DEFAULT + 100);
		ConfigUtil::getInstance()->setFloat("BIG_ENEMY_HEALTH_DEFAULT", BIG_ENEMY_HEALTH_DEFAULT + 200);
		ConfigUtil::getInstance()->setFloat("CREATE_SMALLENEMY_INTERVAL_DEFAULT", CREATE_SMALLENEMY_INTERVAL_DEFAULT - 1.5f);
		ConfigUtil::getInstance()->setFloat("CREATE_MIDDLEENEMY_INTERVAL_DEFAULT", CREATE_MIDDLEENEMY_INTERVAL_DEFAULT - 6.5f);
		ConfigUtil::getInstance()->setFloat("CREATE_BIGENEMY_INTERVAL_DEFAULT", CREATE_BIGENEMY_INTERVAL_DEFAULT - 12);
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemdiffcult->setPositionY(-100);

	//皮肤选择,进入一个新的界面选择皮肤
	auto spskin = Sprite::createWithSpriteFrameName("set_skin.png");
	auto itemskin = MenuItemSprite::create(spskin, spskin, [](Ref*) {

		auto scene = SkinSelect::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemskin->setPositionY(-200);

	//游戏简介，进入一个新的界面
	auto sphelp = Sprite::createWithSpriteFrameName("jj.png");
	auto itemhelp = MenuItemSprite::create(sphelp, sphelp, [](Ref*) {
		auto scene = HelpScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	itemhelp->setPosition(SIZE.width/2 - itemhelp->getContentSize().width/2,-SIZE.height/2+itemhelp->getContentSize().height/2);


	auto menu = Menu::create(itemsimple, itemordinary, itemdiffcult, itemskin, itemhelp, nullptr);
	this->addChild(menu);
	//scheduleUpdate();
	return true;
}