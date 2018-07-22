#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include"UFO.h"
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
}Effect;

class Ammunition {
public:
	Ammunition() :m_numMulti(1) {
		m_Direction = { 0.0f };
		m_bullet_speed = BULLET_SPEED;
		m_2BulletsCount = 0;	//2�ӵ�������
		m_3BulletsCount = 0;	//3�ӵ�������
		m_4BulletsCount = 0;	//4���ӵ�������
		m_5BulletsCount = 0;	//5�ӵ�������
		m_flashBulletsCount = 0;	 //ǿ���ӵ�������
		isFlash = false;
	};
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
	Sprite* generateSimpleBullet(float delta, Scene*, Sprite*, float);
	// ���������ӵ�����Ƿ���enemy��ײ
	bool isHit(Enemy* enemy);
	void getDirection(int);  //ͨ��������������� ���ӵ�֮��ĽǶ�
	// ��������
	// �������

	void upLevel(UfoType type);  //�Ե���������
	void downLevel(UfoType type); //���ߺľ�����
	bool  isFlash;			//�ж��Ƿ�Ϊ�����ӵ�״̬
private:
	int m_numMulti;
	float m_bullet_speed;
	//�����ӵ�������
	Vector<Sprite*> m_bullets;
	//�����ӵ��ĽǶ�
	vector<float>	m_Direction;

	int m_2BulletsCount;	//2�ӵ�������
	int m_3BulletsCount;	//3�ӵ�������
	int m_4BulletsCount;	//4���ӵ�������
	int m_5BulletsCount;	//5�ӵ�������
	int m_flashBulletsCount;	 //ǿ���ӵ�������
	// �Ƴ�����Ļ����ӵ�
	void checkBulletsInVisibleSize();
};