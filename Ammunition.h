#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Hero.h"

#include <vector>
USING_NS_CC;
using std::vector;

// �ӵ�Ч��(�����ӵ�������Ч�����������)
enum class EffectType {
	MULTIPLY_SHOOT, //�������
	FLASH_SHOOT // �������
};

typedef struct Effect {
	EffectType type;
	int EffectCount;
};

class Ammunition {
public:

	// ʣ���ܵ���buff���ӵ����� (����ж���buff��Ӧ�����ɶ���)
	//CC_SYNTHESIZE(vector<Effect> , m_effects, Speed)

	/*	�ƶ���ǰ�����ӵ� 
		@param float ���ϴε��õļ��
	*/
	void moveAllBullets(float delta);
	// �ڴ����ӵ�ʱ���ƶ���������ֻ�����Ƿ����
	/*	�������ӵ� 
		@param float ���ϴε��õļ��
		@param Scene* Ҫ�����ӵ���ӵ��ĳ���
	*/
	void generateNewBullets(float delta, Scene*, Hero*);

	// ���������ӵ�����Ƿ���enemy��ײ
	bool isHit(Enemy* enemy);

	// ��������
	// �������
	//int addEffect_MultiShoot(int effectCounts);
private:
	Vector<Sprite*> m_bullets;
	
	// �Ƴ�����Ļ����ӵ�
	void checkBulletsInVisibleSize();
};