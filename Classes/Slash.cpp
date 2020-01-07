# include "Slash.h"
#include "Model.h"
USING_NS_CC;

Slash::Slash(int width, int height)
{
	m_width = width;
	m_height = height;
	this->init();
}

void Slash::init()
{
	this->damage = 0;
	this->createPhysics();
}

Sprite * Slash::getSprite()
{
	return m_Sprite;
}

void Slash::createPhysics()
{
	m_Sprite = Sprite::create();
	m_Sprite->setVisible(false);
	auto physicBody = PhysicsBody::createBox(Size(m_width, m_height));
	physicBody->setDynamic(false);
	physicBody->setContactTestBitmask(true);
	m_Sprite->setPhysicsBody(physicBody);
}

int Slash::getDamge()
{
	return this->damage;
}

void Slash::setDamge(int damage)
{
	this->damage = damage;
}

Slash::~Slash()
{
}