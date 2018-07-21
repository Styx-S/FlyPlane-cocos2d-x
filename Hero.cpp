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

Vec2	Hero::move(Vec2) {
	//��Ӵ����¼����� (�ɻ��ƶ����¼�)
	//1,����һ���¼�����
	auto lintener = EventListenerTouchOneByOne::create();   //Touch��ʾ���� allatonceֻ����һ��  oneByone������ 
	//onTouchBegin������ʼ ���ַ���ֵ��ֻ�п�ʼ�ɹ��� ���к����¼���
	//onTouchMoved�����ƶ�ʱ onTouchEnded��������ʱ  onTouchCancelled����������ʱ����ʱ
	//2.�ֽ��¼��������߼�
	//a.������ʼʱ
	//lambada���ʽ��[]���ֿ��ƶ��ⲿ�����ķ��ʣ�����һ��һ���Ĵ���
	//Ҳ����дһ��[=]����ʾ�ⲿ���б���ֵ���ݽ��������Է��ʣ������ܽ����޸�
	//������дһ��[&]��ַ������ʾ�ⲿ���б����������ô��ݽ������������Է��ʻ����޸�
	lintener->onTouchBegan = [=](Touch* touch, Event* event) {     //"�����ڲ����庯��"  С���ű�ʾ�����б� �����ű�ʾ����ֵ
		Vec2 touchPos = touch->getLocation();					//[]���Բ��������� �Ӷ�ʹ�ô������п���ʹ��[]�еĲ���
		log("Touch begin...");
		log("touch position is x: %f , y: %f", touchPos.x, touchPos.y);

		this->m_offset = this->getPosition() - touchPos;  //����ɻ�˲�Ʒ���1 ͨ�������λ��ȡ�ú�heroê���������
		bool isContains = this->getBoundingBox().containsPoint(touchPos);   //�жϴ��������Ƿ��ڷɻ���
		//ȡ�þ���ĵ��"����"  �жϲ����ĵ��Ƿ��ھ��������
		//hero->setPosition(touchPos);
		//auto move = MoveTo::create(2.0f, touchPos); //moveby����� moveto �Ǿ���
		//hero->runAction(move);
		return isContains;
	};
	//b.�����������ƶ�ʱ
	lintener->onTouchMoved = [=](Touch* touch, Event* event) {
		Vec2 touchPos = touch->getLocation();
		//Vec2 deltapos = touch->getDelta();   //��һ�δ���������һ�δ�����֮���������
		this->setPosition(touch->getLocation() + m_offset);

		auto minX = this->getContentSize().width / 2;
		this->setPositionX(MAX(this->getPositionX(), 0));
		this->setPositionX(MIN(SIZE.width - 0, this->getPositionX()));

		auto minY = this->getContentSize().height / 2;
		this->setPositionY(MAX(this->getPositionY(), 0));
		this->setPositionY(MIN(SIZE.height - 2 * minY, this->getPositionY()));

		//hero->setPosition(hero->getPosition() + deltapos); //�ɻ�ÿ���ƶ����������ڵ�ǰλ�ü�������ƶ�������
		//log("TouchMoved...");
	};
	//c.��������ʱ
	lintener->onTouchEnded = [](Touch* touch, Event* event) {
		log("TouchEnded...");
	};
	//3.ע��������ַ�����
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(lintener, this);
	//�õ��¼��ַ���
	Listener = lintener;
	return this->getPosition();
}	

bool Hero::isStrike(Enemy* enemy)
{

}