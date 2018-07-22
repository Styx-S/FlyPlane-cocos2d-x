#include "Ammunition.h"
#include "math.h"
void Ammunition::generateNewBullets(float delta, Scene* scene, Sprite* hero) {
	
	for (auto numDirection = 0; numDirection < m_Direction.size(); numDirection++)
	{
		m_bullets.pushBack(this->generateSimpleBullet(delta, scene, hero, m_Direction[numDirection]));
	}
	;
	if (isFlash)
	{
		this->downLevel(UfoType::FLASH_UFO);
	}
	else {
		this->downLevel(UfoType::MULTIPLY_UFO);
	}
}

Sprite*	 Ammunition::generateSimpleBullet(float delta, Scene* scene, Sprite* hero, float Dir) {
	auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	bullet->setPosition(hero->getPositionX(), hero->getPositionY() + hero->getContentSize().height / 5);
	bullet->setRotation(Dir);   //�ӷ��򼯺���ѡ���� �������ӵ�����
	auto distance = bullet->getContentSize().height / 2 + SIZE.height - bullet->getPositionY();
	auto move = MoveBy::create(distance / m_bullet_speed, Vec2(distance * sin(Dir * (3.1415926 / 180.0f)), distance));
	//m_bulletmove.push_back(move);
	bullet->runAction(move);
	scene->addChild(bullet);
	return bullet;
}

void Ammunition::moveAllBullets(float delta) {
	checkBulletsInVisibleSize();
}

bool Ammunition::isHit(Enemy* enemy) {
	for (auto bullet : m_bullets) {
		if (enemy->getBoundingBox().intersectsRect(bullet->getBoundingBox())) {
			enemy->hit(HERO_DAMAGE);
			m_bullets.eraseObject(bullet);
			bullet->removeFromParentAndCleanup(true);
			return true;
		}
	}
	return false;
}

void Ammunition::checkBulletsInVisibleSize() {
	Vector<Sprite *> removableBullets;
	for (auto bullet : m_bullets) {
		if (bullet->getPositionY() >=
			Director::getInstance()->getVisibleSize().height + bullet->getContentSize().height / 2) {
			bullet->removeFromParent();
			// �����ڱ�������ʱ�޸ļ��ϳ�Ա����,������ʱ��ŵ�һ����ʧЧ���ϡ���
			removableBullets.pushBack(bullet);
		}
	}
	for (auto bullet : removableBullets) {
		m_bullets.eraseObject(bullet);
	}
}

void Ammunition::getDirection(int numMulti){ //ͨ�������ı䷽�򼯺�
	switch (numMulti)
	{
	case 1:		m_Direction = {0.0f};     //һ��ʱֻ��0���ӵ�
		break;
	case 2:		m_Direction = { -60.0f,60.0f };  //����ʱ ��ƫ60 ����ƫ60�� ��������
		break;
	case 3:     m_Direction = { -60.0f,0.0f,60.0f }; //����ʱ �����л��� �м��һ��
		break;
	case 4:		m_Direction = { -60.0f,-30.0f,30.0f,60.0f };//4��ʱ���Ų�
		break;
	default:	m_Direction = { -60.0f,-30.0f,0.0f,30.0f,60.0f };///Ĭ�ϳ������Ŷ�Ϊ5�ţ�
		break;
	}
}


void Ammunition::upLevel(UfoType type) {  //�Ե���������
	switch (type)
	{
	case UfoType::FLASH_UFO:
	{
		log("UP Flash");
		m_flashBulletsCount += FLASHBULLET_NUM;
		log("flahbullnum is %d", m_flashBulletsCount);
		isFlash = true;
		log("isFlash? %d", isFlash);
		m_numMulti = 3; //�����ӵ�Ĭ��3��
		m_Direction = { -60.0f,0.0f,60.0f };
		
	}
		break;
	case UfoType::MULTIPLY_UFO:
		if (m_numMulti == 5) {   //5���ӵ���¼5��buffʣ�µ��ӵ���
			m_Direction = { -60.0f,-30.0f,0.0f,30.0f,60.0f };
			this->m_5BulletsCount = MUILBULLET_NUM;
		}
		if (m_numMulti == 4) {
			this->m_numMulti++;
			m_Direction = { -60.0f,-30.0f,0.0f,30.0f,60.0f };
			this->m_5BulletsCount = MUILBULLET_NUM + m_4BulletsCount;
		}
		if (m_numMulti == 3) {
			this->m_numMulti++;
			m_Direction = { -60.0f,-30.0f,30.0f,60.0f };
			this->m_4BulletsCount = MUILBULLET_NUM + m_3BulletsCount;
		}
		if (m_numMulti == 2) {
			this->m_numMulti++;
			m_Direction = { -60.0f,0.0f,60.0f };
			this->m_3BulletsCount = MUILBULLET_NUM + m_2BulletsCount;
		}
		if (m_numMulti == 1) {
			this->m_numMulti++;
			this->m_Direction = { -60.0f,60.0f };
			this->m_2BulletsCount = MUILBULLET_NUM;
		}
		break;
	default:
		break;
	}
}

void Ammunition::downLevel(UfoType type) {
	switch (type)
	{
	case UfoType::FLASH_UFO: {
		if (m_flashBulletsCount >= 0) {
			isFlash = true;
			this->m_flashBulletsCount--;
		}
		else {
			this->isFlash = false;
			this->downLevel(UfoType::MULTIPLY_UFO);
		}
	}
		break;
	case UfoType::MULTIPLY_UFO:
	{
		if (m_flashBulletsCount >= 0) {  //����������ӵ�
			this->downLevel(UfoType::FLASH_UFO);
		}
		if (m_5BulletsCount >= 0)    //5��buff�ӵ������ȼ� ��5���ӵ���ʼ����
		{
			this->m_5BulletsCount--;
			if (m_5BulletsCount == 0)
			{
				m_Direction = { -60.0f,-30.0f,30.0f,60.0f };
				m_numMulti--;
			}
		}
		else if (m_4BulletsCount >= 0)
		{
			this->m_4BulletsCount--;
			if (m_4BulletsCount == 0)
			{
				m_Direction = { -60.0f,0.0f,60.0f };
				m_numMulti--;
			}
		}
		else if (m_3BulletsCount >= 0)
		{
			this->m_3BulletsCount--;
			if (m_3BulletsCount == 0)
			{
				m_Direction = { -60.0f,0.0f,60.0f };
				m_numMulti--;
			}
		}
		else if (m_2BulletsCount >= 0)
		{
			this->m_2BulletsCount--;
			if (m_2BulletsCount == 0)
			{
				m_Direction = { -60.0f,60.0f };
				m_numMulti--;
			}
		}
		else 
		{
			this->m_numMulti = 1;
			m_Direction = { 0.0f };
		}
	}
		break;
	default:
		break;
	}
}