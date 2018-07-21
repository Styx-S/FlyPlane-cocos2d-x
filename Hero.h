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
	void 	creatBullets(Scene*);
	void	moveBullets( ); //�ƶ������ӵ�,ÿ֡����
	bool	isHit(Enemy*);
	bool	isStrike(Enemy*);
private:
	Vec2 m_offset;							//��¼��������ɻ����ĵ�ƫ���� �������ɻ���Χ��ɵ�˲��
	EventListenerTouchOneByOne* Listener;	//�ƶ������ļ�����������ͣʱ��ȡ������
	float m_maxSpeed;						//limit move
	Ammunition* amm;

	Hero();
};
