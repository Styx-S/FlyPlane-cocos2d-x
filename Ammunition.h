#pragma once

#include "cocos2d.h"
#include "Enemy.h"

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
	Ammunition() :m_numMulti(1) {};
	// 剩余受道具buff的子弹数量 (如果有多种buff，应该做成队列)
	CC_SYNTHESIZE(vector<Effect *>, m_effects, Speed);

	/*	移动当前所有子弹 
		@param float 与上次调用的间隔
	*/
	void moveAllBullets(float delta);
	// 在创建子弹时绑定移动动画，则只需检测是否出界
	/*	生成新子弹 
		@param float 与上次调用的间隔
		@param Scene* 要将新子弹添加到的场景
	*/
	void generateNewBullets(float delta, Scene*, Sprite*);
	void creatEffect();
	// 遍历所有子弹检查是否与enemy碰撞
	bool isHit(Enemy* enemy);
	void getDirection(int);  //通过多排射击的排数 算子弹之间的角度
	// 闪电射速
	// 多排射击
	int addEffect_MultiShoot(int effectCounts);
	int addEffect_flashShoot(int effectCounts);
private:
	int m_numMulti;
	//储存子弹的行数
	Vector<Sprite*> m_bullets;
	//储存子弹的角度
	vector<float>	m_Direction;
	// 移除在屏幕外的子弹
	void checkBulletsInVisibleSize();
};