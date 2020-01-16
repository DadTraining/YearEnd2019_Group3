#include "Player.h"
#include "Model.h"
#include "Update.h"
#include "Sound.h"
#include "ResultScene.h"
#define PLAYER_DAMAGE 100.0f	
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
	this->timeStun = Update::GetInstance()->getStunTime();
	this->ratioUlti = Update::GetInstance()->getConditionUlti();
	this->villagersNum = 0;
	this->isAlive = true;
	//Create sprite
	this->playerSprite = Sprite::create("Resources/sprites/Player/idle-with-weapon-1.png");	
	this->playerSprite->retain();
	this->playerSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	//Create animate attack
	auto spriteCacheAttack = SpriteFrameCache::getInstance();
	spriteCacheAttack->addSpriteFramesWithFile("Resources/sprites/Player/Attacks/attackA.plist", "Resources/sprites/Player/Attacks/attackA.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 1; i < 8; i++)
	{
		sprintf(nameAnimateAttack, "attack-A%d.png", i);
		CCLOG("------- Init 10  %s", nameAnimateAttack);
		auto frame = spriteCacheAttack->getSpriteFrameByName(nameAnimateAttack);
		CCLOG("------- Init 11  ____");
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.07f);
	auto animateAttack = Animate::create(animationAtack);
	CCLOG("------- Init 1");
	animateAttack->retain();
	CCLOG("------- Init 2");
	//	auto animateAttack = ResourceManager::GetInstance()->GetPlayerAction("atkA");
	this->attackAnimate = animateAttack;
	//attackAnimate->retain();
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
	Animation* animationDead = Animation::createWithSpriteFrames(animDead, 0.2f);
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
	spriteCacheHit_Player->addSpriteFramesWithFile("Resources/sprites/Player/Hit/hit-with-weapon-front.plist", "Resources/sprites/Player/Hit/hit-with-weapon-front.png");
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

	//Add skill A
	auto spriteCacheSkillA = SpriteFrameCache::getInstance();
	spriteCacheSkillA->addSpriteFramesWithFile("Resources/sprites/Player/Attacks/attackD.plist", "Resources/sprites/Player/Attacks/attackD.png");
	char nameAnimateSkillA[50] = { 0 };
	Vector<SpriteFrame*> animSkillA;
	for (int i = 1; i < 10; i++)
	{
		sprintf(nameAnimateSkillA, "attack-D%d.png", i);
		auto frame = spriteCacheSkillA->getSpriteFrameByName(nameAnimateSkillA);
		animSkillA.pushBack(frame);
	}
	Animation* animationSkillA = Animation::createWithSpriteFrames(animSkillA, 0.1f);
	auto animateSkillA = Animate::create(animationSkillA);
	animateSkillA->retain();
	this->skillAAnimate = animateSkillA;

	//Add skill B

	auto spriteCacheSkillB = SpriteFrameCache::getInstance();
	spriteCacheSkillB->addSpriteFramesWithFile("Resources/sprites/Player/Attacks/attackB.plist", "Resources/sprites/Player/Attacks/attackB.png");
	char nameAnimateSkillB[50] = { 0 };
	Vector<SpriteFrame*> animSkillB;
	for (int i = 1; i < 7; i++)
	{
		sprintf(nameAnimateSkillB, "attack-B%d.png", i);
		auto frame = spriteCacheSkillB->getSpriteFrameByName(nameAnimateSkillB);
		animSkillB.pushBack(frame);
	}
	Animation* animationSkillB = Animation::createWithSpriteFrames(animSkillB, 0.1f);
	auto animateSkillB = Animate::create(animationSkillB);
	animateSkillB->retain();
	this->skillBAnimate = animateSkillB;
	// Adding the physic to player
	addPhysic();
	createSlash();
}


void Player::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() - Size(100, 40), cocos2d::PhysicsMaterial(1.0f, 0.0f, 1.0f));
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

Vec2 Player::getPositionOfSlash()
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
	return position;
}

