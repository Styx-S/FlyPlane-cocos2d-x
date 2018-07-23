#pragma once
#include "ConfigUtil.h"
#define ORIGIN		Director::getInstance()->getVisibleOrigin()
#define SIZE		Director::getInstance()->getVisibleSize()
// Hero颜色，白色为0，蓝色为2，红色为1
#define HERO_COLOR ConfigUtil::getInstance()->getInteger("HERO_COLOR_DEFAULT")

// 标签
#define BACKGROUND_TAG_1		1
#define BACKGROUND_TAG_2		2
#define HERO_TAG 3
#define LABEL_SCORE_TAG			10
#define UFO_TAG_1				20
#define MENU_TAG	11
#define	ITEM_BOMB_TAG	12
#define LABEL_BOMB_TAG	13
#define	ITEM_TOGGLE_TAG	14

// ZORDER
#define BACKGROUND_ZORDER		-1
#define DEFAULT_ZORDER			0
#define FOREGROUND_ZORDER		1
#define UI_ZORDER				99

// 速度
#define BACKGROUND_SPEED		ConfigUtil::getInstance()->getFloat("BACKGROUND_SPEED_DEFAULT")
#define BULLET_SPEED			ConfigUtil::getInstance()->getFloat("BULLET_SPEED_DEFAULT")
#define SMALL_ENEMY_SPEED		ConfigUtil::getInstance()->getFloat("SMALL_ENEMY_SPEED_DEFAULT")
#define MIDDLE_ENEMY_SPEED		ConfigUtil::getInstance()->getFloat("MIDDLE_ENEMY_SPEED_DEFAULT")
#define BIG_ENEMY_SPEED			ConfigUtil::getInstance()->getFloat("BIG_ENEMY_SPEED_DEFAULT")
#define BULLET_FLASH_SPEED		ConfigUtil::getInstance()->getFloat("BULLET_FLASH_SPEED_DEFAULT")

// 血量
#define SMALL_ENEMY_HEALTH		ConfigUtil::getInstance()->getFloat("SMALL_ENEMY_HEALTH_DEFAULT")
#define MIDDLE_ENEMY_HEALTH		ConfigUtil::getInstance()->getFloat("MIDDLE_ENEMY_HEALTH_DEFAULT")
#define BIG_ENEMY_HEALTH		ConfigUtil::getInstance()->getFloat("BIG_ENEMY_HEALTH_DEFAULT")
#define HERO_DAMAGE				ConfigUtil::getInstance()->getFloat("HERO_DAMAGE_DEFAULT")

// 分数
#define SMALL_ENEMY_SCORE		ConfigUtil::getInstance()->getInteger("SMALL_ENEMY_SCORE_DEFAULT")
#define MIDDLE_ENEMY_SCORE		ConfigUtil::getInstance()->getInteger("MIDDLE_ENEMY_SCORE_DEFAULT")
#define BIG_ENEMY_SCORE			ConfigUtil::getInstance()->getInteger("BIG_ENEMY_SCORE_DEFAULT")

// 定时器间隔

#define CREATE_BULLET_INTERVAL				ConfigUtil::getInstance()->getFloat("CREATE_BULLET_INTERVAL_DEFAULT")
#define CREATE_SMALLENEMY_INTERVAL			ConfigUtil::getInstance()->getFloat("CREATE_SMALLENEMY_INTERVAL_DEFAULT")
#define CREATE_MIDDLEENEMY_INTERVAL			ConfigUtil::getInstance()->getFloat("CREATE_MIDDLEENEMY_INTERVAL_DEFAULT")
#define CREATE_BIGENEMY_INTERVAL			ConfigUtil::getInstance()->getFloat("CREATE_BIGENEMY_INTERVAL_DEFAULT")
#define CREATE_UFO_1_INTERVAL				ConfigUtil::getInstance()->getFloat("CREATE_UFO_1_INTERVAL_DEFAULT")
#define	CREATE_SORMENEMYBYBIGENEMY_INTERVAL	ConfigUtil::getInstance()->getFloat("CREATE_SORMENEMYBYBIGENEMY_INTERVAL_DEFAULT")
#define CREATE_SMALLENEMY_DELAY				ConfigUtil::getInstance()->getFloat("CREATE_SMALLENEMY_DELAY_DEFAULT")
#define CREATE_MIDDLEENEMY_DELAY			ConfigUtil::getInstance()->getFloat("CREATE_MIDDLEENEMY_DELAY_DEFAULT")
#define CREATE_BIGENEMY_DELAY				ConfigUtil::getInstance()->getFloat("CREATE_BIGENEMY_DELAY_DEFAULT")

#define CREATE_INCREASINGDIFFICLUTY_INTERVAL 0.5f

#define CREATE_SORMENEMYBYBIGENEMY_DELAY	ConfigUtil::getInstance()->getFloat("CREATE_SORMENEMYBYBIGENEMY_DELAY_DEFAULT")


// 动画播放时间
#define LOADING_TIME_PER_FRAME				0.25f
#define HERO_FLy_TIME_PER_FRAME				0.2f
#define HERO_DIE_TIME_PER_FRAME				0.2f
#define ENEMY_EXPLODE_TIME_PER_FRAME		0.2f
#define ENEMY_FLY_ANIMATION_TIME_PER_FRAME	0.2f
#define ENEMY_HIT_ANIMATION_TIME_PER_FRAME	0.1f
#define UFO_FIRSTDOWN_TIME        0.7f   //道具第一次下来的时间
#define UFO_UP_TIME				  2.0f   //道具第一次上去的时间
#define UFO_SECONDDOWN_TIME       1.0f   //道具第二次下来的时间

// 动画缓存槽
#define HERO_FLY_ANIMATION				"HERO_FLY"
#define HERO_DIE_ANIMATION				"HERO_DIE"
#define SMALLENEMY_EXPLODE_ANIMATION	"SMALLENEMY_EXPLODE"
#define MIDDLEENEMY_HIT_ANIMATION		"MIDDLEENEMY_HIT"
#define MIDDLEENEMY_EXPLODE_ANIMATION	"MIDDLEENEMY_EXPLODE"
#define BIGENEMY_FLY_ANIMATION			"BIGENEMY_FLY"
#define BIGENEMY_HIT_ANIMATION			"BIGENEMY_HIT"
#define BIGENEMY_EXPLODE_ANIMATION		"BIGENEMY_EXPLODE"

// 键值对-键名
#define HIGH_SCORE_KEY "HighScore"

//道具随机出现的范围
#define UFO_RAND_RANGE 100
	
//道具随机出现的范围
#define UFO_RAND_RANGE 100
//两种子弹数
#define MUILBULLET_NUM	100
#define FLASHBULLET_NUM  50

//挑战模式创造怪物次数
#define CHALLANGE_LOOPS  10