#include "Ammunition.h"
#include "math.h"
void Ammunition::generateNewBullets(float delta, Scene* scene, Sprite* hero) {
	
	for (auto numDirection = 0; numDirection < m_Direction.size(); numDirection++)
	{
		m_bullets.pushBack(this->generateSimpleBullet(delta, scene, hero, m_Direction[numDirection]));
	}
	;
	if (!m_effects.empty())   //�����ʱbuff��������Ԫ��
	{
		this->creatEffect(); //ʵ��buff
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

int Ammunition::addEffect_flashShoot(int effectCounts) {
	auto effect = new Effect{ EffectType::FLASH_SHOOT,effectCounts };
	m_bullet_speed = BULLET_FLASH_SPEED;
	isFlash = true;
	//effect ��Ҫdelete
	m_effects.push_back(effect);
	return effectCounts;
}

int Ammunition::addEffect_MultiShoot(int effectCounts) {
	auto effect = new Effect{ EffectType::MULTIPLY_SHOOT,effectCounts };
	//effect ��Ҫdelete
	m_effects.push_back(effect);
	m_numMulti++;
	return effectCounts;
}

void Ammunition::creatEffect() {
	Effect* t_effect = m_effects.front();  //��m_effectsȡ��һ��buff
	for (Effect* effect : m_effects)  //����������������buff������������ӵ���ȡ�����ӵ��������ӵ����ȷ��䣩
	{
		if (effect->type == EffectType::FLASH_SHOOT && effect->EffectCount >= 0)
			t_effect = effect;
	}
	switch (t_effect->type)
	{
	case EffectType::FLASH_SHOOT:
		if (t_effect->EffectCount > 0) {
			t_effect->EffectCount--;
			this->getDirection(1);
			//���øı��ӵ������ԣ������ӵ���
		}
		break;
	case EffectType::MULTIPLY_SHOOT:
		if (t_effect->EffectCount > 0) {
			t_effect->EffectCount--;
			this->getDirection(m_numMulti);   //����������ȡ�÷���ĺ���
			//���øı��ӵ������ԣ������ӵ���
		}
		break;
	default:
		break;
	}
	for (auto i = 0; i < m_effects.size(); i++)
	{
		if (m_effects[i]->EffectCount <= 0)
		{
			if (m_effects[i]->type == EffectType::MULTIPLY_SHOOT)   //������һ���������������-1
				this->m_numMulti--;
			if (m_effects[i]->type == EffectType::MULTIPLY_SHOOT)   //������һ�����������isFLASHΪfalse
				this->isFlash = false; // to-do
			delete m_effects[i];
			m_effects.erase(m_effects.begin() + i, m_effects.begin() + i + 1);
			//������ֵ�i��buff��Ӱ����Ϊ0 ��ɾ����Ԫ�أ���i��Ԫ�أ�
		}
	}
}