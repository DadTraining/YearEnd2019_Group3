#include "MiniBoss01.h"
#include "Update.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Sound.h"
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
	this->damage = Update::GetInstance()->getDamageOfMB1();
	this->hP = Update::GetInstance()->getHPOfMB1();
	//Create sprite
	this->sprite = Sprite::create("Resources/sprites/aMiniBoss/Idle/idle-1.png");
	this->sprite->setScale(m_SCALE_32x32 / 2);
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
	this->createSlash();
	// init isAlive
	this->isAlive = true;
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

void MiniBoss01::setHP(float hP)
{
	this->hP = hP;
}

void MiniBoss01::setDamage(float  damage)
{
	this->damage = damage;
}

void MiniBoss01::setPosSpawn(Point point)
{
	this->posSpawn = point;
}

void MiniBoss01::setAIforEnemy()
{
	auto rpIdleAnimate = RepeatForever::create(this->getIdleAnimate());
	rpIdleAnimate->setTag(TAG_ANIMATE_IDLE1);
	auto rpAttackAnimate = this->getAttackAnimate();
	rpAttackAnimate->setTag(TAG_ANIMATE_ATTACK);
	auto rpRunAnimate = RepeatForever::create(this->getRunAnimate());
	rpRunAnimate->setTag(TAG_ANIMATE_RUN);

	auto player = Update::GetInstance()->getPlayer();

	auto range = std::sqrt(pow((this->getSprite()->getPosition().x - player->getSprite()->getPosition().x), 2) + pow((this->getSprite()->getPosition().y - player->getSprite()->getPosition().y), 2));
	auto vectorMoveToSpawnPoint = Vec2(this->getPosSpawn().x - this->getSprite()->getPosition().x, this->getPosSpawn().y - this->getSprite()->getPosition().y);
	auto vectorMoveToPlayer = Vec2(player->getSprite()->getPosition().x - this->getSprite()->getPosition().x, player->getSprite()->getPosition().y - this->getSprite()->getPosition().y);

	if (range < VISION_OF_MB) {
		if (player->getHP() > 0) {
			this->getSprite()->getPhysicsBody()->setVelocity(vectorMoveToPlayer*SPEED_MB01);
			if (player->getSprite()->getPosition().x < this->getSprite()->getPosition().x) {
				this->getSprite()->setFlipX(180);
			}
			if (player->getSprite()->getPosition().x > this->getSprite()->getPosition().x) {
				this->getSprite()->setFlipX(0);
			}
			if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0) {
				this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
				this->getSprite()->runAction(rpRunAnimate);
			}
			if ((player->getSprite()->getPosition().y < (this->getSprite()->getPosition().y + 50)) &&
				player->getSprite()->getPosition().y >(this->getSprite()->getPosition().y - 50) &&
				std::sqrt(pow(player->getSprite()->getPosition().x - this->getSprite()->getPosition().x, 2)) < RANGE_OF_MB) {
				if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0) {
					this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
					this->getSprite()->runAction(rpAttackAnimate);
				}
			}
			// When player die
			else {
				if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) > 0) {
					this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
					this->getSprite()->runAction(rpRunAnimate);
				}
			}
		}
	}
	else {
		auto vectorMove = Vec2(this->getPosSpawn().x - this->getSprite()->getPosition().x, this->getPosSpawn().y - this->getSprite()->getPosition().y);
		this->getSprite()->getPhysicsBody()->setVelocity(vectorMove*SPEED_MB01);
		if ((this->getSprite()->getPosition() < this->getPosSpawn() && this->getSprite()->getPosition() > this->getPosSpawn() - Vec2(5, 5)) ||
			this->getSprite()->getPosition() > this->getPosSpawn() && this->getSprite()->getPosition() < this->getPosSpawn() + Vec2(5, 5)) {
			this->getSprite()->setPosition(this->getPosSpawn());
		}
		if (this->getPosSpawn().x > this->getSprite()->getPosition().x) {
			this->getSprite()->setFlipX(0);
		}
		if (this->getPosSpawn().x < this->getSprite()->getPosition().x) {
			this->getSprite()->setFlipX(180);
		}
		if (this->getPosSpawn().x == this->getSprite()->getPosition().x) {
			if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) == 0) {
				this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
				this->getSprite()->runAction(rpIdleAnimate);
			}
		}
	}
}

void MiniBoss01::Stun()
{
	auto delay = DelayTime::create(1.5f);
	sprite->stopAllActions();
	sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
	sprite->runAction(delay);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Monster/freezer.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	//emitter->setScale(m_SCALE / 8);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
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

float  MiniBoss01::getHP()
{
	return this->hP;
}

float  MiniBoss01::getDamage()
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

void MiniBoss01::gotHit(int damage)
{
	if (!this->getAlive())
	{
		return;
	}
	Sound::GetInstance()->soundSkeletonHit();
	this->sprite->stopAllActions();
	auto animation = this->getHitAnimate();
	animation->setTag(TAG_ANIMATE_HIT);
	this->sprite->runAction(animation);
	// Adding the effect
	auto dtHP = this->getHP() - damage;
	this->setHP(dtHP);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Player/player_got_hit.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	emitter->setScale(m_SCALE_32x32 / 8);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
	if (this->getHP() <= 0)
	{
		this->setAlive(false);
		this->Die();
	}
}

void MiniBoss01::update(float deltaTime)
{
	if (!this->getAlive())
	{
		return;
	}
	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) == 0)
	{
		this->m_slash->getSprite()->setPosition(Vec2(-1, -1));
	}
	else {
		this->normalAttack();
	}

	if (this->getSprite()->getNumberOfRunningActions() == 0)
	{
		auto animationRun = RepeatForever::create(this->getRunAnimate());
		animationRun->setTag(TAG_ANIMATE_RUN);
		this->getSprite()->runAction(animationRun);
	}
}

void MiniBoss01::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() - Size(80, 30), PhysicsMaterial(1.0f, 0.0f, 1.0f));
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

void MiniBoss01::Die()
{
	Sound::GetInstance()->soundSkeletonDie();
	this->getSprite()->stopAllActions();
	auto mySprite = this->getSprite();
	auto callbackHide = CallFunc::create([mySprite]()
	{
		mySprite->removeFromParent();
	});
	this->isAlive = false;
	this->m_slash->getSprite()->setPosition(Vec2(-1, -1));
	//this->m_slash->getSprite()->removeFromParent();
	auto dieAnimation = this->getDeadAnimate();
	auto sequence = Sequence::create(dieAnimation, callbackHide, nullptr);
	mySprite->runAction(sequence);
}

void MiniBoss01::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool MiniBoss01::getAlive()
{
	return this->isAlive;
}

void MiniBoss01::createSlash()
{
	m_slash = new Slash(100, 100);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_ENEMY1_ATTACK);
	targetScene->addChild(m_slash->getSprite());
	m_slash->setDamge(this->damage);
}

Slash * MiniBoss01::getSlash()
{
	return this->m_slash;
}
