#pragma once
#define CLASS_HERO_H

#include "cocos2d.h"
#include "Constant.h"
#include "Ammunition.h"
#include "Enemy.h"

USING_NS_CC;


class Hero : public Sprite {
public:
	bool initWithFrame();           //�ɻ��ĳ�ʼ���봴��
	static Hero* createHero();

	Vec2	move(Vec2);
	void 	creatBullets(float, Scene*);
	void	moveBullets(float); //�ƶ������ӵ�,ÿ֡����
	void    setPause(bool);
	bool	isHit(Enemy*);
	bool	isStrike(Enemy*);
private:	
	float m_maxSpeed;						//limit move
	int	  seq_Count;		//��Ƶ��

	Ammunition* m_amm;
	bool  isPause;
};