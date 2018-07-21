#include "GameScene.h"
#include "Constant.h"
#include <time.h>

Scene* GameScene::createScene() {
	return GameScene::create();
}

bool GameScene::init() {
	if (!Scene::init())
		return false;
	
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
	auto hero = Sprite::createWithSpriteFrame(
		spriteCache->getSpriteFrameByName("hero1.png"));
	hero->setPosition(size.width / 2, size.height / 5);
	this->addChild(hero, FOREGROUND_ZORDER, HERO_TAG);

	////////////////////////////// �ɻ�����: ��������(��������Ӷ���֡,ʱ���ʹ���);��װΪ����;����
	auto heroAni = Animation::create();
	heroAni->addSpriteFrame(spriteCache->getSpriteFrameByName("hero2.png"));
	heroAni->addSpriteFrame(spriteCache->getSpriteFrameByName("hero1.png"));
	heroAni->setDelayPerUnit(0.2f);
	heroAni->setLoops(CC_REPEAT_FOREVER); // ����ѭ��
	auto animate = Animate::create(heroAni);
	hero->runAction(animate);


	////////////////////////////// ��Ӵ����¼��Ĵ���(�����������󣬱�д�߼���ע�������)
	auto listener = EventListenerTouchOneByOne::create();
	// lambda���ʽ [](){};
	// []�б�ʾ���ⲿ�����Ŀ��ƣ�=:���а�ֵ���ݣ�&:���а����ô���, �����ֶ����ϱ���������ֵ����
	listener->onTouchBegan = [hero, this](Touch* touch, Event* event) {
		auto touchPos = touch->getLocation();
		//log("Touch Began...[%f,%f]", touchPos.x, touchPos.y);
		//auto move = MoveTo::create(0.5f, touchPos);
		//hero->runAction(move);
		// �жϴ���λ���Ƿ���hero��
		if (!hero->boundingBox().containsPoint(touchPos))
			return false;
		this->m_offset = touchPos - hero->getPosition();
		return true; 
	};
	listener->onTouchMoved = [=](Touch *touch, Event* event) {
		auto touchPos = touch->getLocation();
		//log("Touch Moved...[%f,%f]", touchPos.x, touchPos.y);
		//// �ƶ�delta��ô���λ�ã�������ֱ���ƶ�λ�õ������λ��(��ֹδ�����ͼ���Ķ�˲�Ƶ����)
		// ���ַ������������Ʊ߽�
		//hero->setPosition(hero->getPosition() + touch->getDelta());
		hero->setPosition(touchPos - m_offset);

		// �ж��Ƿ���磨ֱ�������ڱ߽緶Χ�ڣ�
		auto rect = hero->getContentSize()/2;
		hero->setPositionX(MIN(size.width - rect.width, hero->getPositionX()));
		hero->setPositionX(MAX(rect.width, hero->getPositionX()));
		hero->setPositionY(MIN(size.height - rect.height, hero->getPositionY()));
		hero->setPositionY(MAX(rect.height, hero->getPositionY()));
	};
	listener->onTouchEnded = [](Touch *touch, Event* event) {
		auto touchPos = touch->getLocation();
		//log("Touch Ended...[%f,%f]", touchPos.x, touchPos.y);
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, hero);
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
	auto spBomb = Sprite::createWithSpriteFrameName("bomb.png");
	auto itemBomb = MenuItemSprite::create(spBomb, spBomb, [](Ref*) {
		log("boooooooooooooooooo");
	});
	auto menu = Menu::create();

	auto lblBomb = Label::createWithBMFont("font.fnt", StringUtils::format("X%d", this->m_bombCount));
	lblBomb->setPosition(itemBomb->getPosition() + Vec2(itemBomb->getContentSize().width,0));
	this->addChild(lblBomb);
	menu->addChild(itemBomb);
	this->addChild(menu,UI_ZORDER);

	scheduleUpdate();

	/////////////////////////// �ӵ�
	// auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	// bullet->setPosition(hero->getPositionX(), hero->getPositionY() + hero->getContentSize().height / 2);
	// this->addChild(bullet, 1, 4);
	//�µĶ�ʱ��-��ʱ�����ӵ�(��update���ƶ���ɾ��)
	schedule(schedule_selector(GameScene::createBullet), CREATE_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createEnemy), CREATE_SMALLENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_SMALLENEMY_DELAY);
//	schedule(schedule_selector(GameScene::createMiddleEnemy), CREATE_MIDDLE_ENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_MIDDLE_ENEMY_DELAY);
//	schedule(schedule_selector(GameScene::createBigEnemy), CREATE_BIG_ENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_BIG_ENEMY_DELAY);
	schedule(schedule_selector(GameScene::createUFO), CREATE_BIGENEMY_INTERVAL);

	srand((unsigned int)time(NULL));
	return true;
	
}

