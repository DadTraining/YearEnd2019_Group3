#include "Objects.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Objects::Objects()
{
}

Objects::~Objects()
{
}

void Objects::setHP(int hp)
{
	this->hP = hp;
}

int Objects::getHP()
{
	return hP;
}

void Objects::setDammage(int damage)
{
	this->damage = damage;
}

int Objects::getDamage()
{
	return damage;
}

void Objects::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

Sprite * Objects::getSprite()
{
	return sprite;
}
void Objects::setAnimateAttack(Animate * animateAttack)
{
	this->animateAttack = animateAttack;
}
Animate * Objects::getAnimateAttack()
{
	return animateAttack->clone();
}
void Objects::setAnimateIdle(Animate * animateIdle)
{
	this->animateIdle = animateIdle;
}
Animate * Objects::getAnimateIdle()
{
	return animateIdle->clone();
}
void Objects::setAnimateMove(Animate * animateMove)
{
	this->animateMove = animateMove;
}
Animate * Objects::getAnimateMove()
{
	return animateMove->clone();
}
void Objects::setAnimateDead(Animate * animateDead)
{
	this->animateDead = animateDead;
}
Animate * Objects::getAnimateDead()
{
	return animateDead->clone();
}
void Objects::setAnimateRun(Animate * animateRun)
{
	this->animateRun = animateRun;
}
Animate * Objects::getAnimateRun()
{
	return animateRun->clone();
}
