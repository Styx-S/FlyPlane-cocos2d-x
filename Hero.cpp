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

void Hero::setPause(bool x)   //������ͣ״̬�����ж�������ͣ״̬���޷�����
{
	this->isPause = x;
}

Vec2	Hero::move(Vec2 touchPos) {
		//�ƶ��ɻ���
	if (!isPause) {
		this->setPosition(touchPos);

		auto minX = this->getContentSize().width / 2;
		this->setPositionX(MAX(this->getPositionX(), 0));
		this->setPositionX(MIN(SIZE.width - 0, this->getPositionX()));

		auto minY = this->getContentSize().height / 2;
		this->setPositionY(MAX(this->getPositionY(), 0));
		this->setPositionY(MIN(SIZE.height - 2 * minY, this->getPositionY()));
	}
	return this->getPosition();
}	

bool Hero::isStrike(Enemy* enemy)
{
	if(!isPause)
		return m_amm->isHit(enemy);
}

bool Hero::isHit(Enemy* enemy)
{	
	if (this->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && !isPause )
	{
		return TRUE;
	}
	return FALSE;
}

void Hero::creatBullets(float delta, Scene* scene) {
	if(!isPause)
		m_amm->generateNewBullets(delta,scene,this);
}


void Hero::moveBullets(float delta){
	if (!isPause)
		this->m_amm->moveAllBullets(delta);
}