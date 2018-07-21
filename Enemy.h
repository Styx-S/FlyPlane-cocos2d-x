#pragma once

#include "cocos2d.h"
#include "Constant.h"
USING_NS_CC;

class Enemy : public Sprite {
public:
 	//static Enemy* create() = 0;
	//bool initWithFrameName(const std::string&);
	void Enemy::move();

	/*	生成一个protected Vec2 m_speed,并提供一个访问器和更改器方法 */
	CC_SYNTHESIZE(Vec2, m_speed, Speed)
	CC_SYNTHESIZE(float, m_health, Health)

	/*	获取击杀这个飞机应得的分数 */
	CC_SYNTHESIZE_READONLY(int, m_score, Score)
	/*	对Enemy造成伤害，如果生命低于0，则自动调用down方法 */ 
	bool hit(float);
protected:
	/*	播放爆炸动画并将它从父节点删除 */
	virtual void playExplodeAnimationAndDie() = 0;
	/*	播放飞行过程中动画 */
	virtual void playFlyAnimation() = 0;
	/*	播放被击中的动画 */
	virtual void playHitAnimation() = 0;
	
};

class SmallEnemy : public Enemy {
public:
	static SmallEnemy* create();
protected:
	virtual void playFlyAnimation()override;
	virtual void playHitAnimation()override;
	virtual void playExplodeAnimationAndDie()override;
};

class MiddleEnemy : public Enemy {
public:
	static MiddleEnemy* create();
protected:
	virtual void playFlyAnimation()override;
	virtual void playHitAnimation()override;
	virtual void playExplodeAnimationAndDie()override;
};

class BigEnemy : public Enemy {
public:
	static BigEnemy* create();
protected:
	virtual void playFlyAnimation()override;
	virtual void playHitAnimation()override;
	virtual void playExplodeAnimationAndDie()override;
};