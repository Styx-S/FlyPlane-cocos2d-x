#include "GameScene.h"
#include "Constant.h"
#include "OverScene.h"
#include "AudioEngine.h"
#include <time.h>

using namespace experimental;

Scene* GameScene::createScene() {
	return GameScene::create();
}

bool GameScene::init() {
	if (!Scene::init())
		return false;

	AudioEngine::play2d("game_music.mp3", true, 0.4f);
	auto director = Director::getInstance();
	auto spriteCache = SpriteFrameCache::getInstance();
	auto origin = director->getVisibleOrigin();
	auto size = director->getVisibleSize();
	// ����ͼ��
	// Ǩ�Ƶ�LoadingScene spriteCache->addSpriteFramesWithFile("shoot_background.plist");
	// ��ͼ����ȡ�þ���
	auto background = Sprite::createWithSpriteFrame(
		spriteCache->getSpriteFrameByName("background.png"));
	auto otherBg = Sprite::createWithSpriteFrame(
		spriteCache->getSpriteFrameByName("background.png"));
	// ê��: �����鱾������תΪȫ������Ļ�׼��
	// Ĭ��Ϊ��0.5,0.5��������������Ķ���Position
	// ����Ϊ��0,0�� ��ôsetPosition�������þ������½ǵ�λ��
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	otherBg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	otherBg->setPositionY(background->getContentSize().height-1);
	// ��ʹ��ê��ķ�ʽ
	//background->setPosition(director->getVisibleSize().width / 2,
	//	background->getContentSize().height / 2);

	// ���������
	background->getTexture()->setAntiAliasTexParameters();
	otherBg->getTexture()->setAntiAliasTexParameters();

	this->addChild(background, BACKGROUND_ZORDER, BACKGROUND_TAG_1);
	this->addChild(otherBg, BACKGROUND_ZORDER, BACKGROUND_TAG_2);

	// spriteCache->addSpriteFramesWithFile("shoot.plist");
	/*auto hero = Sprite::createWithSpriteFrame(
		spriteCache->getSpriteFrameByName("hero1.png"));*/
	m_hero = Hero::createHero();
	m_hero->setPosition(size.width / 2, size.height / 5);
	this->addChild(m_hero, FOREGROUND_ZORDER, HERO_TAG);

	////////////////////////////// ��Ӵ����¼��Ĵ���(�����������󣬱�д�߼���ע�������)
	auto listener = EventListenerTouchOneByOne::create();
	// lambda���ʽ [](){};
	// []�б�ʾ���ⲿ�����Ŀ��ƣ�=:���а�ֵ���ݣ�&:���а����ô���, �����ֶ����ϱ���������ֵ����
	auto hero = this->m_hero;
	listener->onTouchBegan = [hero, this](Touch* touch, Event* event) {
		auto touchPos = touch->getLocation();
		//log("Touch Began...[%f,%f]", touchPos.x, touchPos.y);
		//auto move = MoveTo::create(0.5f, touchPos);
		//hero->runAction(move);
		// �жϴ���λ���Ƿ���hero��
		if (!m_hero->boundingBox().containsPoint(touchPos))
			return false;
		this->m_offset = touchPos - m_hero->getPosition();
		return true; 
	};
	listener->onTouchMoved = [=](Touch *t, Event* e) {
		if (Director::getInstance()->isPaused() && this->m_isOver)	return;

		Vec2 touchPos = t->getLocation();
		//Vec2 deltaPos = t->getDelta();	//��һ�δ���������һ�δ�����֮���������		
		//log("Touch Moved");
		hero->move(touchPos + m_offset);
		//hero->setPosition(deltaPos + hero->getPosition());

		auto minX = hero->getContentSize().width / 2;
		auto minY = hero->getContentSize().height / 2;
		auto maxX = SIZE.width - minX;
		auto maxY = 500;
		auto x = MAX(minX, MIN(maxX, hero->getPositionX()));
		auto y = MAX(minY, MIN(maxY, hero->getPositionY()));
		hero->setPosition(x, y);
	};
	listener->onTouchEnded = [](Touch *touch, Event* event) {
		//auto touchPos = touch->getLocation();
		//log("Touch Ended...[%f,%f]", touchPos.x, touchPos.y);
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_hero);
	/////////////////////////// UI
	// �Ʒ�
	auto lblScore = Label::createWithBMFont("font.fnt",
		StringUtils::format("%d", this->m_totalScore));
	lblScore->setAnchorPoint(Vec2(0.5, 1));
	lblScore->setPositionX(SIZE.width/2);
	lblScore->setPositionY(SIZE.height - lblScore->getContentSize().height / 2);
	lblScore->setColor(Color3B::BLACK);
	this->addChild(lblScore, UI_ZORDER, LABEL_SCORE_TAG);

	// ը��UI

	//ը���˵�
	auto spBomb = Sprite::createWithSpriteFrameName("bomb.png");
	auto itemBomb = MenuItemSprite::create(spBomb, spBomb, [this, lblScore](Ref *) {
		//�����Ϸ������ͣ״̬���Ͳ���Ӧ
		if (Director::getInstance()->isPaused() || this->m_isOver)	return;
		if (this->m_bombCount <= 0)	return;
		for (auto enemy : this->m_enemies)
		{
			enemy->hit(10000);
			this->m_totalScore += enemy->getScore();
		}
		this->m_enemies.clear();
		lblScore->setString(StringUtils::format("%d", this->m_totalScore));
		this->m_bombCount--;
		this->changeBomb();
	});
	itemBomb->setPosition(itemBomb->getContentSize());


	//��ͣ�˵�
	auto spPauseNormal = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto spPauseSelected = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	auto spResumeNormal = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto spResumeSelected = Sprite::createWithSpriteFrameName("game_resume_pressed.png");
	auto itemPause = MenuItemSprite::create(spPauseNormal, spPauseSelected);
	auto itemResume = MenuItemSprite::create(spResumeNormal, spResumeSelected);
	auto toggle = MenuItemToggle::createWithCallback([this](Ref *sender) {
		//��ȡ��ǰѡ������±�(��0��ʼ)
		int index = dynamic_cast<MenuItemToggle *>(sender)->getSelectedIndex();
		if (index)
		{
			Director::getInstance()->pause();
			m_hero->setPause(true);
			//listener->setEnabled(false);
			//itemBomb->setEnabled(false);
		}
		else
		{
			Director::getInstance()->resume();
			m_hero->setPause(false);
			//listener->setEnabled(true);
			//itemBomb->setEnabled(true);
		}
	}, itemPause, itemResume, nullptr);
	toggle->setPosition(SIZE - toggle->getContentSize());


	//ը���˵�
	auto menu = Menu::create();
	menu->addChild(itemBomb, FOREGROUND_ZORDER, ITEM_BOMB_TAG);
	menu->addChild(toggle);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, UI_ZORDER, MENU_TAG);

	auto lblBomb = Label::createWithBMFont("font.fnt", StringUtils::format("X%d", this->m_bombCount));
	lblBomb->setPosition(itemBomb->getPosition() + Vec2(40, 0));
	this->addChild(lblBomb, UI_ZORDER, LABEL_BOMB_TAG);
	lblBomb->setColor(Color3B(100, 10, 10));
	lblBomb->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	//��ʼ���˵���ͱ�ǩ����ʾ
	this->changeBomb();

	scheduleUpdate();

	/////////////////////////// �ӵ�
	// auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	// bullet->setPosition(hero->getPositionX(), hero->getPositionY() + hero->getContentSize().height / 2);
	// this->addChild(bullet, 1, 4);
	//�µĶ�ʱ��-��ʱ�����ӵ�(��update���ƶ���ɾ��)
	schedule(schedule_selector(GameScene::createBullets), CREATE_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createSmallEnemy), CREATE_SMALLENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_SMALLENEMY_DELAY);
	schedule(schedule_selector(GameScene::createMiddleEnemy), CREATE_MIDDLEENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_MIDDLEENEMY_DELAY);
	schedule(schedule_selector(GameScene::createBigEnemy), CREATE_BIGENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_BIGENEMY_DELAY);
	schedule(schedule_selector(GameScene::createUfo), CREATE_UFO_1_INTERVAL, CC_REPEAT_FOREVER,1.0f);

	srand((unsigned int)time(NULL));
	return true;
	
}

