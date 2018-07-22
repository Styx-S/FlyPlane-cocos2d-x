#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Hero.h"

#include <vector>
USING_NS_CC;
using std::vector;

// 子弹效果(不对子弹数量生效的无需放在这)
enum class EffectType {
	MULTIPLY_SHOOT, //多行射击
	FLASH_SHOOT // 闪电射击
};

typedef struct Effect {
	EffectType type;
	int EffectCount;
};

class Ammunition {
public:

	// 剩余受道具buff的子弹数量 (如果有多种buff，应该做成队列)
	//CC_SYNTHESIZE(vector<Effect> , m_effects, Speed)

	/*	移动当前所有子弹 
		@param float 与上次调用的间隔
	*/
	void moveAllBullets(float delta);
	// 在创建子弹时绑定移动动画，则只需检测是否出界
	/*	生成新子弹 
		@param float 与上次调用的间隔
		@param Scene* 要将新子弹添加到的场景
	*/
	void generateNewBullets(float delta, Scene*, Hero*);

	// 遍历所有子弹检查是否与enemy碰撞
	bool isHit(Enemy* enemy);

	// 闪电射速
	// 多排射击
	//int addEffect_MultiShoot(int effectCounts);
private:
	Vector<Sprite*> m_bullets;
	
	// 移除在屏幕外的子弹
	void checkBulletsInVisibleSize();
};