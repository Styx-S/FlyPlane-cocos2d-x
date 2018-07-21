#pragma once

#include "cocos2d.h"
#include "Constant.h"
USING_NS_CC;

class Enemy : public Sprite {
public:
 	//static Enemy* create() = 0;
	//bool initWithFrameName(const std::string&);
	void Enemy::move();

	/*	����һ��protected Vec2 m_speed,���ṩһ���������͸��������� */
	CC_SYNTHESIZE(Vec2, m_speed, Speed)
	CC_SYNTHESIZE(float, m_health, Health)

	/*	��ȡ��ɱ����ɻ�Ӧ�õķ��� */
	CC_SYNTHESIZE_READONLY(int, m_score, Score)
	/*	��Enemy����˺��������������0�����Զ�����down���� */ 
	bool hit(float);
protected:
	/*	���ŷ��й����ж��� */
	virtual void playFlyAnimation() = 0;
	/*	���ű����еĶ��� */
	virtual void playHitAnimation() = 0;
	/*	���ű�ը�����������Ӹ��ڵ�ɾ�� */
	virtual void playExplodeAnimationAndDie() = 0;

	virtual void _playFly(Animation*);
	virtual void _playhit(Animation*);
	virtual void _playEx(Animation*);
	
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