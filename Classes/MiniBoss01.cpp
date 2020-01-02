#include "MiniBoss01.h"
//#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Model.h"

USING_NS_CC;

MiniBoss01::MiniBoss01(Scene* scene) {
	//init sprite and Animate
	targetScene = scene;
	this->init();


}

MiniBoss01::~MiniBoss01()
{
}

void MiniBoss01::init()
{
	//Create sprite
	this->sprite = Sprite::create("Resources/sprites/aMiniBoss/Idle/idle-1.png");
	this->sprite->setScale(m_SCALE / 2);
	//Create animate attackA
	auto spriteCacheAttack_MB1 = SpriteFrameCache::getInstance();
	spriteCacheAttack_MB1->addSpriteFramesWithFile("Resources/sprites/aMiniBoss/Attacks/attackA.plist", "Resources/sprites/aMiniBoss/Attacks/attackA.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 1; i < 9; i++)
	{
		sprintf(nameAnimateAttack, "attack-A%d.png", i);
		auto frame = spriteCacheAttack_MB1->getSpriteFrameByName(nameAnimateAttack);
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, TIME_ONE_ATTACK);
	auto animateAttack = Animate::create(animationAtack);
	animateAttack->retain();
	this->attackAnimate = animateAttack;
	attackAnimate->retain();

	//Create animate idle
	auto spriteCacheIdle_MB1 = SpriteFrameCache::getInstance();
	spriteCacheIdle_MB1->addSpriteFramesWithFile("Resources/sprites/aMiniBoss/Idle/idle.plist", "Resources/sprites/aMiniBoss/Idle/idle.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 1; i < 5; i++)
	{
		sprintf(nameAnimateIdle, "idle-%d.png", i);
		auto frame = spriteCacheIdle_MB1->getSpriteFrameByName(nameAnimateIdle);
		animIdle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, TIME_ONE_IDLE);
	auto animateIdle = Animate::create(animationIdle);
	animateIdle->retain();
	this->idleAnimate = animateIdle;
	idleAnimate->retain();

	//Create animate dead
	auto spriteCacheDead_MB1 = SpriteFrameCache::getInstance();
	spriteCacheDead_MB1->addSpriteFramesWithFile("Resources/sprites/aMiniBoss/Dead/dead.plist", "Resources/sprites/aMiniBoss/Dead/dead.png");
	char nameAnimateDead[50] = { 0 };
	Vector<SpriteFrame*> animDead;
	for (int i = 1; i < 5; i++)
	{
		sprintf(nameAnimateDead, "dead-%d.png", i);
		auto frame = spriteCacheDead_MB1->getSpriteFrameByName(nameAnimateDead);
		animDead.pushBack(frame);
	}
	Animation* animationDead = Animation::createWithSpriteFrames(animDead, TIME_ONE_DEAD);
	auto animateDead = Animate::create(animationDead);
	animateDead->retain();
	this->deadAnimate = animateDead;
	deadAnimate->retain();

	//Create animate run
	auto spriteCacheRun_MB1 = SpriteFrameCache::getInstance();
	spriteCacheRun_MB1->addSpriteFramesWithFile("Resources/sprites/aMiniBoss/Walk/walk.plist", "Resources/sprites/aMiniBoss/Walk/walk.png");
	char nameAnimateRun[50] = { 0 };
	Vector<SpriteFrame*> animRun;
	for (int i = 1; i < 7; i++)
	{
		sprintf(nameAnimateRun, "walk-%d.png", i);
		auto frame = spriteCacheRun_MB1->getSpriteFrameByName(nameAnimateRun);
		animRun.pushBack(frame);
	}
	Animation* animationRun = Animation::createWithSpriteFrames(animRun, TIME_ONE_RUN);
	auto animateWalk = Animate::create(animationRun);
	animateWalk->retain();
	this->runAnimate = animateWalk;

	//Create animate Hit
	auto spriteCacheHit_MB1 = SpriteFrameCache::getInstance();
	spriteCacheHit_MB1->addSpriteFramesWithFile("Resources/sprites/aMiniBoss/Hit/hit.plist", "Resources/sprites/aMiniBoss/Hit/hit.png");
	char nameAnimateHit[50] = { 0 };
	Vector<SpriteFrame*> animHit;
	for (int i = 1; i < 4; i++)
	{
		sprintf(nameAnimateHit, "hit-%d.png", i);
		auto frame = spriteCacheHit_MB1->getSpriteFrameByName(nameAnimateHit);
		animHit.pushBack(frame);
	}
	Animation* animationHit = Animation::createWithSpriteFrames(animHit, TIME_ONE_HIT);
	auto animateHit = Animate::create(animationHit);
	animateHit->retain();
	this->hitAnimate = animateHit;

	// Add physics
	addPhysic();
	// init slash
	m_slash = new Slash(100, 100);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_ENEMY1_ATTACK);
	targetScene->addChild(m_slash->getSprite());
}

void MiniBoss01::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void MiniBoss01::setAttackAnimate(Animate * attackAnimate)
{
	this->attackAnimate = attackAnimate;
}

void MiniBoss01::setIdleAnimate(Animate * idleAnimate)
{
	this->idleAnimate = idleAnimate;
}

void MiniBoss01::setHitAnimate(Animate * hitAnimate)
{
	this->hitAnimate = hitAnimate;
}

void MiniBoss01::setRunAnimate(Animate * runAnimate)
{
	this->runAnimate = runAnimate;
}

void MiniBoss01::setDeadAnimate(Animate * deadAnimate)
{
	this->deadAnimate = deadAnimate;
}

void MiniBoss01::setHP(float* hP)
{
	this->hP = hP;
}

void MiniBoss01::setDamage(float * damage)
{
	this->damage = damage;
}

void MiniBoss01::setPosSpawn(Point point)
{
	this->posSpawn = point;
}

Sprite * MiniBoss01::getSprite()
{
	return this->sprite;
}

Animate * MiniBoss01::getAttackAnimate()
{
	return this->attackAnimate;
}

Animate * MiniBoss01::getIdleAnimate()
{
	return this->idleAnimate;
}

Animate * MiniBoss01::getHitAnimate()
{
	return this->hitAnimate;
}

Animate * MiniBoss01::getRunAnimate()
{
	return this->runAnimate;
}

Animate * MiniBoss01::getDeadAnimate()
{
	return this->deadAnimate;
}

float * MiniBoss01::getHP()
{
	return this->hP;
}

float * MiniBoss01::getDamage()
{
	return this->damage;
}

Point MiniBoss01::getPosSpawn()
{
	return this->posSpawn;
}

void MiniBoss01::normalAttack()
{
	auto isLeft = this->getSprite()->isFlippedX();
	auto distance = this->getSprite()->getContentSize().width / 2;
	if (isLeft)
	{
		m_slash->getSprite()->setPosition(this->getSprite()->getPosition() - Vec2(distance, 0));
	}
	else {
		m_slash->getSprite()->setPosition(this->getSprite()->getPosition() + Vec2(distance, 0));
	}
}

void MiniBoss01::gotHit()
{
	this->sprite->stopAllActions();
	auto animation = this->getHitAnimate();
	animation->setTag(TAG_ANIMATE_HIT);
	this->sprite->runAction(animation);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Player/player_got_hit.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	emitter->setScale(m_SCALE / 8);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
	
}

void MiniBoss01::update(float deltaTime)
{
	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) == 0)
	{
		this->m_slash->getSprite()->setPosition(Vec2(-1, -1));
	}
	else {
		this->normalAttack();
	}
}

void MiniBoss01::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() - Size(80, 30));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_ENEMY);
	this->getSprite()->setPhysicsBody(physicsBody);
}

void MiniBoss01::setIndex(int index)
{
	this->getSprite()->getPhysicsBody()->setGroup(index);
}
