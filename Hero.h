#pragma once

#include "cocos2d.h"
#include "Constant.h"
#include"Enemy.h"
#include"Ammunition.h"

USING_NS_CC;

class Hero : public Sprite {
public:
	bool initWithFrame();           //飞机的初始化与创造
	static Hero* createHero();

	Vec2	move( Vec2 );
	void 	creatBullets(Scene*);
	void	moveBullets( ); //移动所有子弹,每帧调用
	bool	isHit(Enemy*);
	bool	isStrike(Enemy*);
private:
	Vec2 m_offset;							//记录触摸点与飞机中心的偏移量 解决点击飞机周围造成的瞬移
	EventListenerTouchOneByOne* Listener;	//移动函数的监听器方便暂停时候取消监听
	float m_maxSpeed;						//limit move
	Ammunition* amm;

	Hero();
};
