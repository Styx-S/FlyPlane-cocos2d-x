#include "LoadingScene.h"
#include "GameScene.h"
#include "Constant.h"
#include "AudioEngine.h"
#include "SelectScene.h"
#include "ConfigUtil.h"


using namespace experimental;

Scene* LoadingScene::createScene() {
	return LoadingScene::create();
}
bool LoadingScene::init() {
	if (!Scene::init())
		return false;
	ConfigUtil::getInstance();
	// ͼ�����뻺��
	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("shoot_background.plist");
	spriteCache->addSpriteFramesWithFile("shoot.plist");
	// ���⡢����
	auto spBackground = Sprite::createWithSpriteFrameName("background.png");
	spBackground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(spBackground);
	auto spTitle = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	spTitle->setPosition(SIZE.width / 2, SIZE.height * 2 / 3);
	this->addChild(spTitle);

	// ���붯��
	auto spLoading = Sprite::createWithSpriteFrameName("game_loading1.png");
	spLoading->setPosition(SIZE.width/2, spTitle->getPositionY() 
		- spTitle->getContentSize().height/2 - spLoading->getContentSize().height/2 -30);
	this->addChild(spLoading);
	auto aninLoading = LoadingScene::getLoopAnimation(1,4,"game_loading%d.png",true);
	aninLoading->setDelayPerUnit(LOADING_TIME_PER_FRAME);
	aninLoading->setLoops(2);
	auto anieLoading = Animate::create(aninLoading);
	auto sqLoading = Sequence::create(anieLoading,CallFunc::create([]() {
		auto scene = SelectScene::create(); //�Ӽ���ҳ������Ѷ�ģʽѡ��
		Director::getInstance()->replaceScene(TransitionMoveInB::create(0,scene));
	}),nullptr);
	spLoading->runAction(sqLoading);
	//// ���ض������� ////
	auto aniCache = AnimationCache::getInstance();
	// Hero����
	auto aninHeroFly = LoadingScene::getLoopAnimation(1,2,"hero%d.png",true);
	aninHeroFly->setDelayPerUnit(0.2f);
	aninHeroFly->setLoops(CC_REPEAT_FOREVER);
	aniCache->addAnimation(aninHeroFly, HERO_FLY_ANIMATION);
	// SmallEnemy����
	auto aniSEnemyExplode = LoadingScene::getLoopAnimation(1, 4, "enemy1_down%d.png");
	aniSEnemyExplode->setDelayPerUnit(ENEMY_EXPLODE_TIME_PER_FRAME);
	aniCache->addAnimation(aniSEnemyExplode, SMALLENEMY_EXPLODE_ANIMATION);
	// MiddleEnemy����
	auto aniMEnemyHit = LoadingScene::getLoopAnimation(1, 1, "enemy2_hit.png");
	aniMEnemyHit->setDelayPerUnit(ENEMY_HIT_ANIMATION_TIME_PER_FRAME);
	aniMEnemyHit->setRestoreOriginalFrame(true);
	aniCache->addAnimation(aniMEnemyHit, MIDDLEENEMY_HIT_ANIMATION);
	
	auto aniMEnemyExplode = LoadingScene::getLoopAnimation(1, 4, "enemy2_down%d.png");
	aniMEnemyExplode->setDelayPerUnit(ENEMY_EXPLODE_TIME_PER_FRAME);
	aniCache->addAnimation(aniMEnemyExplode, MIDDLEENEMY_EXPLODE_ANIMATION);
	// BigEnemy����
	auto aniBEnemyFly = LoadingScene::getLoopAnimation(1,2,"enemy3_n%d.png",true);
	aniBEnemyFly->setLoops(CC_REPEAT_FOREVER);
	aniBEnemyFly->setDelayPerUnit(ENEMY_FLY_ANIMATION_TIME_PER_FRAME);
	aniCache->addAnimation(aniBEnemyFly, BIGENEMY_FLY_ANIMATION);
	
	auto aniBEnemyHit = LoadingScene::getLoopAnimation(1, 1, "enemy3_hit.png");
	aniBEnemyHit->setDelayPerUnit(ENEMY_HIT_ANIMATION_TIME_PER_FRAME);
	aniBEnemyHit->setRestoreOriginalFrame(true);
	aniCache->addAnimation(aniBEnemyHit, BIGENEMY_HIT_ANIMATION);
	
	auto aniBEnemyExplode = LoadingScene::getLoopAnimation(1, 6, "enemy3_down%d.png");
	aniBEnemyExplode->setDelayPerUnit(ENEMY_EXPLODE_TIME_PER_FRAME);
	aniCache->addAnimation(aniBEnemyExplode, BIGENEMY_EXPLODE_ANIMATION);
	//Aerolite ��ը����
	auto aniAerolite = LoadingScene::getLoopAnimation(1, 1, "star_bomb.png");
	aniAerolite->setDelayPerUnit(ENEMY_EXPLODE_TIME_PER_FRAME / 4);
	aniCache->addAnimation(aniAerolite, AEROLITE_EXPLODE_ANIMATION);
	//hero��������
	auto ani_herodie = Animation::create();
	for (int i = 0; i < 4; i++)
	{
		auto frameName = StringUtils::format("hero_blowup_n%d.png", i + 1);
		ani_herodie->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	ani_herodie->setDelayPerUnit(HERO_DIE_TIME_PER_FRAME); //����ʱ��
	AnimationCache::getInstance()->addAnimation(ani_herodie, HERO_DIE_ANIMATION);

	// Ԥ���������ļ�
	AudioEngine::preload("achievement.mp3");
	AudioEngine::preload("big_spaceship_flying.mp3");
	AudioEngine::preload("bullet.mp3");
	AudioEngine::preload("button.mp3");
	AudioEngine::preload("enemy1_down.mp3");
	AudioEngine::preload("enemy2_down.mp3");
	AudioEngine::preload("enemy3_down.mp3");
	AudioEngine::preload("game_music.mp3");
	AudioEngine::preload("game_over.mp3");
	AudioEngine::preload("get_bomb.mp3");
	AudioEngine::preload("get_double_laser.mp3");
	AudioEngine::preload("out_porp.mp3");
	AudioEngine::preload("use_bomb.mp3");


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
 //	animation->autorelease();   ��create���ѽ�����autorelease,����Ҫ�ظ�����
	return animation;
}