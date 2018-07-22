#pragma once

#include "cocos2d.h"
#include "Constant.h"
#include"Enemy.h"
#include"Ammunition.h"

USING_NS_CC;

class Hero : public Sprite {
public:
	bool initWithFrame();           //�ɻ��ĳ�ʼ���봴��
	static Hero* createHero();

	Vec2	move( Vec2 );
	void 	creatBullets(Scene*, float);
	void	moveBullets(float); //�ƶ������ӵ�,ÿ֡����
	bool	isHit(Enemy*);
	bool	isStrike(Enemy*); 
private:
	EventListenerTouchOneByOne* Listener;	//�ƶ������ļ�����������ͣʱ��ȡ������
	float m_maxSpeed;						//limit move
	Ammunition* amm;
};
