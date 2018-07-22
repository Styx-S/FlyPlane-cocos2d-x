#include "ConfigUtil.h"
#include "DefaultConstant.h"

ConfigUtil* ConfigUtil::instance = nullptr;

ConfigUtil* ConfigUtil::getInstance() {
	if (ConfigUtil::instance == nullptr) {
		ConfigUtil::instance = new ConfigUtil();
		ConfigUtil::instance->init();
	}
	return ConfigUtil::instance;
}
void ConfigUtil::init() {
#define config UserDefault::getInstance()
	// 配置项不存在
	if (!UserDefault::isXMLFileExist()) {
		// 血量和速度
		config->setFloatForKey("BACKGROUND_SPEED_DEFAULT", BACKGROUND_SPEED_DEFAULT);
		config->setFloatForKey("BULLET_SPEED_DEFAULT", BULLET_SPEED_DEFAULT);
		config->setFloatForKey("SMALL_ENEMY_SPEED_DEFAULT", SMALL_ENEMY_SPEED_DEFAULT);
		config->setFloatForKey("MIDDLE_ENEMY_SPEED_DEFAULT", MIDDLE_ENEMY_SPEED_DEFAULT);
		config->setFloatForKey("BIG_ENEMY_SPEED_DEFAULT", BIG_ENEMY_SPEED_DEFAULT);
		config->setFloatForKey("SMALL_ENEMY_HEALTH_DEFAULT", SMALL_ENEMY_HEALTH_DEFAULT);
		config->setFloatForKey("MIDDLE_ENEMY_HEALTH_DEFAULT", MIDDLE_ENEMY_HEALTH_DEFAULT);
		config->setFloatForKey("BIG_ENEMY_HEALTH_DEFAULT", BIG_ENEMY_HEALTH_DEFAULT);
		config->setFloatForKey("HERO_DAMAGE_DEFAULT", HERO_DAMAGE_DEFAULT);
		// 定时器
		config->setFloatForKey("CREATE_BULLET_INTERVAL_DEFAULT", CREATE_BULLET_INTERVAL_DEFAULT);
		config->setFloatForKey("CREATE_SMALLENEMY_INTERVAL_DEFAULT", CREATE_SMALLENEMY_INTERVAL_DEFAULT);
		config->setFloatForKey("CREATE_MIDDLEENEMY_INTERVAL_DEFAULT", CREATE_MIDDLEENEMY_INTERVAL_DEFAULT);
		config->setFloatForKey("CREATE_BIGENEMY_INTERVAL_DEFAULT", CREATE_BIGENEMY_INTERVAL_DEFAULT);
		config->setFloatForKey("CREATE_SORMENEMYBYBIGENEMY_INTERVAL_DEFAULT", CREATE_SORMENEMYBYBIGENEMY_INTERVAL_DEFAULT);
		config->setFloatForKey("CREATE_UFO_1_INTERVAL_DEFAULT", CREATE_UFO_1_INTERVAL_DEFAULT);
		config->setFloatForKey("CREATE_SMALLENEMY_DELAY_DEFAULT", CREATE_SMALLENEMY_DELAY_DEFAULT);
		config->setFloatForKey("CREATE_MIDDLEENEMY_DELAY_DEFAULT", CREATE_MIDDLEENEMY_DELAY_DEFAULT);
		config->setFloatForKey("CREATE_BIGENEMY_DELAY_DEFAULT", CREATE_BIGENEMY_DELAY_DEFAULT);
		config->setFloatForKey("CREATE_SORMENEMYBYBIGENEMY_DELAY", CREATE_SORMENEMYBYBIGENEMY_DELAY);

		// 分数
		config->setIntegerForKey("SMALL_ENEMY_SCORE_DEFAULT", SMALL_ENEMY_SCORE_DEFAULT);
		config->setIntegerForKey("MIDDLE_ENEMY_SCORE_DEFAULT", MIDDLE_ENEMY_SCORE_DEFAULT);
		config->setIntegerForKey("BIG_ENEMY_SCORE_DEFAULT", BIG_ENEMY_SCORE_DEFAULT);
		config->setIntegerForKey("HERO_COLOR_DEFAULT", HERO_COLOR_DEFAULT);
		config->flush();
	}
	this->m_floatMap["BACKGROUND_SPEED_DEFAULT"] = config->getFloatForKey("BACKGROUND_SPEED_DEFAULT");
	this->m_floatMap["BULLET_SPEED_DEFAULT"] = config->getFloatForKey("BULLET_SPEED_DEFAULT");
	this->m_floatMap["SMALL_ENEMY_SPEED_DEFAULT"] = config->getFloatForKey("SMALL_ENEMY_SPEED_DEFAULT");
	this->m_floatMap["MIDDLE_ENEMY_SPEED_DEFAULT"] = config->getFloatForKey("MIDDLE_ENEMY_SPEED_DEFAULT");
	this->m_floatMap["BIG_ENEMY_SPEED_DEFAULT"] = config->getFloatForKey("BIG_ENEMY_SPEED_DEFAULT");
	this->m_floatMap["SMALL_ENEMY_HEALTH_DEFAULT"] = config->getFloatForKey("SMALL_ENEMY_HEALTH_DEFAULT");
	this->m_floatMap["MIDDLE_ENEMY_HEALTH_DEFAULT"] = config->getFloatForKey("MIDDLE_ENEMY_HEALTH_DEFAULT");
	this->m_floatMap["BIG_ENEMY_HEALTH_DEFAULT"] = config->getFloatForKey("BIG_ENEMY_HEALTH_DEFAULT");
	this->m_floatMap["HERO_DAMAGE_DEFAULT"] = config->getFloatForKey("HERO_DAMAGE_DEFAULT");
	this->m_floatMap["CREATE_BULLET_INTERVAL_DEFAULT"] = config->getFloatForKey("CREATE_BULLET_INTERVAL_DEFAULT");
	this->m_floatMap["CREATE_SMALLENEMY_INTERVAL_DEFAULT"] = config->getFloatForKey("CREATE_SMALLENEMY_INTERVAL_DEFAULT");
	this->m_floatMap["CREATE_MIDDLEENEMY_INTERVAL_DEFAULT"] = config->getFloatForKey("CREATE_MIDDLEENEMY_INTERVAL_DEFAULT");
	this->m_floatMap["CREATE_BIGENEMY_INTERVAL_DEFAULT"] = config->getFloatForKey("CREATE_BIGENEMY_INTERVAL_DEFAULT");
	this->m_floatMap["CREATE_UFO_1_INTERVAL_DEFAULT"] = config->getFloatForKey("CREATE_UFO_1_INTERVAL_DEFAULT");
	this->m_floatMap["CREATE_SORMENEMYBYBIGENEMY_INTERVAL_DEFAULT"] = config->getFloatForKey("CREATE_SORMENEMYBYBIGENEMY_INTERVAL_DEFAULT");
	this->m_floatMap["CREATE_SMALLENEMY_DELAY_DEFAULT"] = config->getFloatForKey("CREATE_SMALLENEMY_DELAY_DEFAULT");
	this->m_floatMap["CREATE_MIDDLEENEMY_DELAY_DEFAULT"] = config->getFloatForKey("CREATE_MIDDLEENEMY_DELAY_DEFAULT");
	this->m_floatMap["CREATE_BIGENEMY_DELAY_DEFAULT"] = config->getFloatForKey("CREATE_BIGENEMY_DELAY_DEFAULT");
	this->m_floatMap["CREATE_SORMENEMYBYBIGENEMY_DELAY"] = config->getFloatForKey("CREATE_SORMENEMYBYBIGENEMY_DELAY");

	this->m_intMap["SMALL_ENEMY_SCORE_DEFAULT"] = config->getIntegerForKey("SMALL_ENEMY_SCORE_DEFAULT");
	this->m_intMap["MIDDLE_ENEMY_SCORE_DEFAULT"] = config->getIntegerForKey("MIDDLE_ENEMY_SCORE_DEFAULT");
	this->m_intMap["BIG_ENEMY_SCORE_DEFAULT"] = config->getIntegerForKey("BIG_ENEMY_SCORE_DEFAULT");
	this->m_intMap["HERO_COLOR_DEFAULT"] = config->getIntegerForKey("HERO_COLOR_DEFAULT");
}

float ConfigUtil::getFloat(const std::string& str) {
	if (this->m_floatMap.count(str) != 0)
		return this->m_floatMap[str];
	else return -1.0f;
}
int ConfigUtil::getInteger(const std::string& str) {
	if (ConfigUtil::instance->m_intMap.count(str) != 0)
		return ConfigUtil::instance->m_intMap[str];
	else return -1;
}
void ConfigUtil::setFloat(const std::string& str, float f) {
	this->m_floatMap[str] = f;
}
void ConfigUtil::setInteger(const std::string& str, int i) {
	this->m_intMap[str] = i;
}



