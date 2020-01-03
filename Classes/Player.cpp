#include "Player.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Update.h"
USING_NS_CC;

Player::Player(Scene* scene) {
	//init sprite and Animate
	targetScene = scene;
	this->init();
	//create scece
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
}

Player::~Player()
{
}

void Player::init()
{
	this->damage = Update::GetInstance()->getDamageOfPlayer();
	this->hP = Update::GetInstance()->getHPOfPlayer();
	this->villagersNum = 0;
	//Create sprite
	this->playerSprite = Sprite::create("Resources/sprites/Player/idle-with-weapon-1.png");

	//Create animate attack
	auto spriteCacheAttack = SpriteFrameCache::getInstance();
	spriteCacheAttack->addSpriteFramesWithFile("Resources/sprites/Player/Attacks/attackA.plist", "Resources/sprites/Player/Attacks/attackA.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 1; i < 8; i++)
	{
		sprintf(nameAnimateAttack, "attack-A%d.png", i);
		auto frame = spriteCacheAttack->getSpriteFrameByName(nameAnimateAttack);
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.07f);
	auto animateAttack = Animate::create(animationAtack);
	animateAttack->retain();
	//	auto animateAttack = ResourceManager::GetInstance()->GetPlayerAction("atkA");
	this->attackAnimate = animateAttack;
	attackAnimate->retain();
	//Create animate idle
	auto spriteCacheIdle = SpriteFrameCache::getInstance();
	spriteCacheIdle->addSpriteFramesWithFile("Resources/sprites/Player/Idle/idle-with-weapon.plist", "Resources/sprites/Player/Idle/idle-with-weapon.png");
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
	this->idleAnimate = animateIdle;
	idleAnimate->retain();

	//Create animate dead
	auto spriteCacheDead = SpriteFrameCache::getInstance();
	spriteCacheDead->addSpriteFramesWithFile("Resources/sprites/Player/Dead/dead.plist", "Resources/sprites/Player/Dead/dead.png");
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
	this->deadAnimate = animateDead;
	deadAnimate->retain();
	//Create animate run
	auto spriteCacheRun = SpriteFrameCache::getInstance();
	spriteCacheRun->addSpriteFramesWithFile("Resources/sprites/Player/Run/run.plist", "Resources/sprites/Player/Run/run.png");
	char nameAnimateRun[50] = { 0 };
	Vector<SpriteFrame*> animRun;
	for (int i = 1; i < 13; i++)
	{
		sprintf(nameAnimateRun, "run-%d.png", i);
		auto frame = spriteCacheRun->getSpriteFrameByName(nameAnimateRun);
		animRun.pushBack(frame);
	}
	Animation* animationRun = Animation::createWithSpriteFrames(animRun, 0.1f);
	auto animateRun = Animate::create(animationRun);
	animateRun->retain();
	this->runAnimate = animateRun;
	runAnimate->retain();

	auto spriteCacheHit_Player = SpriteFrameCache::getInstance();
	spriteCacheHit_Player->addSpriteFramesWithFile("Resources/sprites/Player/Hit/hit-with-weapon-front.plist", "Resources/sprites/Player//Hit/hit-with-weapon-front.png");
	char nameAnimateHit[50] = { 0 };
	Vector<SpriteFrame*> animHit;
	for (int i = 1; i < 5; i++)
	{
		sprintf(nameAnimateHit, "hit-with-weapon-front-%d.png", i);
		auto frame = spriteCacheHit_Player->getSpriteFrameByName(nameAnimateHit);
		animHit.pushBack(frame);
	}
	Animation* animationHit = Animation::createWithSpriteFrames(animHit, TIME_ONE_HIT);
	auto animateHit = Animate::create(animationHit);
	animateHit->retain();
	this->hitAnimate = animateHit;
	hitAnimate->retain();

	// Adding the physic to player
	addPhysic();
	// init slash
	m_slash = new Slash(150, 150);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_NORMAL_ATTACK);
	targetScene->addChild(m_slash->getSprite());
}

void Player::update(float deltaTime)
{
	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) == 0)
	{
		this->m_slash->getSprite()->setPosition(Vec2(-1, -1));
	}
	CheckUpdate();
	/*if (this->getHP() <= 0) {
		this->Die();
	}*/
}

void Player::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() - Size(100, 40));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_PLAYER);
	this->getSprite()->setPhysicsBody(physicsBody);
}

void Player::setSprite(Sprite * sprite)
{
	this->playerSprite = sprite;
}

void Player::setAttackAnimate(Animate * attackAnimate)
{
	this->attackAnimate = attackAnimate;
}

void Player::setIdleAnimate(Animate * idleAnimate)
{
	this->idleAnimate = idleAnimate;
}

void Player::setHitAnimate(Animate * hitAnimate)
{
	this->hitAnimate = hitAnimate;
}

void Player::setRunAnimate(Animate * runAnimate)
{
	this->runAnimate = runAnimate;
}

void Player::setDeadAnimate(Animate * deadAnimate)
{
	this->deadAnimate = deadAnimate;
}

void Player::setHP(float hP)
{
	this->hP = hP;
}

void Player::setDamage(float damage)
{
	this->damage = damage;
}
void Player::normalAttack()
{
	auto isLeft = this->getSprite()->isFlippedX();
	auto distance = this->getSprite()->getContentSize().width / 2 - 10;
	Vec2 position;
	if (isLeft)
	{
		position = Vec2(this->getSprite()->getPosition() - Vec2(distance, 0));		
	}
	else {
		position = Vec2(this->getSprite()->getPosition() + Vec2(distance, 0));
	}
	m_slash->getSprite()->setPosition(position);
}

void Player::increaseVillager(int num)
{
	villagersNum += num;
}
void Player::CheckUpdate()
{
	if (villagersNum == 10) {
		this->setDamage(this->getDamage() + 1);
		this->setHP(this->getHP() + 5);
		villagersNum = 0;

	}
}
void Player::gotHit()
{
	playerSprite->stopActionByTag(TAG_ANIMATE_RUN);
	playerSprite->stopActionByTag(TAG_ANIMATE_IDLE1);
	playerSprite->stopActionByTag(TAG_ANIMATE_HIT);
	playerSprite->stopActionByTag(TAG_ANIMATE_ATTACK);

	auto animation = this->getHitAnimate();
	animation->setTag(TAG_ANIMATE_HIT);
	playerSprite->runAction(animation);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Player/player_got_hit.plist");
	emitter->setPosition(playerSprite->getPosition());
	emitter->setScale(m_SCALE / 8);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
	auto dtHP = this->getHP() - Update::GetInstance()->getDamageOfMB1();
	this->setHP(dtHP);
}

Sprite * Player::getSprite()
{
	return this->playerSprite;
}

Animate * Player::getAttackAnimate()
{
	return this->attackAnimate;
}

Animate * Player::getIdleAnimate()
{
	return this->idleAnimate;
}

Animate * Player::getHitAnimate()
{
	return this->hitAnimate;
}

Animate * Player::getRunAnimate()
{
	return this->runAnimate;
}

Animate * Player::getDeadAnimate()
{
	return this->deadAnimate;
}

float  Player::getHP()
{
	return this->hP;
}

float  Player::getDamage()
{
	return this->damage;
}

void Player::Die()
{
	//this->getSprite()->setPhysicsBody(nullptr);
}