void Player::createSlash()
{
	// create m_slashNormal
	m_slashNormal = new Slash(50, 100);
	m_slashNormal->setDamge(damage);
	m_slashNormal->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_NORMAL_ATTACK);
	targetScene->addChild(m_slashNormal->getSprite());
	// create m_slashSpear
	m_slashSpear = new Slash(110, 50);
	m_slashSpear->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_NORMAL_ATTACK);
	targetScene->addChild(m_slashSpear->getSprite());
	m_slashSpear->setDamge(0);
	// create m_slashUltimate
	m_slashUltimate = new Slash(100, 150);
	m_slashUltimate->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_NORMAL_ATTACK);
	targetScene->addChild(m_slashUltimate->getSprite());
	m_slashUltimate->setDamge(damage * this->ratioUlti);
}

void Player::normalAttack()
{
	auto position = getPositionOfSlash();
	m_slashNormal->getSprite()->setPosition(position);
	m_numberOfKeyPress = NORMAL_ATTACK_KEY;
}

void Player::spearAttack()
{
	auto position = getPositionOfSlash();
	m_slashSpear->getSprite()->setPosition(position);
	m_numberOfKeyPress = SPEAR_ATTACK_KEY;
	m_slashSpear->getSprite()->getPhysicsBody()->setTag(Model::KNOCKBACK);
}

void Player::UltimateAttack()
{
	auto position = getPositionOfSlash();
	m_slashUltimate->getSprite()->setPosition(position);
	m_numberOfKeyPress = ULTIMATE_ATTACK_KEY;
}


void Player::increaseVillager(int num)
{
	villagersNum += num;
}

void Player::gotHit(int damage)
{
	if (!this->isAlive)
	{
		return;
	}
	playerSprite->stopActionByTag(TAG_ANIMATE_RUN);
	playerSprite->stopActionByTag(TAG_ANIMATE_IDLE1);
	playerSprite->stopActionByTag(TAG_ANIMATE_HIT);
	playerSprite->stopActionByTag(TAG_ANIMATE_ATTACK);

	// Play sound hit
	Sound::GetInstance()->soundPlayerHit();
	auto animation = this->getHitAnimate();
	animation->setTag(TAG_ANIMATE_HIT);
	playerSprite->runAction(animation);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Player/player_got_hit.plist");
	emitter->setPosition(playerSprite->getPosition());
	emitter->setScale(m_SCALE_32x32 / 8);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
	auto dtHP = this->getHP() - damage;
	this->setHP(dtHP);
	if (this->getHP() <= 0)
	{
		this->Die();
	}
}

Slash * Player::getSlash()
{
	switch (this->m_numberOfKeyPress)
	{
	case NORMAL_ATTACK_KEY:
		return this->m_slashNormal;
	case SPEAR_ATTACK_KEY:
		return this->m_slashSpear;	
	case ULTIMATE_ATTACK_KEY:
		return this->m_slashUltimate;
	}
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

Animate * Player::getSkillAAnimate()
{
	return this->skillAAnimate;
}

Animate * Player::getSkillBAnimate()
{
	return this->skillBAnimate;
}

float  Player::getHP()
{
	return this->hP;
}

float  Player::getDamage()
{
	return this->damage;
}

float Player::getTimeStun()
{
	return this->timeStun;
}

float Player::getRatioUlti()
{
	return this->ratioUlti;
}

void Player::Die()
{
	if (!this->isAlive)
	{
		return;
	}
	this->getSprite()->stopAllActions();
	auto mySprite = this->getSprite();
	mySprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
	auto callbackHide = CallFunc::create([mySprite]()
	{
		auto scene = ResultScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(0.0f, scene));
	});
	auto dieAnimation = this->getDeadAnimate();
	auto sequence = Sequence::create(dieAnimation, callbackHide, nullptr);
	this->isAlive = false;
	Sound::GetInstance()->soundPlayerDie();
	mySprite->runAction(sequence);
}

void Player::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool Player::getAlive()
{
	return this->isAlive;
}
void Player::update(float deltaTime)
{
	//if (!this->isAlive)
	//{
	//	return;
	//}
	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) == 0)
	{
		this->m_slashNormal->getSprite()->setPosition(Vec2(-100, -100));
		this->m_slashSpear->getSprite()->setPosition(Vec2(-100, -100));
		this->m_slashUltimate->getSprite()->setPosition(Vec2(-100, -100));
	}
}

int Player::getVillagersNum()
{
	return this->villagersNum;
}
