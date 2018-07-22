#include "Hero.h"
#include "AudioEngine.h"

using namespace experimental;

bool Hero::initWithFrame()
{
	std::string frameName = "hero1.png";
	seq_Count = 0;
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
	this->m_amm = new Ammunition();
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
		this->setPositionX(MAX(this->getPositionX(), this->getContentSize().width/2));
		this->setPositionX(MIN(this->getPositionX(), SIZE.width - this->getContentSize().width/2));

		auto minY = this->getContentSize().height / 2;
		this->setPositionY(MAX(this->getPositionY(), this->getContentSize().height/2));
		this->setPositionY(MIN(SIZE.height - this->getContentSize().height/2, this->getPositionY()));

	}
	return this->getPosition();
}

bool Hero::isStrike(Enemy* enemy)
{
	if (this->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && !isPause)
	{
		return TRUE;
	}
	return FALSE;
}

bool Hero::isHit(Enemy* enemy)
{
	if (!isPause)
		return m_amm->isHit(enemy);
}

void Hero::creatBullets(float delta, Scene* scene){
	seq_Count ++;    //��Ƶ
	if (!isPause)
	{
		log("isFlash? %d", this->m_amm->isFlash);
		if (this->m_amm->isFlash)
		{
			if (seq_Count >= 3) {
				m_amm->generateNewBullets(delta, scene, this);
				seq_Count = 0;
			}
		}
		if (!this->m_amm->isFlash)
		{
			if (seq_Count >= 10) {
				m_amm->generateNewBullets(delta, scene, this);
				seq_Count = 0;
			}
		}
		AudioEngine::play2d("bullet.mp3");
	}
		
}


void Hero::moveBullets(float delta) {
	if (!isPause)
		this->m_amm->moveAllBullets(delta);
}