#include "OverScene.h"
#include "Constant.h"
#include "GameScene.h"
#include "AudioEngine.h"
#include "SelectScene.h"

using namespace experimental;

Scene* OverScene::createScene(int score)
{
	auto scene = new OverScene();
	if (scene && scene->init(score))
	{
		scene->autorelease();
		return scene;
	}
	delete scene;
	scene = nullptr;
	return nullptr;
}

bool OverScene::init(int score)
{
	do
	{
		CC_BREAK_IF(!Scene::init());
		AudioEngine::play2d("game_over.mp3");

		auto bg = Sprite::createWithSpriteFrameName("gameover.png");
		bg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		bg->setPosition(0, SIZE.height);
		this->addChild(bg, BACKGROUND_ZORDER);

		auto highScore = UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE_KEY, 0);
		auto lblHighScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", highScore));
		lblHighScore->setPosition(ORIGIN + Vec2(SIZE.width / 2, SIZE.height / 5 * 4));
		this->addChild(lblHighScore, UI_ZORDER);
		lblHighScore->setColor(Color3B::BLACK);
		if (highScore < score)
		{
			highScore = score;
			UserDefault::getInstance()->setIntegerForKey(HIGH_SCORE_KEY, highScore);
			auto seq = Sequence::create(
				ScaleTo::create(1, 5),
				CallFuncN::create([highScore](Node *node) {
				dynamic_cast<Label*>(node)->setString(StringUtils::format("%d", highScore));
			}),
				ScaleTo::create(1, 1),
				nullptr);
			lblHighScore->runAction(seq);
		}

		auto lblScore = Label::createWithBMFont("font.fnt", StringUtils::format("%d", score));
		lblScore->setPosition(ORIGIN + Vec2(SIZE.width / 2, SIZE.height / 3));
		this->addChild(lblScore, UI_ZORDER);
		lblScore->setColor(Color3B::BLACK);
		lblScore->setBMFontSize(60);

		auto spRestart = Sprite::createWithSpriteFrameName("btn_finish.png");
		auto itemRestart = MenuItemSprite::create(spRestart, spRestart, [](Ref*) {
			auto scene = SelectScene::createScene();
			Director::getInstance()->replaceScene(scene);
			AudioEngine::play2d("button.mp3");
		});
		itemRestart->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		itemRestart->setPosition(SIZE.width - 20, 20);

		auto menu = Menu::create(itemRestart, nullptr);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, UI_ZORDER);

		return true;
	} while (0);
	return false;
}