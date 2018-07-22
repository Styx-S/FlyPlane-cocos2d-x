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

<<<<<<< HEAD
Vec2	Hero::move(Vec2 touchPos) {
		//�ƶ��ɻ���
=======
void Hero::setPause(bool x)   //������ͣ״̬�����ж�������ͣ״̬���޷�����
{
	this->isPause = x;
}

Vec2	Hero::move(Vec2 touchPos) {
		//�ƶ��ɻ���
	if (!isPause) {
>>>>>>> fd7d4409816f4f0e2f14a1c6f70cc02d2b34a4bf
		this->setPosition(touchPos);

		auto minX = this->getContentSize().width / 2;
		this->setPositionX(MAX(this->getPositionX(), 0));
		this->setPositionX(MIN(SIZE.width - 0, this->getPositionX()));

		auto minY = this->getContentSize().height / 2;
		this->setPositionY(MAX(this->getPositionY(), 0));
		this->setPositionY(MIN(SIZE.height - 2 * minY, this->getPositionY()));
<<<<<<< HEAD

=======
	}
>>>>>>> fd7d4409816f4f0e2f14a1c6f70cc02d2b34a4bf
	return this->getPosition();
}	

bool Hero::isStrike(Enemy* enemy)
{
<<<<<<< HEAD
	return m_amm->isHit(enemy);
=======
	if(!isPause)
		return m_amm->isHit(enemy);
>>>>>>> fd7d4409816f4f0e2f14a1c6f70cc02d2b34a4bf
}

bool Hero::isHit(Enemy* enemy)
{	
<<<<<<< HEAD
	if (this->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
=======
	if (this->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && !isPause )
>>>>>>> fd7d4409816f4f0e2f14a1c6f70cc02d2b34a4bf
	{
		return TRUE;
	}
	return FALSE;
}

void Hero::creatBullets(float delta, Scene* scene) {
<<<<<<< HEAD
	m_amm->generateNewBullets(delta,scene,this);
}

void Hero::moveBullets(float delta){
	this->m_amm->moveAllBullets(delta);
=======
	if(!isPause)
		m_amm->generateNewBullets(delta,scene,this);
}


void Hero::moveBullets(float delta){
	if (!isPause)
		this->m_amm->moveAllBullets(delta);
>>>>>>> fd7d4409816f4f0e2f14a1c6f70cc02d2b34a4bf
}