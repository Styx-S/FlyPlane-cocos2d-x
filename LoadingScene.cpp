#include "LoadingScene.h"
#include "GameScene.h"
#include "Constant.h"

Scene* LoadingScene::createScene() {
	return LoadingScene::create();
}
bool LoadingScene::init() {
	if (!Scene::init())
		return false;
	// 图集载入缓存
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("shoot_background.plist");
	spriteCache->addSpriteFramesWithFile("shoot.plist");
	
	// 标题、背景
	auto spBackground = Sprite::createWithSpriteFrameName("background.png");
	spBackground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(spBackground);
	auto spTitle = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	spTitle->setPosition(SIZE.width / 2, SIZE.height * 2 / 3);
	this->addChild(spTitle);

	// 载入动画
	auto spLoading = Sprite::createWithSpriteFrameName("game_loading1.png");
	spLoading->setPosition(SIZE.width/2, spTitle->getPositionY() 
		- spTitle->getContentSize().height/2 - spLoading->getContentSize().height/2 -30);
	this->addChild(spLoading);
	auto aninLoading = LoadingScene::getLoopAnimation(1,4,"game_loading%d.png",true);
	aninLoading->setDelayPerUnit(LOADING_TIME_PER_FRAME);
	aninLoading->setLoops(4);
	auto anieLoading = Animate::create(aninLoading);
	auto sqLoading = Sequence::create(anieLoading,CallFunc::create([]() {
		auto scene = GameScene::create();
		Director::getInstance()->replaceScene(TransitionMoveInB::create(0,scene));
	}),nullptr);
	spLoading->runAction(sqLoading);
	//// 加载动画缓存 ////
	auto aniCache = AnimationCache::getInstance();
	// Hero动画
	auto aninHeroFly = LoadingScene::getLoopAnimation(1,2,"hero%d.png",true);
	aninHeroFly->setDelayPerUnit(0.2f);
	aninHeroFly->setLoops(CC_REPEAT_FOREVER);
	aniCache->addAnimation(aninHeroFly, HERO_FLY_ANIMATION);
	// SmallEnemy动画
	auto aniSEnemyExplode = LoadingScene::getLoopAnimation(1, 4, "enemy1_down%d.png");
	aniSEnemyExplode->setDelayPerUnit(ENEMY_EXPLODE_TIME_PER_FRAME);
	aniCache->addAnimation(aniSEnemyExplode, SMALLENEMY_EXPLODE_ANIMATION);
	// MiddleEnemy动画
	
	
	return true;
}
Animation* LoadingScene::getLoopAnimation(int startIndex, int frameNums, const std::string& formatString, bool flag) {
	auto animation = Animation::create();
	for (int i = flag?startIndex+1:startIndex; i <= frameNums; i++) {
		auto frameName = StringUtils::format(formatString.c_str(), i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	if (flag)
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
			StringUtils::format(formatString.c_str(), startIndex)));
 //	animation->autorelease();   在create中已进行了autorelease,不需要重复调用
	return animation;
}