#include"UFO.h"

bool Ufo::initWithSpriteFrameType(const UfoType& type) {
	this->m_type = type;
	std::string frameName = "ufo1.png";
	switch (type)
	{
	case UfoType::BOMB_UFO:		
			frameName = "ufo2.png";
			break;
	case UfoType::FLASH_UFO:	
		frameName = "flash.png";
		break;
	case UfoType::MONSTER_UFO:
		frameName = "kulo.png";
		break;
	case UfoType::MULTIPLY_UFO:		
		frameName = "ufo1.png";
		break;
	default:
		break;
	}
	if (!Sprite::initWithSpriteFrameName(frameName))
	{
		return false;
	}


	return true;
}

Ufo* Ufo::create(const UfoType& type) {
	auto ufo = new Ufo();
	if (ufo && ufo->initWithSpriteFrameType(type))
	{
		ufo->autorelease(); //放入自动计数池  
		return ufo;
	}

	delete ufo;
	ufo = nullptr;
	return nullptr;
}

UfoType Ufo::getType() {
	return this->m_type;
}