#include "aMiniBoss.h"
USING_NS_CC;


aMiniBoss::aMiniBoss(cocos2d::Scene* scene)
{
	this->init();

	auto visibleSize= Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	
}


aMiniBoss::~aMiniBoss()
{
}

void aMiniBoss::init()
{
	//create sprite aMiniBoss
	Sprite* aMiniBoss = Sprite::create("./sprites/aMiniBoss/Idle/idle.png");
	Sprite* bossFrame = Sprite::createWithSpriteFrame(aMiniBoss->getSpriteFrame());
	aMiniBoss = bossFrame;
	this->setSprite(aMiniBoss);

	//create animate attack
	auto spriteCacheAttack = SpriteFrameCache::getInstance();
	spriteCacheAttack->addSpriteFramesWithFile("./sprites/aMiniBoss/Attack/attackA.plist", "./sprites/aMiniBoss/Attack/attackA.png");
	char animateAttack[50] = { 0 };
	Vector<SpriteFrame*> attack;
	for (int i = 0; i < 8; i++)
	{
		sprintf(animateAttack, "attack-A%d.png", i + 1);
		auto frame = spriteCacheAttack->getSpriteFrameByName(animateAttack);
		attack.pushBack(frame);
	}
	Animation* animationAttack = Animation::createWithSpriteFrames(attack, 0.1f);
	auto animateAtk = Animate::create(animationAttack);
	animateAtk->retain();
	this->setAnimateAttack(animateAtk);

	//create aminate dead
	auto spriteCacheDead = SpriteFrameCache::getInstance();
	spriteCacheDead->addSpriteFramesWithFile("./sprites/aMiniBoss/Dead/dead.plist", "./sprites/aMiniBoss/Dead/dead.png");
	char aniDead[50] = { 0 };
	Vector<SpriteFrame*> dead;
	for (int i = 0; i < 4; i++)
	{
		sprintf(aniDead, "dead-%d.png", i + 1);
		auto frame = spriteCacheDead->getSpriteFrameByName(aniDead);
		dead.pushBack(frame);
	}
	Animation* animationDead = Animation::createWithSpriteFrames(dead, 0.1f);
	auto animateDead = Animate::create(animationDead);
	animateDead->retain();
	this->setAnimateDead(animateDead);

	//create aminate hit
	auto spriteCacheHit = SpriteFrameCache::getInstance();
	spriteCacheHit->addSpriteFramesWithFile("./sprites/aMiniBoss/Hit/hit.plist", "./sprites/aMiniBoss/Hit/hit.png");
	char aniHit[50] = { 0 };
	Vector<SpriteFrame*> hit;
	for (int i = 0; i < 3; i++)
	{
		sprintf(aniHit, "hit-%d.png", i + 1);
		auto frame = spriteCacheHit->getSpriteFrameByName(aniHit);
		hit.pushBack(frame);
	}
	Animation* animationHit = Animation::createWithSpriteFrames(hit, 0.1f);
	auto animateHit = Animate::create(animationHit);
	animateHit->retain();
	this->setAnimateHit(animateHit);
	

	//create animate idle
	auto spriteCacheIdle = SpriteFrameCache::getInstance();
	spriteCacheIdle->addSpriteFramesWithFile("./sprites/aMiniBoss/Idle/idle.plist", "./sprites/aMiniBoss/Idle/idle.png");
	char aniIdle[50] = { 0 };
	Vector<SpriteFrame*> idle;
	for (int i = 0; i < 4; i++)
	{
		sprintf(aniIdle, "idle-%d.png", i + 1);
		auto frame = spriteCacheIdle->getSpriteFrameByName(aniIdle);
		idle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(idle, 0.1f);
	auto animateIdle = Animate::create(animationIdle);
	animateIdle->retain();
	this->setAnimateIdle(animateIdle);

	//create animate walk
	auto spriteCacheWalk = SpriteFrameCache::getInstance();
	spriteCacheWalk->addSpriteFramesWithFile("./sprites/aMiniBoss/Walk/walk.plist", "./sprites/aMiniBoss/Walk/walk.png");
	char aniWalk[50] = { 0 };
	Vector<SpriteFrame*> walk;
	for (int i = 0; i < 6; i++)
	{
		sprintf(aniWalk, "walk-%d.png", i + 1);
		auto frame = spriteCacheWalk->getSpriteFrameByName(aniWalk);
		walk.pushBack(frame);
	}
	Animation* animationWalk = Animation::createWithSpriteFrames(walk, 0.1f);
	auto animateWalk = Animate::create(animationWalk);
	animateWalk->retain();
	this->setAnimateMove(animateWalk);
}

void aMiniBoss::update(float deltaTime)
{
}