void GameScene::update(float delta) {
	float speed = 1.5f;
	cycleBackground(1, 2, speed);
	//auto bullet = getChildByTag(4);
	//shoot(3*speed);
	// �����ӵ�
	Vector<Sprite *> removableBullets;
	for (auto bullet : m_bullets) {
		bullet->setPositionY(bullet->getPositionY() + speed * 4);
		if (bullet->getPositionY() >= 
			Director::getInstance()->getVisibleSize().height + bullet->getContentSize().height/2) {
			this->removeChild(bullet);
			// �����ڱ�������ʱ�޸ļ��ϳ�Ա����,������ʱ��ŵ�һ����ʧЧ���ϡ���
			removableBullets.pushBack(bullet);
		}
	}

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
		for (auto bullet : m_bullets) {
			if (removableBullets.contains(bullet))
				continue;
			if (enemy->getBoundingBox().intersectsRect(bullet->getBoundingBox())) {
				removableBullets.pushBack(bullet);
				this->removeChild(bullet);
				if (enemy->hit(HERO_DAMAGE)) {
					removableEnemies.pushBack(enemy);
					this->m_totalScore += enemy->getScore();
					auto lblScore = static_cast<Label*>(this->getChildByTag(LABEL_SCORE_TAG));
					lblScore->setString(StringUtils::format("%d", m_totalScore));
					lblScore->setPositionY(SIZE.height - lblScore->getContentSize().height / 2);
					break;
				}
			}
		}
		// ��hero��ײ���
		if (enemy->getBoundingBox().intersectsRect(
			this->getChildByTag(HERO_TAG)->getBoundingBox())) {
			//
		}
	}
	for (auto bullet : removableBullets) {
		m_bullets.eraseObject(bullet);
	}
	removableBullets.clear();
	for (auto enemy : removableEnemies) {
		m_enemies.eraseObject(enemy);
	}
	removableEnemies.clear();
}

void GameScene::createEnemy(float) {
	auto enemy = SmallEnemy::create();
	enemy->setPositionY(SIZE.height + enemy->getContentSize().height/2);
	float minX = enemy->getContentSize().width / 2;
	float maxX = SIZE.width - minX;
	float x = rand() % (int)(maxX - minX + 1) + minX; // ���磬Ҫ�õ�0��3����Ҫģ(3+1)
	enemy->setPositionX(x);
	this->addChild(enemy);
	m_enemies.pushBack(enemy);
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
void GameScene::createBullet(float delta) {
	auto hero = getChildByTag(HERO_TAG);
	auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	bullet->setPosition(hero->getPositionX(), hero->getPositionY() + hero->getContentSize().height / 2);
	this->addChild(bullet, 1, 4);
	m_bullets.pushBack(bullet);
}
void GameScene::createUFO(float delta) {
	/////////////////////////// ����
	auto ufo = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ufo1.png"));
	auto minX = ufo->getContentSize().width / 2;
	auto maxX = SIZE.width;
	ufo->setPosition(rand() % (int)(maxX - minX + 1) + minX, SIZE.height + ufo->getContentSize().height / 2);
	this->addChild(ufo, FOREGROUND_ZORDER, UFO_TAG_1);
	auto move1 = MoveBy::create(1, Vec2(0, -300));
	ufo->runAction(Sequence::create(move1, move1->reverse(), nullptr));

}
//void GameScene::cycleBackground(int aim_tag, int other_tag, float speed) {
//	// Ҳ���Բ���1��2һ�����µ�����2�����׺��1��2�Żس�ʼλ�ã������жϱȽϼ�
//	auto aim = this->getChildByTag(aim_tag);
//	auto other = this->getChildByTag(other_tag);
//	aim->setPositionY(aim->getPositionY() - speed);
//	if (aim->getPositionY()+aim->getContentSize().height <= 0)
//		aim->setPositionY(other->getPositionY()+aim->getContentSize().height-2 );
//}
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

//void GameScene::shoot(float speed) {
//	auto plane = this->getChildByTag(0);
//	static const int N = 50;
//	static const int interval = 10;
//	if (bullets.size() == 0) {
//		for (int i = 0; i < N; i++){
//			bullets.push_back(Sprite::createWithSpriteFrame(
//				SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet1.png")));
//			this->addChild(bullets[i], interval*(i-N-1));
//			bullets[i]->setPosition(plane->getPositionX(), 
//				plane->getPositionY() + plane->getContentSize().height / 2);
//		}
//	}
//	for (int i = 0; i < N; i++){
//		if (bullets[i]->getZOrder() < 0) {
//			bullets[i]->setZOrder(bullets[i]->getZOrder() + 1); 
//			bullets[i]->setPosition(plane->getPositionX(),
//				plane->getPositionY() + plane->getContentSize().height / 2);
//		}
//		else {
//			bullets[i]->setPositionY(bullets[i]->getPositionY() + speed);
//			if (bullets[i]->getPositionY() > Director::getInstance()->getVisibleSize().height) {
//				bullets[i]->setPosition(plane->getPositionX(), plane->getPositionY()
//					+ plane->getContentSize().height / 2);
//				bullets[i]->setZOrder(bullets[(i+1)%N]->getZOrder()-interval);
//			}
//		}
//	}
//}