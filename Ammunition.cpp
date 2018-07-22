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
	bullet->setRotation(Dir);   //从方向集合中选择方向 并调整子弹方向
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
			// 不能在遍历集合时修改集合成员数量,所以暂时存放到一个“失效集合”中
			removableBullets.pushBack(bullet);
		}
	}
	for (auto bullet : removableBullets) {
		m_bullets.eraseObject(bullet);
	}
}

void Ammunition::getDirection(int numMulti){ //通过行数改变方向集合
	switch (numMulti)
	{
	case 1:		m_Direction = {0.0f};     //一行时只有0度子弹
		break;
	case 2:		m_Direction = { -60.0f,60.0f };  //两行时 左偏60 和右偏60度 两个方向
		break;
	case 3:     m_Direction = { -60.0f,0.0f,60.0f }; //三行时 在两行基础 中间加一行
		break;
	case 4:		m_Direction = { -60.0f,-30.0f,30.0f,60.0f };//4行时候排布
		break;
	default:	m_Direction = { -60.0f,-30.0f,0.0f,30.0f,60.0f };///默认超过五排都为5排，
		break;
	}
}


void Ammunition::upLevel(UfoType type) {  //吃到道具升级
	switch (type)
	{
	case UfoType::FLASH_UFO:
	{
		log("UP Flash");
		m_flashBulletsCount += FLASHBULLET_NUM;
		log("flahbullnum is %d", m_flashBulletsCount);
		isFlash = true;
		log("isFlash? %d", isFlash);
		m_numMulti = 3; //超级子弹默认3列
		m_Direction = { -60.0f,0.0f,60.0f };
		
	}
		break;
	case UfoType::MULTIPLY_UFO:
		if (m_numMulti == 5) {   //5种子弹记录5种buff剩下的子弹数
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
		if (m_flashBulletsCount >= 0) {  //如果有闪电子弹
			this->downLevel(UfoType::FLASH_UFO);
		}
		if (m_5BulletsCount >= 0)    //5种buff子弹有优先级 从5列子弹开始发射
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