#pragma once

#include "cocos2d.h"
USING_NS_CC;
#include <map>
using namespace std;

class ConfigUtil {
private:
	ConfigUtil() {}
	ConfigUtil(const ConfigUtil&) {}
	ConfigUtil& operator=(const ConfigUtil&) {}

	void init();

	map<std::string, float> m_floatMap;
	map<std::string, int> m_intMap;

	static ConfigUtil* instance;
public:
	static ConfigUtil* getInstance();
	int getInteger(const std::string&);
	float getFloat(const std::string&);
	void setInteger(const std::string&, int);
	void setFloat(const std::string&, float);
};