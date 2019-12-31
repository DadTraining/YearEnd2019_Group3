# include "Slash.h"
#include "Model.h"
USING_NS_CC;

Slash::Slash()
{
	this->init();
}

void Slash::init()
{
	m_Sprite = Sprite::create();
	m_Sprite->setVisible(false);
	auto physicBody = PhysicsBody::createBox(Size(50, 120));
	physicBody->setDynamic(false);
	physicBody->setContactTestBitmask(true);
	m_Sprite->setPhysicsBody(physicBody);
}

Sprite * Slash::getSprite()
{
	return m_Sprite;
}

Slash::~Slash()
{
}