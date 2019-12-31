#include "Villager.h"
#include "Model.h"
#include "SimpleAudioEngine.h"
#define ONE_TIME_IDLE_VILLAGER 0.05f
Villager::Villager(Scene * scene)
{
	targetScene = scene;
	this->init();
}

Villager::~Villager()
{
}

void Villager::init()
{
	this->createIdleAnimation();
	this->addPhysic();
}

void Villager::update()
{
}

void Villager::createIdleAnimation()
{
	// Create Sprite
	this->sprite = Sprite::create("Resources/sprites/Village/Idle/spr_Idle_strip_1.png");
	this->sprite->setScale(m_SCALE / 2);
	auto spriteCacheFrame = SpriteFrameCache::getInstance();
	spriteCacheFrame->addSpriteFramesWithFile("Resources/sprites/Village/Idle/sideCityzen.plist", "Resources/sprites/Village/Idle/sideCityzen.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 1; i < 17; i++)
	{
		sprintf(nameAnimateIdle, "spr_Idle_strip_%d.png", i);
		auto frame = spriteCacheFrame->getSpriteFrameByName(nameAnimateIdle);
		animIdle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, ONE_TIME_IDLE_VILLAGER);
	auto animateIdle = Animate::create(animationIdle);
	animateIdle->retain();
	this->idleAnimate = animateIdle;
	this->idleAnimate->retain();
}

void Villager::addPhysic()
{
	auto physicBody = PhysicsBody::createBox(this->getSprite()->getContentSize());
	this->sprite->setPhysicsBody(physicBody);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(Model::BITMASK_VILLAGER);
	physicBody->setContactTestBitmask(true);
}

Sprite * Villager::getSprite()
{
	return this->sprite;
}

Animate * Villager::getIdleAnimate()
{
	return this->idleAnimate;
}

void Villager::Die()
{
}
