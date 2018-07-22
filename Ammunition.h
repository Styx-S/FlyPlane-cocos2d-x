#pragma once

#include "cocos2d.h"
#include "Enemy.h"

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
	Ammunition() :m_numMulti(1) {};
	// ʣ���ܵ���buff���ӵ����� (����ж���buff��Ӧ�����ɶ���)
	CC_SYNTHESIZE(vector<Effect *>, m_effects, Speed);

	/*	�ƶ���ǰ�����ӵ� 
		@param float ���ϴε��õļ��
	*/
	void moveAllBullets(float delta);
	// �ڴ����ӵ�ʱ���ƶ���������ֻ�����Ƿ����
	/*	�������ӵ� 
		@param float ���ϴε��õļ��
		@param Scene* Ҫ�����ӵ���ӵ��ĳ���
	*/
	void generateNewBullets(float delta, Scene*, Sprite*);

	void creatEffect();

	// ���������ӵ�����Ƿ���enemy��ײ
	bool isHit(Enemy* enemy);
	void getDirection(int);  //ͨ��������������� ���ӵ�֮��ĽǶ�
	// ��������
	// �������
	int addEffect_MultiShoot(int effectCounts);
	int addEffect_flashShoot(int effectCounts);
private:
	int m_numMulti;
	//�����ӵ�������
	Vector<Sprite*> m_bullets;
	//�����ӵ��ĽǶ�
	vector<float>	m_Direction;
	// �Ƴ�����Ļ����ӵ�
	void checkBulletsInVisibleSize();
};