void GameScene::update(float delta) {
	float speed = 1.5f;
	cycleBackground(1, 2, speed);
	//auto bullet = getChildByTag(4);
	//shoot(3*speed);

	m_hero->moveBullets(delta);
	
	// �����л�
	Vector<Enemy *> removableEnemies;
	for (auto enemy : m_enemies) {
		enemy->move();
		if (enemy->getPositionY() <= -enemy->getContentSize().height / 2) {
			this->removeChild(enemy);
			removableEnemies.pushBack(enemy);
		}
	}

	// ��ײ���
	for (auto enemy : m_enemies) {
		if (removableEnemies.contains(enemy))
			continue;
		// ���ӵ���ײ���
		if (m_hero->isHit(enemy))
		{
			if (enemy->getHealth() <= 0)
			{
				removableEnemies.pushBack(enemy);
				enemy->hit(1);
			}
			else
			{
				enemy->hit(1);
			}

			this->m_totalScore += enemy->getScore();
			auto lblScore = static_cast<Label*>(this->getChildByTag(LABEL_SCORE_TAG));
			lblScore->setString(StringUtils::format("%d", m_totalScore));
			lblScore->setPositionY(SIZE.height - lblScore->getContentSize().height / 2);

		}
		//for (auto bullet : m_bullets) {
		//	if (removableBullets.contains(bullet))
		//		continue;
		//	if (enemy->getBoundingBox().intersectsRect(bullet->getBoundingBox())) {
		//		removableBullets.pushBack(bullet);
		//		this->removeChild(bullet);
		//		if (enemy->hit(HERO_DAMAGE)) {
		//			removableEnemies.pushBack(enemy);
		//			this->m_totalScore += enemy->getScore();
		//			auto lblScore = static_cast<Label*>(this->getChildByTag(LABEL_SCORE_TAG));
		//			lblScore->setString(StringUtils::format("%d", m_totalScore));
		//			lblScore->setPositionY(SIZE.height - lblScore->getContentSize().height / 2);
		//			break;
		//		}
		//	}
		//}
		// ��hero��ײ���
		/*if (m_hero->isStrike(enemy))
		{
			this->gameOver();
			enemy->hit(10000);
		}*/
	}

	for (auto enemy : removableEnemies) {
		m_enemies.eraseObject(enemy);
	}
	removableEnemies.clear();

	Vector<Ufo *>removableUFO;
	for (auto Ufo : m_Ufos)
	{

		if (Ufo->getPositionY() + Ufo->getContentSize().height / 2 <= 0)  //����Խ��
		{
			removableUFO.pushBack(Ufo);
			this->removeChild(Ufo);
		}
		if (Ufo->getBoundingBox().intersectsRect(m_hero->getBoundingBox()))  //������ɻ���ײ
		{
			switch (Ufo->getType())
			{
			case UfoType::BOMB_UFO: if (m_bombCount < 3) {
				this->m_bombCount++;
				this->changeBomb();
			}
				break;
			case UfoType::FLASH_UFO: 
				m_hero->m_amm->upLevel(UfoType::FLASH_UFO);
				log("get Flash");
				break;
			case UfoType::MONSTER_UFO:	
				break;
			case UfoType::MULTIPLY_UFO: 
				m_hero->m_amm->upLevel(UfoType::MULTIPLY_UFO);
				break;
			default:
				break;
			}
			removableUFO.pushBack(Ufo);
			this->removeChild(Ufo);
			
		}

	}

	for (auto Ufo : removableUFO)
	{
		m_Ufos.eraseObject(Ufo);

	}
	removableUFO.clear();
}

