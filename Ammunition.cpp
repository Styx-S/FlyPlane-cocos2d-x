#include "Ammunition.h"
#include "math.h"
void Ammunition::generateNewBullets(float delta, Scene* scene, Sprite* hero) {
	
	for (auto numDirection = 0; numDirection < m_Direction.size(); numDirection++)
	{
		m_bullets.pushBack(this->generateSimpleBullet(delta, scene, hero, m_Direction[numDirection]));
	}
	;
	if (!m_effects.empty())   //如果此时buff向量中有元素
	{
		this->creatEffect(); //实现buff
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

int Ammunition::addEffect_flashShoot(int effectCounts) {
	auto effect = new Effect{ EffectType::FLASH_SHOOT,effectCounts };
	m_bullet_speed = BULLET_FLASH_SPEED;
	isFlash = true;
	//effect 需要delete
	m_effects.push_back(effect);
	return effectCounts;
}

int Ammunition::addEffect_MultiShoot(int effectCounts) {
	auto effect = new Effect{ EffectType::MULTIPLY_SHOOT,effectCounts };
	//effect 需要delete
	m_effects.push_back(effect);
	m_numMulti++;
	return effectCounts;
}

void Ammunition::creatEffect() {
	Effect* t_effect = m_effects.front();  //从m_effects取第一个buff
	for (Effect* effect : m_effects)  //遍历接下来的所有buff，如果有闪电子弹就取闪电子弹（闪电子弹优先发射）
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
			//设置改变子弹的属性（闪电子弹）
		}
		break;
	case EffectType::MULTIPLY_SHOOT:
		if (t_effect->EffectCount > 0) {
			t_effect->EffectCount--;
			this->getDirection(m_numMulti);   //将行数放入取得方向的函数
			//设置改变子弹的属性（多排子弹）
		}
		break;
	default:
		break;
	}
	for (auto i = 0; i < m_effects.size(); i++)
	{
		if (m_effects[i]->EffectCount <= 0)
		{
			if (m_effects[i]->type == EffectType::MULTIPLY_SHOOT)   //消耗完一个多行射击就行数-1
				this->m_numMulti--;
			if (m_effects[i]->type == EffectType::MULTIPLY_SHOOT)   //消耗完一个闪电射击就isFLASH为false
				this->isFlash = false; // to-do
			delete m_effects[i];
			m_effects.erase(m_effects.begin() + i, m_effects.begin() + i + 1);
			//如果发现第i个buff的影响数为0 就删除此元素（第i个元素）
		}
	}
}