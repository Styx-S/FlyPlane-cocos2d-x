#include "Enemy.h"
#include "Constant.h"
#include "LoadingScene.h"
#include "AudioEngine.h"
#define FROM_ANICACHE(name) AnimationCache::getInstance()->getAnimation(name)

using namespace experimental;
///////////// Enemy

bool Enemy::hit(float hurt) {
	this->setHealth(this->getHealth() - hurt);
	if (this->getHealth() <= 0) {
		this->playExplodeAnimationAndDie();
		return true;
	}
	else { 
		this->playHitAnimation();
		return false;
	}
}
void Enemy::move() {
	this->setPosition(this->getPosition() + m_speed);
}
Vec2 Enemy::setDefaultPositon() {
	this->setPositionY(SIZE.height + this->getContentSize().height / 2);
	float minX = this->getContentSize().width / 2;
	float maxX = SIZE.width - minX;
	float x = rand() % (int)(maxX - minX + 1) + minX; // 例如，要得到0到3，需要模(3+1)
	this->setPositionX(x);
	return this->getPosition();
}
bool Enemy::isAbilityCallEnemy() {
	return false;
}

void Enemy::_playFly(Animation* enemyAnimation) {
	this->runAction(Animate::create(enemyAnimation));
}
void Enemy::_playhit(Animation* enemyAnimation) {
	this->runAction(Animate::create(enemyAnimation));
}
void Enemy::_playEx(Animation* enemyAnimation) {
	auto enemyAnimate = Animate::create(enemyAnimation);
	auto seq = Sequence::create(enemyAnimate, CallFuncN::create(
		[](Node* node) {
		node->removeFromParentAndCleanup(true);
	}), nullptr);
	this->stopAllActions(); // 停掉其他（循环）动画
	this->runAction(seq);
}

//////////// SmallEnemy
SmallEnemy* SmallEnemy::create() {
	auto sEnemy = new SmallEnemy();
	if (sEnemy && sEnemy->initWithSpriteFrameName("enemy1.png")) {
		sEnemy->autorelease();
		sEnemy->m_health = SMALL_ENEMY_HEALTH;
		sEnemy->m_speed = Vec2(0, -SMALL_ENEMY_SPEED);
		sEnemy->m_score = SMALL_ENEMY_SCORE;
	}
	else {
		delete sEnemy;
		sEnemy = nullptr;
	}
	return sEnemy;
}
// do nothing
void SmallEnemy::playFlyAnimation() {}
void SmallEnemy::playHitAnimation() {}
void SmallEnemy::playExplodeAnimationAndDie() {
	auto ani = FROM_ANICACHE(SMALLENEMY_EXPLODE_ANIMATION);
	this->_playEx(ani);
	AudioEngine::play2d("enemy1_down.mp3");
}
bool SmallEnemy::isAbilityCallEnemy() {
	return false;
}

//////////// MiddleEnemy
MiddleEnemy* MiddleEnemy::create() {
	auto sEnemy = new MiddleEnemy();
	if (sEnemy && sEnemy->initWithSpriteFrameName("enemy2.png")) {
		sEnemy->autorelease();
		sEnemy->m_health = MIDDLE_ENEMY_HEALTH;
		sEnemy->m_speed = Vec2(0, -MIDDLE_ENEMY_SPEED);
		sEnemy->m_score = MIDDLE_ENEMY_SCORE;
	}
	else {
		delete sEnemy;
		sEnemy = nullptr;
	}
	return sEnemy;
}
void MiddleEnemy::playFlyAnimation() {}
void MiddleEnemy::playHitAnimation(){
	auto ani = FROM_ANICACHE(MIDDLEENEMY_HIT_ANIMATION);
	this->_playFly(ani);
}
void MiddleEnemy::playExplodeAnimationAndDie() {
	auto ani = FROM_ANICACHE(MIDDLEENEMY_EXPLODE_ANIMATION);
	this->_playEx(ani);
	AudioEngine::play2d("enemy2_down.mp3");
}
bool MiddleEnemy::isAbilityCallEnemy() {
	return false;
}