void GameScene::createBigEnemy(float) {
	auto bigEnemy = BigEnemy::create();
	bigEnemy->playFlyAnimation();
	bigEnemy->setDefaultPositon();
	this->addChild(bigEnemy);
	m_enemies.pushBack(bigEnemy);
}

void GameScene::createMiddleEnemy(float) {
	auto middleEnemy = MiddleEnemy::create();
	middleEnemy->playFlyAnimation();
	middleEnemy->setDefaultPositon();
	this->addChild(middleEnemy);
	m_enemies.pushBack(middleEnemy);
}

void GameScene::createSmallEnemy(float) {
	auto smallEnemy = SmallEnemy::create();
	smallEnemy->playFlyAnimation();
	smallEnemy->setDefaultPositon();
	this->addChild(smallEnemy);
	m_enemies.pushBack(smallEnemy);
}
//void GameScene::createSmallEnemy(float delta) {
//	this->createEnemy(EnemyType::SMALL_ENEMY);
//}
//void GameScene::createMiddleEnemy(float delta) {
//	this->createEnemy(EnemyType::MIDDLE_ENEMY);
//}
//void GameScene::createBigEnemy(float delta) {
//	this->createEnemy(EnemyType::BIG_ENEMY);
//}

/*void GameScene::createUFO(float delta) {
	/////////////////////////// ����
	auto ufo = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ufo1.png"));
	auto minX = ufo->getContentSize().width / 2;
	auto maxX = SIZE.width;
	ufo->setPosition(rand() % (int)(maxX - minX + 1) + minX, SIZE.height + ufo->getContentSize().height / 2);
	this->addChild(ufo, FOREGROUND_ZORDER, UFO_TAG_1);
	auto move1 = MoveBy::create(1, Vec2(0, -300));
	ufo->runAction(Sequence::create(move1, move1->reverse(), nullptr));
}*/

