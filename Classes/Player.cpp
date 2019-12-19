#include "Player.h"
//#include "ResourceManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Player::Player(cocos2d::Scene* scene) {
	//init sprite and Animate
	this->init();

	//create scece
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->scene = scene;


}

Player::~Player()
{
}

void Player::init()
{
	//Create sprite
	Sprite* player = Sprite::create("sprites/Player/idle-with-weapon-1.png");
	Sprite* playerFrame = Sprite::createWithSpriteFrame(player->getSpriteFrame());
	this->setSprite(playerFrame);

	//Create animate attack
	auto spriteCacheAttack = SpriteFrameCache::getInstance();
	spriteCacheAttack->addSpriteFramesWithFile("sprites/Player/Attacks/attackA.plist", "sprites/Player/Attacks/attackA.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 1; i < 8; i++)
	{
		sprintf(nameAnimateAttack, "attack-A%d.png", i);
		auto frame = spriteCacheAttack->getSpriteFrameByName(nameAnimateAttack);
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.1f);
	auto animateAttack = Animate::create(animationAtack);
	animateAttack->retain();
//	auto animateAttack = ResourceManager::GetInstance()->GetPlayerAction("atkA");
	this->setAnimateAttack(animateAttack);
	
	//Create animate idle
	auto spriteCacheIdle = SpriteFrameCache::getInstance();
	spriteCacheIdle->addSpriteFramesWithFile("sprites/Player/Idle/idle-with-weapon.plist", "sprites/Player/Idle/idle-with-weapon.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 1; i < 7; i++)
	{
		sprintf(nameAnimateIdle, "idle-with-weapon-%d.png", i);
		auto frame = spriteCacheIdle->getSpriteFrameByName(nameAnimateIdle);
		animIdle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, 0.2f);
	auto animateIdle = Animate::create(animationIdle);
	animateIdle->retain();
	this->setAnimateIdle(animateIdle);

	//Create animate move
	auto spriteCacheMove = SpriteFrameCache::getInstance();
	spriteCacheIdle->addSpriteFramesWithFile("sprites/Player/Walk/walk-with-weapon.plist", "sprites/Player/Walk/walk-with-weapon.png");
	char nameAnimateMove[50] = { 0 };
	Vector<SpriteFrame*> animMove;
	for (int i = 1; i < 12; i++)
	{
		sprintf(nameAnimateMove, "walk-with-weapon-%d.png", i);
		auto frame = spriteCacheMove->getSpriteFrameByName(nameAnimateMove);
		animMove.pushBack(frame);
	}
	Animation* animationMove = Animation::createWithSpriteFrames(animMove, 0.1f);
	auto animateMove = Animate::create(animationMove);
	animateMove->retain();
	this->setAnimateMove(animateMove);

	//Create animate dead
	auto spriteCacheDead = SpriteFrameCache::getInstance();
	spriteCacheDead->addSpriteFramesWithFile("sprites/Player/Dead/dead.plist", "sprites/Player/Dead/dead.png");
	char nameAnimateDead[50] = { 0 };
	Vector<SpriteFrame*> animDead;
	for (int i = 1; i < 7; i++)
	{
		sprintf(nameAnimateDead, "dead-%d.png", i);
		auto frame = spriteCacheDead->getSpriteFrameByName(nameAnimateDead);
		animDead.pushBack(frame);
	}
	Animation* animationDead = Animation::createWithSpriteFrames(animDead, 0.26f);
	auto animateDead = Animate::create(animationDead);
	animateDead->retain();
	this->setAnimateDead(animateDead);

	//Create animate run
	auto spriteCacheRun = SpriteFrameCache::getInstance();
	spriteCacheRun->addSpriteFramesWithFile("sprites/Player/Run/run.plist", "sprites/Player/Run/run.png");
	char nameAnimateRun[50] = { 0 };
	Vector<SpriteFrame*> animRun;
	for (int i = 1; i < 13; i++)
	{
		sprintf(nameAnimateRun, "run-%d.png", i);
		auto frame = spriteCacheRun->getSpriteFrameByName(nameAnimateRun);
		animRun.pushBack(frame);
	}
	Animation* animationRun = Animation::createWithSpriteFrames(animRun, 0.07f);
	auto animateRun = Animate::create(animationRun);
	animateRun->retain();
	this->setAnimateRun(animateRun);
}

void Player::update(float deltaTime)
{
}
