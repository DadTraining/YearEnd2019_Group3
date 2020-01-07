#include "Portal.h"
#include "Model.h"
#include "MainMenu.h"
#include "CastleScene.h"
#include "ResultScene.h"
Animate * Portal::getIdleAnimate()
{
	return this->animationIdle;
}

Portal::Portal()
{
	this->init();
}

void Portal::init()
{
	// create Animation Portal
	this->sprite = Sprite::create("Resources/sprites/Portal/zaap_1.png");
	this->sprite->setScale(4);
	//Create animate attackA
	auto FrameCache = SpriteFrameCache::getInstance();
	FrameCache->addSpriteFramesWithFile("Resources/sprites/Portal/sideCityzen.plist", "Resources/sprites/Portal/sideCityzen.png");
	char IdleAnimate[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 1; i < 11; i++)
	{
		sprintf(IdleAnimate, "zaap_%d.png", i);
		auto frame = FrameCache->getSpriteFrameByName(IdleAnimate);
		animIdle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, TIME_ONE_SPIN);
	auto idleAnimate = Animate::create(animationIdle);
	idleAnimate->retain();
	this->animationIdle = idleAnimate;
	this->addPhysics();
}

Sprite * Portal::getSprite()
{
	return this->sprite;
}

void Portal::InitSprite()
{
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	auto animation = RepeatForever::create(this->getIdleAnimate());
	sprite->runAction(animation);
}

void Portal::addPhysics()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() / 3);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	sprite->setPhysicsBody(physicsBody);
}

void Portal::onContact(cocos2d::PhysicsContact & contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();
	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_PORTAL_FINALBOSS)
		|| (a->getCollisionBitmask() == Model::BITMASK_PORTAL_FINALBOSS && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		auto myScene = CastleScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, myScene));
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_PORTAL_BASE)
		|| (a->getCollisionBitmask() == Model::BITMASK_PORTAL_BASE && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		auto myScene = ResultScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, myScene));
	}
}
	



Portal::~Portal()
{
}
