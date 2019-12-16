#include "Objects.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Objects::Objects()
{
}

Objects::~Objects()
{
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
	//this->animateAttack->retain();
}
Animate * Objects::getAnimateAttack()
{
	return animateAttack;
}
void Objects::setAnimateIdle(Animate * animateIdle)
{
	this->animateIdle = animateIdle;
	//this->animateIdle->retain();
}
Animate * Objects::getAnimateIdle()
{
	return animateIdle;
}
void Objects::setAnimateMove(Animate * animateMove)
{
	this->animateMove = animateMove;
	//this->animateMove->retain();
}
Animate * Objects::getAnimateMove()
{
	return animateMove;
}
void Objects::setAnimateDead(Animate * animateDead)
{
	this->animateDead = animateDead;
	//this->animateDead->retain();
}
Animate * Objects::getAnimateDead()
{
	return animateDead;
}
void Objects::setAnimateRun(Animate * animateRun)
{
	this->animateRun = animateRun;
	//this->animateRun->retain();
}
Animate * Objects::getAnimateRun()
{
	return animateRun;
}
