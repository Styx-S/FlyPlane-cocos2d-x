#pragma once

#include "cocos2d.h"
#include "Constant.h"
USING_NS_CC;

class Enemy : public Sprite {
public:
	/*	���������ٶ��ƶ��� */
	void Enemy::move();

	/*	��������Ĭ��λ�ã�Ϊ��Ļ�ϲ���ˮƽ��������ĵط�*/
	Vec2 setDefaultPositon();

	/*	����һ��protected Vec2 m_speed,���ṩһ���������͸��������� */
	CC_SYNTHESIZE(Vec2, m_speed, Speed)
	CC_SYNTHESIZE(float, m_health, Health)

	/*	��ȡ��ɱ����ɻ�Ӧ�õķ��� */
	CC_SYNTHESIZE_READONLY(int, m_score, Score)
	/*	��Enemy����˺��������������0�����Զ�����down���� */ 
	bool hit(float);
	/*	���ŷ��й����ж��� */
	virtual void playFlyAnimation() = 0;
	virtual bool isAbilityCallEnemy();
protected:
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
	virtual void playFlyAnimation()override;
protected:
	virtual void playHitAnimation()override;
	virtual void playExplodeAnimationAndDie()override;
	bool isAbilityCallEnemy()override;
};

class MiddleEnemy : public Enemy {
public:
	static MiddleEnemy* create();
	virtual void playFlyAnimation()override;
	bool isAbilityCallEnemy()override;
protected:
	virtual void playHitAnimation()override;
	virtual void playExplodeAnimationAndDie()override;
};

class BigEnemy : public Enemy {
public:
	static BigEnemy* create();
	virtual void playFlyAnimation()override;
	bool isAbilityCallEnemy()override;
protected:
	virtual void playHitAnimation()override;
	virtual void playExplodeAnimationAndDie()override;
};

class Aerolite :public Enemy {
public:
	static Aerolite* create();
	virtual void playFlyAnimation()override;
	bool isAbilityCallEnemy()override;
protected:
	virtual void playHitAnimation()override;
	virtual void playExplodeAnimationAndDie()override;

};

class LittleAerolite :public Enemy {
public:
	static LittleAerolite* create(const std::string&);
	virtual void playFlyAnimation()override;
	bool isAbilityCallEnemy()override;
	static Vec2 calculateAimBy(int index);
protected:
	virtual void playHitAnimation()override;
	virtual void playExplodeAnimationAndDie()override;

};