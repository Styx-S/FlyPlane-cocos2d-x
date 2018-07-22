#include "Hero.h"

bool Hero::initWithFrame()
{
	std::string frameName = "hero1.png";
	if (!Sprite::initWithSpriteFrameName(frameName))
	{
		return false;
	}
	/*�ӻ�����ȡ�ö���*/
	auto  ani = AnimationCache::getInstance()->getAnimation(HERO_FLY_ANIMATION);
	//2.��������װΪ����
	auto animator = Animate::create(ani);

	//3.�������ж���
	this->runAction(animator);
	return true;
}

Hero* Hero::createHero() {
	auto hero = new Hero();
	if (hero && hero->initWithFrame())
	{
		hero->autorelease(); //�����Զ�������  
		return hero;
	}

	delete hero;
	hero = nullptr;
	return nullptr;
}

Vec2	Hero::move(Vec2 touchPos) {
		//�ƶ��ɻ���
		this->setPosition(touchPos);

		auto minX = this->getContentSize().width / 2;
		this->setPositionX(MAX(this->getPositionX(), 0));
		this->setPositionX(MIN(SIZE.width - 0, this->getPositionX()));

		auto minY = this->getContentSize().height / 2;
		this->setPositionY(MAX(this->getPositionY(), 0));
		this->setPositionY(MIN(SIZE.height - 2 * minY, this->getPositionY()));

	return this->getPosition();
}	

bool Hero::isStrike(Enemy* enemy)
{
	return amm->isHit(enemy);
}

bool Hero::isHit(Enemy* enemy)
{	
	if (this->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
	{
		return TRUE;
	}
	return FALSE;
}