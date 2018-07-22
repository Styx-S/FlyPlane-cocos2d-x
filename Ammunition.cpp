#include "Ammunition.h"
void Ammunition::generateNewBullets(float delta, Scene* scene, Hero* hero) {
	auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	bullet->setPosition(hero->getPositionX(), hero->getPositionY() + hero->getContentSize().height / 2);
	scene->addChild(bullet);
	auto distance = bullet->getContentSize().height / 2 + SIZE.height - bullet->getPositionY();
	auto move = MoveBy::create(distance / BULLET_SPEED, Vec2(0, distance));
	bullet->runAction(move);
	m_bullets.pushBack(bullet);
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