//////////// BigEnemy
BigEnemy* BigEnemy::create() {
	auto sEnemy = new BigEnemy();
	if (sEnemy && sEnemy->initWithSpriteFrameName("enemy3_n1.png")) {
		sEnemy->autorelease();
		sEnemy->m_health = BIG_ENEMY_HEALTH;
		sEnemy->m_speed = Vec2(0, -BIG_ENEMY_SPEED);
		sEnemy->m_score = BIG_ENEMY_SCORE;
	}
	else {
		delete sEnemy;
		sEnemy = nullptr;
	}
	return sEnemy;
}
void BigEnemy::playFlyAnimation() {
	auto ani = FROM_ANICACHE(BIGENEMY_FLY_ANIMATION);
	this->_playFly(ani);
	AudioEngine::play2d("big_spaceship_flying.mp3");
}
void BigEnemy::playHitAnimation() {
	auto ani = FROM_ANICACHE(BIGENEMY_HIT_ANIMATION);
	this->_playFly(ani);
}
void BigEnemy::playExplodeAnimationAndDie() {
	auto ani = FROM_ANICACHE(BIGENEMY_EXPLODE_ANIMATION);
	this->_playEx(ani);	
	AudioEngine::play2d("enemy3_down.mp3");
}
bool BigEnemy::isAbilityCallEnemy() {
	return true;
}



////bool Enemy::initWithFrameName(const std::string& frameName) {
////	if (!Sprite::initWithSpriteFrameName(frameName))
////		return false;
////	return true;
////}
////Enemy* Enemy::create() {
////	auto enemy = new Enemy();
////	if (enemy && enemy->initWithEnemyType(type)) {
////		enemy->autorelease(); //引用计数器暂时+1
////		return enemy;
////	}
////	delete enemy;
////	enemy = nullptr;
////	return nullptr;
////}
//void Enemy::playExplodeAnimationAndDie() {
//	auto enemyAnimation = Animation::create();
//	for (int i = 0; i < frameNums; i++) {
//		auto frameName = StringUtils::format(formatString.c_str(), enemyIndex, i + 1);
//		enemyAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
//	}
//	enemyAnimation->setDelayPerUnit(ENEMY_EXPLODE_TIME_PER_FRAME);
//	auto enemyAnimate = Animate::create(enemyAnimation);
//	auto seq = Sequence::create(enemyAnimate, CallFuncN::create(
//		[](Node* node) {
//		node->removeFromParentAndCleanup(true);
//	}), nullptr);
//	this->stopAllActions(); // 停掉其他（循环）动画
//	this->runAction(seq);
//}
//void Enemy::playFlyAnimation(int enemyIndex, int frameNums, const std::string& formatString) {
//	auto enemyAnimation = Animation::create();
//	for (int i = 1; i < frameNums; i++) {
//		auto frameName = StringUtils::format(formatString.c_str(), enemyIndex, frameNums);
//		enemyAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
//	}
//	enemyAnimation->addSpriteFrame(
//		SpriteFrameCache::getInstance()->getSpriteFrameByName(
//			StringUtils::format(formatString.c_str(), enemyIndex, 1)));
//	enemyAnimation->setDelayPerUnit(ENEMY_FLY_ANIMATION_TIME_PER_FRAME);
//	enemyAnimation->setLoops(CC_REPEAT_FOREVER);
//	auto enemyAnimate = Animate::create(enemyAnimation);
//	this->runAction(enemyAnimate);
//}
//void Enemy::playHitAnimation(int enemyIndex, int frameNums, const std::string& formatString) {
//	auto enemyAnimation = Animation::create();
//	for (int i = 0; i < frameNums; i++) {
//		auto frameName = StringUtils::format(formatString.c_str(), enemyIndex, frameNums);
//		enemyAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
//	}
//	enemyAnimation->setRestoreOriginalFrame(true);
//	enemyAnimation->setDelayPerUnit(ENEMY_HIT_ANIMATION_TIME_PER_FRAME);
//	this->runAction(Animate::create(enemyAnimation));
//}
