#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Hero.h"
#include "UFO.h"
USING_NS_CC;

class GameScene : public Scene {
private:
	Vec2 m_offset;  //����ʱ�������Heroê���λ��
	Hero* m_hero;
	Vector<Enemy*> m_enemies;
	Vector<Ufo *>m_Ufos;
	bool m_isOver;		//�ж���Ϸ�Ƿ����
	

	void changeBomb();
	void cycleBackground(int, int, float);
	void gameOver();
	
	void createUfo(float);
	void createBigEnemy(float);
	void createMiddleEnemy(float);
	void createSmallEnemy(float);
	void createBullets(float);
	//Vector<Prop*> m_pros;
public:
	static Scene* createScene();
	CREATE_FUNC(GameScene)  //�ú괴������
	bool init(); //all these are cocos function
	int m_totalScore;
	int m_bombCount;  //ը����
	bool isPause;	//��Ҫ�ж���Ϸ�Ƿ���ͣ

	void update(float)	override;
	
};