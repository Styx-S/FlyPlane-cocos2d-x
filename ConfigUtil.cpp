#include "ConfigUtil.h"
#include "DefaultConstant.h"

ConfigUtil* ConfigUtil::instance = NULL;

ConfigUtil* ConfigUtil::getInstance() {
	if (ConfigUtil::instance == nullptr) {
		ConfigUtil::instance = new ConfigUtil();
		ConfigUtil::instance->init();
	}
	return ConfigUtil::instance;
}
void ConfigUtil::init() {
	auto config = UserDefault::getInstance();
	// 配置文件不存在
	if (config->getIntegerForKey("DEFAULT_CONSTANT", 0)) {
		// 血量和速度
		config->setFloatForKey("BACKGROUND_SPEED_DEFFAULT", BACKGROUND_SPEED_DEFFAULT);
		config->setFloatForKey("BULLET_SPEED_DEFFAULT", BULLET_SPEED_DEFFAULT);
		config->setFloatForKey("SMALL_ENEMY_SPEED_DEFFAULT", SMALL_ENEMY_SPEED_DEFFAULT);
		config->setFloatForKey("MIDDLE_ENEMY_SPEED_DEFFAULT", MIDDLE_ENEMY_SPEED_DEFFAULT);
		config->setFloatForKey("BIG_ENEMY_SPEED_DEFFAULT", BIG_ENEMY_SPEED_DEFFAULT);
		config->setFloatForKey("SMALL_ENEMY_HEALTH_DEFFAULT", SMALL_ENEMY_HEALTH_DEFFAULT);
		config->setFloatForKey("MIDDLE_ENEMY_HEALTH_DEFFAULT", MIDDLE_ENEMY_HEALTH_DEFFAULT);
		config->setFloatForKey("BIG_ENEMY_HEALTH_DEFFAULT", BIG_ENEMY_HEALTH_DEFFAULT);
		config->setFloatForKey("HERO_DAMAGE_DEFFAULT", HERO_DAMAGE_DEFFAULT);
		// 定时器
		config->setFloatForKey("CREATE_BULLET_INTERVAL_DEFFAULT", CREATE_BULLET_INTERVAL_DEFFAULT);
		config->setFloatForKey("CREATE_SMALLENEMY_INTERVAL_DEFFAULT", CREATE_SMALLENEMY_INTERVAL_DEFFAULT);
		config->setFloatForKey("CREATE_MIDDLEENEMY_INTERVAL_DEFFAULT", CREATE_MIDDLEENEMY_INTERVAL_DEFFAULT);
		config->setFloatForKey("CREATE_BIGENEMY_INTERVAL_DEFFAULT", CREATE_BIGENEMY_INTERVAL_DEFFAULT);
		config->setFloatForKey("CREATE_UFO_1_INTERVAL_DEFFAULT", CREATE_UFO_1_INTERVAL_DEFFAULT);
		config->setFloatForKey("CREATE_SMALLENEMY_DELAY_DEFFAULT", CREATE_SMALLENEMY_DELAY_DEFFAULT);
		config->setFloatForKey("CREATE_MIDDLEENEMY_DELAY_DEFFAULT", CREATE_MIDDLEENEMY_DELAY_DEFFAULT);
		config->setFloatForKey("CREATE_BIGENEMY_DELAY_DEFFAULT", CREATE_BIGENEMY_DELAY_DEFFAULT);
		
		// 分数
		config->setIntegerForKey("SMALL_ENEMY_SCORE_DEFFAULT", SMALL_ENEMY_SCORE_DEFFAULT);
		config->setIntegerForKey("MIDDLE_ENEMY_SCORE_DEFFAULT", MIDDLE_ENEMY_SCORE_DEFFAULT);
		config->setIntegerForKey("BIG_ENEMY_SCORE_DEFFAULT", BIG_ENEMY_SCORE_DEFFAULT);
	}
	this->m_floatMap["BACKGROUND_SPEED_DEFFAULT"] = config->getFloatForKey("BACKGROUND_SPEED_DEFFAULT");
	this->m_floatMap["BULLET_SPEED_DEFFAULT"] = config->getFloatForKey("BULLET_SPEED_DEFFAULT");
	this->m_floatMap["SMALL_ENEMY_SPEED_DEFFAULT"] = config->getFloatForKey("SMALL_ENEMY_SPEED_DEFFAULT");
	this->m_floatMap["MIDDLE_ENEMY_SPEED_DEFFAULT"] = config->getFloatForKey("MIDDLE_ENEMY_SPEED_DEFFAULT");
	this->m_floatMap["BIG_ENEMY_SPEED_DEFFAULT"] = config->getFloatForKey("BIG_ENEMY_SPEED_DEFFAULT");
	this->m_floatMap["SMALL_ENEMY_HEALTH_DEFFAULT"] = config->getFloatForKey("SMALL_ENEMY_HEALTH_DEFFAULT");
	this->m_floatMap["MIDDLE_ENEMY_HEALTH_DEFFAULT"] = config->getFloatForKey("MIDDLE_ENEMY_HEALTH_DEFFAULT");
	this->m_floatMap["BIG_ENEMY_HEALTH_DEFFAULT"] = config->getFloatForKey("BIG_ENEMY_HEALTH_DEFFAULT");
	this->m_floatMap["HERO_DAMAGE_DEFFAULT"] = config->getFloatForKey("HERO_DAMAGE_DEFFAULT");
	this->m_floatMap["CREATE_BULLET_INTERVAL_DEFFAULT"] = config->getFloatForKey("CREATE_BULLET_INTERVAL_DEFFAULT");
	this->m_floatMap["CREATE_SMALLENEMY_INTERVAL_DEFFAULT"] = config->getFloatForKey("CREATE_SMALLENEMY_INTERVAL_DEFFAULT");
	this->m_floatMap["CREATE_MIDDLEENEMY_INTERVAL_DEFFAULT"] = config->getFloatForKey("CREATE_MIDDLEENEMY_INTERVAL_DEFFAULT");
	this->m_floatMap["CREATE_BIGENEMY_INTERVAL_DEFFAULT"] = config->getFloatForKey("CREATE_BIGENEMY_INTERVAL_DEFFAULT");
	this->m_floatMap["CREATE_UFO_1_INTERVAL_DEFFAULT"] = config->getFloatForKey("CREATE_UFO_1_INTERVAL_DEFFAULT");
	this->m_floatMap["CREATE_SMALLENEMY_DELAY_DEFFAULT"] = config->getFloatForKey("CREATE_SMALLENEMY_DELAY_DEFFAULT");
	this->m_floatMap["CREATE_MIDDLEENEMY_DELAY_DEFFAULT"] = config->getFloatForKey("CREATE_MIDDLEENEMY_DELAY_DEFFAULT");
	this->m_floatMap["CREATE_BIGENEMY_DELAY_DEFFAULT"] = config->getFloatForKey("CREATE_BIGENEMY_DELAY_DEFFAULT");

	this->m_intMap["SMALL_ENEMY_SCORE_DEFFAULT"] = config->getIntegerForKey("SMALL_ENEMY_SCORE_DEFFAULT");
	this->m_intMap["MIDDLE_ENEMY_SCORE_DEFFAULT"] = config->getIntegerForKey("MIDDLE_ENEMY_SCORE_DEFFAULT");
	this->m_intMap["BIG_ENEMY_SCORE_DEFFAULT"] = config->getIntegerForKey("BIG_ENEMY_SCORE_DEFFAULT");

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



