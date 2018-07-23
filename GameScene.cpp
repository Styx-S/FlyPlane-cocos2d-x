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

	time_count = 0;
	isChallange = false;

	this->m_isVoiceOn = true;

	count = 1;

	AudioEngine::play2d("game_music.mp3", true, 0.4f);
	auto director = Director::getInstance();
	auto spriteCache = SpriteFrameCache::getInstance();
	auto origin = director->getVisibleOrigin();
	auto size = director->getVisibleSize();
	// 读入图集
	// 迁移到LoadingScene spriteCache->addSpriteFramesWithFile("shoot_background.plist");
	// 从图集中取得精灵
	auto background = Sprite::createWithSpriteFrame(
		spriteCache->getSpriteFrameByName("background.png"));
	auto otherBg = Sprite::createWithSpriteFrame(
		spriteCache->getSpriteFrameByName("background.png"));
	// 锚点: 将精灵本地坐标转为全局坐标的基准点
	// 默认为（0.5,0.5）即将精灵的中心对正Position
	// 设置为（0,0） 那么setPosition即是设置精灵左下角的位置
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	otherBg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	otherBg->setPositionY(background->getContentSize().height-1);
	// 不使用锚点的方式
	//background->setPosition(director->getVisibleSize().width / 2,
	//	background->getContentSize().height / 2);

	// 开启抗锯齿
	background->getTexture()->setAntiAliasTexParameters();
	otherBg->getTexture()->setAntiAliasTexParameters();

	this->addChild(background, BACKGROUND_ZORDER, BACKGROUND_TAG_1);
	this->addChild(otherBg, BACKGROUND_ZORDER, BACKGROUND_TAG_2);

	// spriteCache->addSpriteFramesWithFile("shoot.plist");
	/*auto hero = Sprite::createWithSpriteFrame(
		spriteCache->getSpriteFrameByName("hero1.png"));*/
	m_hero = Hero::createHero();
	m_hero->setPosition(size.width / 2, size.height / 5);
	if (HERO_COLOR == 1)
	{
		m_hero->setColor(Color3B::RED);
	}
	else if (HERO_COLOR == 2)
	{
		m_hero->setColor(Color3B::BLUE);
	}
	this->addChild(m_hero, FOREGROUND_ZORDER, HERO_TAG);

	////////////////////////////// 添加触摸事件的处理(创建监听对象，编写逻辑，注册监听器)
	auto listener = EventListenerTouchOneByOne::create();
	// lambda表达式 [](){};
	// []中表示对外部变量的控制，=:所有按值传递，&:所有按引用传递, 或者手动加上变量名，按值传递
	auto hero = this->m_hero;
	listener->onTouchBegan = [hero, this](Touch* touch, Event* event) {
		auto touchPos = touch->getLocation();
		//log("Touch Began...[%f,%f]", touchPos.x, touchPos.y);
		//auto move = MoveTo::create(0.5f, touchPos);
		//hero->runAction(move);
		// 判断触摸位置是否在hero上
		if (!m_hero->boundingBox().containsPoint(touchPos))
			return false;
		this->m_offset =  m_hero->getPosition() - touchPos;
		return true; 
	};
	listener->onTouchMoved = [=](Touch *t, Event* e) {
		if (Director::getInstance()->isPaused() && this->m_isOver)	return;

		Vec2 touchPos = t->getLocation();
		//Vec2 deltaPos = t->getDelta();	//上一次触摸点与这一次触摸点之间的向量差		
		//log("Touch Moved");
		hero->move(touchPos + m_offset);
		//hero->setPosition(deltaPos + hero->getPosition());
	};
	listener->onTouchEnded = [](Touch *touch, Event* event) {
		//auto touchPos = touch->getLocation();
		//log("Touch Ended...[%f,%f]", touchPos.x, touchPos.y);
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_hero);
	/////////////////////////// UI
	// 计分
	auto lblScore = Label::createWithBMFont("font.fnt",
		StringUtils::format("%d", this->m_totalScore));
	lblScore->setAnchorPoint(Vec2(0.5, 1));
	lblScore->setPositionX(SIZE.width/2);
	lblScore->setPositionY(SIZE.height - lblScore->getContentSize().height / 2);
	lblScore->setColor(Color3B::BLACK);
	this->addChild(lblScore, UI_ZORDER, LABEL_SCORE_TAG);

	// 炸弹UI

	//炸弹菜单
	auto spBomb = Sprite::createWithSpriteFrameName("bomb.png");
	auto itemBomb = MenuItemSprite::create(spBomb, spBomb, [this, lblScore](Ref *) {
		//如果游戏处于暂停状态，就不响应
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


	//暂停菜单
	auto spPauseNormal = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto spPauseSelected = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	auto spResumeNormal = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto spResumeSelected = Sprite::createWithSpriteFrameName("game_resume_pressed.png");
	auto itemPause = MenuItemSprite::create(spPauseNormal, spPauseSelected);
	auto itemResume = MenuItemSprite::create(spResumeNormal, spResumeSelected);
	auto toggle = MenuItemToggle::createWithCallback([this](Ref *sender) {
		//获取当前选择项的下标(从0开始)
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

	auto notQuiet = Sprite::createWithSpriteFrameName("voice.png");
	auto Quiet = Sprite::createWithSpriteFrameName("no_voice.png");
	auto itemQuiet = MenuItemSprite::create(Quiet, Quiet);
	auto itemNotQuiet = MenuItemSprite::create(notQuiet, notQuiet);
	auto tog = MenuItemToggle::createWithCallback([this](Ref *sender) {
		int index = dynamic_cast<MenuItemToggle *>(sender)->getSelectedIndex();
		if (index)
		{
			this->m_isVoiceOn = false;
		}
		else
		{
			this->m_isVoiceOn = true;
		}
	}, itemQuiet, itemNotQuiet, nullptr);
	tog->setPosition(tog->getContentSize().width, SIZE.height - 50);



	//炸弹菜单
	auto menu = Menu::create();
	menu->addChild(itemBomb, FOREGROUND_ZORDER, ITEM_BOMB_TAG);
	menu->addChild(toggle);
	menu->addChild(tog);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, UI_ZORDER, MENU_TAG);

	auto lblBomb = Label::createWithBMFont("font.fnt", StringUtils::format("X%d", this->m_bombCount));
	lblBomb->setPosition(itemBomb->getPosition() + Vec2(40, 0));
	this->addChild(lblBomb, UI_ZORDER, LABEL_BOMB_TAG);
	lblBomb->setColor(Color3B(100, 10, 10));
	lblBomb->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	//初始化菜单项和标签的显示
	this->changeBomb();

	scheduleUpdate();

	/////////////////////////// 子弹
	// auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	// bullet->setPosition(hero->getPositionX(), hero->getPositionY() + hero->getContentSize().height / 2);
	// this->addChild(bullet, 1, 4);
	//新的定时器-定时创建子弹(在update中移动和删除)
	schedule(schedule_selector(GameScene::createBullets), CREATE_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createSmallEnemy), CREATE_SMALLENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_SMALLENEMY_DELAY);
	schedule(schedule_selector(GameScene::createMiddleEnemy), CREATE_MIDDLEENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_MIDDLEENEMY_DELAY);
	schedule(schedule_selector(GameScene::createBigEnemy), CREATE_BIGENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_BIGENEMY_DELAY);
	schedule(schedule_selector(GameScene::createUfo), CREATE_UFO_1_INTERVAL, CC_REPEAT_FOREVER,1.0f);
	schedule(schedule_selector(GameScene::createSorMEnemyByBigEnemy), CREATE_SORMENEMYBYBIGENEMY_INTERVAL, CC_REPEAT_FOREVER, CREATE_SORMENEMYBYBIGENEMY_DELAY);


	//动态难度
	schedule(schedule_selector(GameScene::increasingDifficulty), CREATE_INCREASINGDIFFICLUTY_INTERVAL, CC_REPEAT_FOREVER,1.0f);
	srand((unsigned int)time(NULL));
	return true;
	
}

void GameScene::update(float delta) {
	float speed = 1.5f;
	cycleBackground(1, 2, speed);
	//auto bullet = getChildByTag(4);
	//shoot(3*speed);

	m_hero->moveBullets(delta);
	if (isChallange)
	{
		schedule(schedule_selector(GameScene::createSmallEnemy),0.3f, CHALLANGE_LOOPS,0);
		schedule(schedule_selector(GameScene::createMiddleEnemy),2.0f, CHALLANGE_LOOPS, 0);
		schedule(schedule_selector(GameScene::createBigEnemy),3.0f, CHALLANGE_LOOPS, 0);
		this->time_count++;
		if (time_count == 1800)
		{
			log("30s later....");
			this->isChallange = false;
			this->time_count = 0;
		}
	}
	

	if (this->m_isVoiceOn)
	{
		AudioEngine::resumeAll();
	}
	else if (!this->m_isVoiceOn)
	{
		AudioEngine::pauseAll();
	}

	// 遍历敌机
	Vector<Enemy *> removableEnemies;
	for (auto enemy : m_enemies) {
		enemy->move();
		if (enemy->getPositionY() <= -enemy->getContentSize().height / 2) {
			this->removeChild(enemy);
			removableEnemies.pushBack(enemy);
		}
	}

	// 碰撞检测
	for (auto enemy : m_enemies) {
		if (removableEnemies.contains(enemy))
			continue;
		// 与子弹碰撞检测
		if (m_hero->isHit(enemy))
		{
			if (enemy->getHealth() <= 0)
			{
				removableEnemies.pushBack(enemy);
				this->m_totalScore += enemy->getScore();
				auto lblScore = static_cast<Label*>(this->getChildByTag(LABEL_SCORE_TAG));
				lblScore->setString(StringUtils::format("%d", m_totalScore));
				lblScore->setPositionY(SIZE.height - lblScore->getContentSize().height / 2);
			}
			else
			{
				//
			}


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
		// 与hero碰撞检测
		if (m_hero->isStrike(enemy))
		{
			this->gameOver();
			enemy->hit(10000);
		}
	}

	for (auto enemy : removableEnemies) {
		m_enemies.eraseObject(enemy);
	}
	removableEnemies.clear();

	Vector<Ufo *>removableUFO;
	for (auto Ufo : m_Ufos)
	{

		if (Ufo->getPositionY() + Ufo->getContentSize().height / 2 <= 0)  //道具越界
		{
			removableUFO.pushBack(Ufo);
			this->removeChild(Ufo);
		}
		if (Ufo->getBoundingBox().intersectsRect(m_hero->getBoundingBox()))  //道具与飞机碰撞
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
				break;
			case UfoType::MONSTER_UFO:	
				this->challangeStart();
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
void GameScene::createMiddleEnemyByBigEnemy(Enemy* enemy) {
	auto middleEnemy = MiddleEnemy::create();
	middleEnemy->playFlyAnimation();
	middleEnemy->setPositionX(enemy->getPosition().x);
	middleEnemy->setPositionY(enemy->getPosition().y - enemy->getContentSize().height / 2);
	this->addChild(middleEnemy);
	m_enemies.pushBack(middleEnemy);	
}

void GameScene::createSmallEnemyByBigEnemy(Enemy* enemy) {
	auto smallEnemy1 = SmallEnemy::create();
	smallEnemy1->playFlyAnimation();
	smallEnemy1->setPositionY(enemy->getPosition().y - enemy->getContentSize().height / 2);
	smallEnemy1->setPositionX(enemy->getPositionX());
	this->addChild(smallEnemy1);
	m_enemies.pushBack(smallEnemy1);

	auto smallEnemy2 = SmallEnemy::create();
	smallEnemy2->playFlyAnimation();
	smallEnemy2->setPositionY(enemy->getPosition().y - enemy->getContentSize().height / 2);
	smallEnemy2->setPositionX(enemy->getPositionX() - enemy->getContentSize().width / 2);
	this->addChild(smallEnemy2);
	m_enemies.pushBack(smallEnemy2);

	auto smallEnemy3 = SmallEnemy::create();
	smallEnemy3->playFlyAnimation();
	smallEnemy3->setPositionY(enemy->getPosition().y - enemy->getContentSize().height / 2);
	smallEnemy3->setPositionX(enemy->getPositionX() + enemy->getContentSize().width / 2);
	this->addChild(smallEnemy3);
	m_enemies.pushBack(smallEnemy3);
	
}
void GameScene::createSorMEnemyByBigEnemy(float delta) {
	for (auto enemy : m_enemies) {
		if (enemy->isAbilityCallEnemy() && enemy->getPositionY() < SIZE.height - enemy->getContentSize().height)
			 {
			auto randNum = rand() % 2;
			switch (randNum)
				{
			case 0:
				this->createSmallEnemyByBigEnemy(enemy);
				break;
			case 1:
				this->createMiddleEnemyByBigEnemy(enemy);
				break;
			default:
				break;
				}
			break;
		}
	}
}

void GameScene::cycleBackground(int bg1_tag, int bg2_tag, float speed) {
	auto bg1 = this->getChildByTag(bg1_tag);
	auto bg2 = this->getChildByTag(bg2_tag);
	float HEIGHT = bg1->getContentSize().height;
	float bg1Y = bg1->getPositionY();
	// 在屏幕以外则无需移动
	if (bg1Y > -HEIGHT)
		bg1->setPositionY(bg1Y - speed);
	float bg2Y = bg2->getPositionY();
	if (bg2Y <= 0){
		// 重置为初始位置
		bg1->setPositionY(0);
		bg2->setPositionY(HEIGHT - 1);
	}
	else bg2->setPositionY(bg2Y - speed);
}


/*
1.当炸弹数为0时，菜单项和标签都不显示
2.当炸弹数为1时，只显示菜单项
3.当炸弹数大于1时，显示菜单项和标签，且更新标签显示内容
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
	m_hero->setPause(true);
	//1.设置成员变量m_isOver为true
	this->m_isOver = true;
	//2.道具还在跑
	for (auto node : this->getChildren())
	{
		node->stopAllActions();
	}
	//3.执行爆炸动画
	auto aniHero = AnimationCache::getInstance()->getAnimation(HERO_DIE_ANIMATION);
	auto seq = Sequence::create(Animate::create(aniHero), CallFunc::create([this]() {
		//4.跳转场景
		auto scene = OverScene::createScene(this->m_totalScore);
		Director::getInstance()->replaceScene(scene);
	}), nullptr);
	m_hero->runAction(seq);
	//5.停止所有定时器
	this->unscheduleAllCallbacks();
}


void GameScene::createBullets(float a)
{
	AudioEngine::play2d("bullet.mp3");
	m_hero->creatBullets(a,this);
}

void GameScene::createUfo(float)
{
	int Ufo_rand = rand() % 4;
	std::string frameName;
	int X_RAND;               //道具出现的随机范围
	UfoType type;
	switch (Ufo_rand)
	{
	case 0:
		type = UfoType::BOMB_UFO;
		frameName = "ufo2.png";
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
	Ufo->setPosition(x, SIZE.height + Ufo->getContentSize().height / 2); //随机产生位置
	this->addChild(Ufo, UI_ZORDER);
	this->m_Ufos.pushBack(Ufo);
	//通过顺序序列 让道具先下来再上去
	  
	//log("RAND_X is %d", X_RAND);
	auto movedown = MoveTo::create(UFO_FIRSTDOWN_TIME, Vec2(Ufo->getPositionX(), (SIZE.height - SIZE.height / 2)));
	Ufo->setPositionX(Ufo->getPositionX() + X_RAND);
	auto moveup = MoveTo::create(UFO_UP_TIME, Vec2(Ufo->getPositionX(), (SIZE.height + SIZE.height / 4)));
	Ufo->setPositionX(Ufo->getPositionX() + X_RAND);
	auto Ufodown = MoveTo::create(UFO_SECONDDOWN_TIME, Vec2(Ufo->getPositionX(), (0 - Ufo->getContentSize().height)));
	auto seq = Sequence::create(movedown, moveup, Ufodown, RemoveSelf::create(), nullptr);
	Ufo->runAction(seq);
}


void GameScene::challangeStart() {
	this->isChallange = true;
}


void GameScene::increasingDifficulty(float delta)
{
	if (GameScene::isLevelUp())
	{
		ConfigUtil::getInstance()->setFloat("BACKGROUND_SPEED_DEFAULT", BACKGROUND_SPEED * 1.1);
		ConfigUtil::getInstance()->setFloat("SMALL_ENEMY_SPEED_DEFAULT", SMALL_ENEMY_SPEED * 1.1);
		ConfigUtil::getInstance()->setFloat("MIDDLE_ENEMY_SPEED_DEFAULT", MIDDLE_ENEMY_SPEED * 1.1);
		ConfigUtil::getInstance()->setFloat("BIG_ENEMY_SPEED_DEFAULT", BIG_ENEMY_SPEED * 1.1);
		ConfigUtil::getInstance()->setFloat("SMALL_ENEMY_HEALTH_DEFAULT", SMALL_ENEMY_HEALTH * 1.1);
		ConfigUtil::getInstance()->setFloat("MIDDLE_ENEMY_HEALTH_DEFAULT", MIDDLE_ENEMY_HEALTH * 1.1);
		ConfigUtil::getInstance()->setFloat("BIG_ENEMY_HEALTH_DEFAULT", BIG_ENEMY_HEALTH * 1.1);
		ConfigUtil::getInstance()->setFloat("CREATE_SMALLENEMY_INTERVAL_DEFAULT", CREATE_SMALLENEMY_INTERVAL * 0.9);
		ConfigUtil::getInstance()->setFloat("CREATE_MIDDLEENEMY_INTERVAL_DEFAULT", CREATE_MIDDLEENEMY_INTERVAL * 0.9);
		ConfigUtil::getInstance()->setFloat("CREATE_BIGENEMY_INTERVAL_DEFAULT", CREATE_BIGENEMY_INTERVAL * 0.9);
	}
	
}

bool GameScene::isLevelUp()
{
	
	if (this->m_totalScore - 20 * count >= 0)
	{
		count += 1;
		return true;
	}
	return false;
}