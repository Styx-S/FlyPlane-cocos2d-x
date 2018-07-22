#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Hero.h"
#include "UFO.h"
USING_NS_CC;

class GameScene : public Scene {
private:
	Vec2 m_offset;  //触摸时触摸点距Hero锚点的位置
	Hero* m_hero;
	Vector<Enemy*> m_enemies;
	Vector<Ufo *>m_Ufos;
	bool m_isOver;		//判断游戏是否结束
	

	void changeBomb();
	void cycleBackground(int, int, float);
	void gameOver();
	
	void createUfo(float);
	void createBigEnemy(float);
	void createMiddleEnemy(float);
	void createSmallEnemy(float);
	void createBullets(float);

	void createSorMEnemyByBigEnemy(float);
	void createSmallEnemyByBigEnemy(Enemy* enemy);
	void createMiddleEnemyByBigEnemy(Enemy* enemy);
	void increasingDifficulty(float delta);
	bool isLevelUp();


	//Vector<Prop*> m_pros;
public:
	static Scene* createScene();
	CREATE_FUNC(GameScene)  //用宏创建对象
	bool init(); //all these are cocos function
	int m_totalScore;
	int m_bombCount;  //炸弹数
	bool isPause;	//需要判断游戏是否暂停
	int count;//

	void update(float)	override;
	void addEnemyToEnemies(Enemy*);
	
};