void GameScene::cycleBackground(int bg1_tag, int bg2_tag, float speed) {
	auto bg1 = this->getChildByTag(bg1_tag);
	auto bg2 = this->getChildByTag(bg2_tag);
	float HEIGHT = bg1->getContentSize().height;
	float bg1Y = bg1->getPositionY();
	// ����Ļ�����������ƶ�
	if (bg1Y > -HEIGHT)
		bg1->setPositionY(bg1Y - speed);
	float bg2Y = bg2->getPositionY();
	if (bg2Y <= 0){
		// ����Ϊ��ʼλ��
		bg1->setPositionY(0);
		bg2->setPositionY(HEIGHT - 1);
	}
	else bg2->setPositionY(bg2Y - speed);
}


/*
1.��ը����Ϊ0ʱ���˵���ͱ�ǩ������ʾ
2.��ը����Ϊ1ʱ��ֻ��ʾ�˵���
3.��ը��������1ʱ����ʾ�˵���ͱ�ǩ���Ҹ��±�ǩ��ʾ����
*/
void GameScene::changeBomb()
{
	auto menu = this->getChildByTag(MENU_TAG);
	auto itemBomb = menu->getChildByTag(ITEM_BOMB_TAG);
	auto lblBomb = this->getChildByTag(LABEL_BOMB_TAG);

	if (this->m_bombCount <= 0)
	{
		itemBomb->setVisible(false);
		lblBomb->setVisible(false);
	}
	else if (this->m_bombCount == 1)
	{
		itemBomb->setVisible(true);
		lblBomb->setVisible(false);
	}
	else
	{
		itemBomb->setVisible(true);
		lblBomb->setVisible(true);
		dynamic_cast<Label*>(lblBomb)->setString(StringUtils::format("X%d", this->m_bombCount));
	}
}


void GameScene::gameOver()
{
	//1.���ó�Ա����m_isOverΪtrue
	this->m_isOver = true;
	//2.���߻�����
	for (auto node : this->getChildren())
	{
		node->stopAllActions();
	}
	//3.ִ�б�ը����
	auto aniHero = AnimationCache::getInstance()->getAnimation(HERO_DIE_ANIMATION);
	auto seq = Sequence::create(Animate::create(aniHero), CallFunc::create([this]() {
		//4.��ת����
		auto scene = OverScene::createScene(this->m_totalScore);
		Director::getInstance()->replaceScene(scene);
	}), nullptr);
	m_hero->runAction(seq);
	//5.ֹͣ���ж�ʱ��
	this->unscheduleAllCallbacks();
}


void GameScene::createBullets(float a)
{
	m_hero->creatBullets(a,this);
}

void GameScene::createUfo(float)
{
	int Ufo_rand = rand() % 4;
	std::string frameName;
	int X_RAND;               //���߳��ֵ������Χ
	UfoType type;
	switch (Ufo_rand)
	{
	case 0:type = UfoType::MULTIPLY_UFO;
		frameName = "ufo1.png";
		/*type = UfoType::BOMB_UFO;
		frameName = "ufo2.png";*/
		break;
	case 1:		type = UfoType::FLASH_UFO;
		frameName = "flash.png";
		break;
	case 2:		type = UfoType::MONSTER_UFO;
		frameName = "kulo.png";
		break;
	case 3:		type = UfoType::MULTIPLY_UFO;
		frameName = "ufo1.png";
		break;
	default:
		break;
	}
	auto Ufo = Ufo::create(type);
	X_RAND = rand() % (UFO_RAND_RANGE + 1) - UFO_RAND_RANGE;
	float minX = Ufo->getContentSize().width / 2 + fabs(X_RAND);
	float maxX = SIZE.width - minX - fabs(X_RAND);
	float x = rand() % (int)(maxX - minX) + minX;
	Ufo->setPosition(x, SIZE.height + Ufo->getContentSize().height / 2); //�������λ��
	this->addChild(Ufo, UI_ZORDER);
	this->m_Ufos.pushBack(Ufo);
	//ͨ��˳������ �õ�������������ȥ
	  
	//log("RAND_X is %d", X_RAND);
	auto movedown = MoveTo::create(UFO_FIRSTDOWN_TIME, Vec2(Ufo->getPositionX(), (SIZE.height - SIZE.height / 2)));
	Ufo->setPositionX(Ufo->getPositionX() + X_RAND);
	auto moveup = MoveTo::create(UFO_UP_TIME, Vec2(Ufo->getPositionX(), (SIZE.height + SIZE.height / 4)));
	Ufo->setPositionX(Ufo->getPositionX() + X_RAND);
	auto Ufodown = MoveTo::create(UFO_SECONDDOWN_TIME, Vec2(Ufo->getPositionX(), (0 - Ufo->getContentSize().height)));
	auto seq = Sequence::create(movedown, moveup, Ufodown, RemoveSelf::create(), nullptr);
	Ufo->runAction(seq);
}