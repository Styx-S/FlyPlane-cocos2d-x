#pragma once

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;

class GameScene : public Scene {
public:
	GameScene() :m_offset(Vec2::ZERO), m_totalScore(0) {}
	static Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameScene)
		
	void update(float) override;
private:
	Vec2 m_offset;
	Vector<Sprite*> m_bullets;
	Vector<Enemy*> m_enemies;
	int m_bombCount;
	int m_totalScore;
	void cycleBackground(int, int, float);
	//void shoot(float);
	void createBullet(float);
	void createEnemy(float);
	void createSmallEnemy(float);
	void createMiddleEnemy(float);
	void createBigEnemy(float);
	void createUFO(float);
};