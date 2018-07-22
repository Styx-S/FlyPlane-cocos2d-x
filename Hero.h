#pragma once
#define CLASS_HERO_H

#include "cocos2d.h"
#include "Constant.h"
#include "Ammunition.h"
#include "Enemy.h"

USING_NS_CC;


class Hero : public Sprite {
public:
	bool initWithFrame();           //飞机的初始化与创造
	static Hero* createHero();

	Vec2	move(Vec2);
	void 	creatBullets(float, Scene*);
	void	moveBullets(float); //移动所有子弹,每帧调用
	void    setPause(bool);
	bool	isHit(Enemy*);
	bool	isStrike(Enemy*);
private:	
	float m_maxSpeed;						//limit move
	int	  seq_Count;		//分频器

	Ammunition* m_amm;
	bool  isPause;
};