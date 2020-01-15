#include "KnightBoss.h"
#include "Update.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Sound.h"
USING_NS_CC;

KnightBoss::KnightBoss(Scene* scene) {
	//init sprite and Animate
	targetScene = scene;
	this->init();


}

KnightBoss::~KnightBoss()
{
}

void KnightBoss::init()
{
	////Create sprite
	//this->sprite = Sprite::create("Resources/sprites/KnightBoss/Idle/ready_1.png");
	//this->sprite->setScale(m_SCALE_32x32);
	//this->damage = Update::GetInstance()->getDamageOfMB1();
	//this->hP = Update::GetInstance()->getHPOfMB1();
	//this->price = rand() % 11 + 10;
	//this->isEvoled = false;
	////Create animate attackA
	//auto spriteCacheAttack_MB1 = SpriteFrameCache::getInstance();
	//spriteCacheAttack_MB1->addSpriteFramesWithFile("Resources/sprites/KnightBoss/Attacks/attack4.plist", "Resources/sprites/KnightBoss/Attacks/attack4.png");
	//char nameAnimateAttack[50] = { 0 };
	//Vector<SpriteFrame*> animAttack;
	//for (int i = 1; i < 7; i++)
	//{
	//	sprintf(nameAnimateAttack, "attack4_%d.png", i);
	//	auto frame = spriteCacheAttack_MB1->getSpriteFrameByName(nameAnimateAttack);
	//	animAttack.pushBack(frame);
	//}
	//Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.2f);
	//auto animateAttack = Animate::create(animationAtack);
	//animateAttack->retain();
	//this->attackAnimate = animateAttack;
	//attackAnimate->retain();
	//
	////Create animate idle
	//auto spriteCacheIdle_MB1 = SpriteFrameCache::getInstance();
	//spriteCacheIdle_MB1->addSpriteFramesWithFile("Resources/sprites/KnightBoss/Idle/ready.plist", "Resources/sprites/KnightBoss/Idle/ready.png");
	//char nameAnimateIdle[50] = { 0 };
	//Vector<SpriteFrame*> animIdle;
	//for (int i = 1; i < 4; i++)
	//{
	//	sprintf(nameAnimateIdle, "ready_%d.png", i);
	//	auto frame = spriteCacheIdle_MB1->getSpriteFrameByName(nameAnimateIdle);
	//	animIdle.pushBack(frame);
	//}
	//Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, 0.2f);
	//auto animateIdle = Animate::create(animationIdle);
	//animateIdle->retain();
	//this->idleAnimate = animateIdle;
	//idleAnimate->retain();

	////Create animate dead
	//auto spriteCacheDead_MB1 = SpriteFrameCache::getInstance();
	//spriteCacheDead_MB1->addSpriteFramesWithFile("Resources/sprites/KnightBoss/Die/fall_back.plist", "Resources/sprites/KnightBoss/Die/fall_back.png");
	//char nameAnimateDead[50] = { 0 };
	//Vector<SpriteFrame*> animDead;
	//for (int i = 1; i < 6; i++)
	//{
	//	sprintf(nameAnimateDead, "fall_back_%d.png", i);
	//	auto frame = spriteCacheDead_MB1->getSpriteFrameByName(nameAnimateDead);
	//	animDead.pushBack(frame);
	//}
	//Animation* animationDead = Animation::createWithSpriteFrames(animDead, 0.15f);
	//auto animateDead = Animate::create(animationDead);
	//animateDead->retain();
	//this->deadAnimate = animateDead;
	//deadAnimate->retain();

	////Create animate run
	//auto spriteCacheRun_MB1 = SpriteFrameCache::getInstance();
	//spriteCacheRun_MB1->addSpriteFramesWithFile("Resources/sprites/KnightBoss/Run/run.plist", "Resources/sprites/KnightBoss/Run/run.png");
	//char nameAnimateRun[50] = { 0 };
	//Vector<SpriteFrame*> animRun;
	//for (int i = 1; i < 7; i++)
	//{
	//	sprintf(nameAnimateRun, "run_%d.png", i);
	//	auto frame = spriteCacheRun_MB1->getSpriteFrameByName(nameAnimateRun);
	//	animRun.pushBack(frame);
	//}
	//Animation* animationRun = Animation::createWithSpriteFrames(animRun, 0.1f);
	//auto animateWalk = Animate::create(animationRun);
	//animateWalk->retain();
	//this->runAnimate = animateWalk;

	////Create animate Hit
	//auto spriteCacheHit_MB1 = SpriteFrameCache::getInstance();
	//spriteCacheHit_MB1->addSpriteFramesWithFile("Resources/sprites/KnightBoss/Hit/hit.plist", "Resources/sprites/KnightBoss/Hit/hit.png");
	//char nameAnimateHit[50] = { 0 };
	//Vector<SpriteFrame*> animHit;
	//for (int i = 1; i < 4; i++)
	//{
	//	sprintf(nameAnimateHit, "hit_%d.png", i);
	//	auto frame = spriteCacheHit_MB1->getSpriteFrameByName(nameAnimateHit);
	//	animHit.pushBack(frame);
	//}
	//Animation* animationHit = Animation::createWithSpriteFrames(animHit, 0.3f);
	//auto animateHit = Animate::create(animationHit);
	//animateHit->retain();
	//this->hitAnimate = animateHit;

	this->sprite = Sprite::create("Resources/sprites/dMiniBoss/Idle/idle-1.png");
	this->sprite->setScale(m_SCALE_32x32);
	this->price = 500;
	this->damage = Update::GetInstance()->getDamageOfMB1();
	this->hP = Update::GetInstance()->getHPOfMB1();

	//Create animate attackA
	auto spriteCacheAttack_BHB = SpriteFrameCache::getInstance();
	spriteCacheAttack_BHB->addSpriteFramesWithFile("Resources/sprites/dMiniBoss/Attack/attackA.plist", "Resources/sprites/dMiniBoss/Attack/attackA.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 1; i < 13; i++)
	{
		sprintf(nameAnimateAttack, "attack-A%d.png", i);
		auto frame = spriteCacheAttack_BHB->getSpriteFrameByName(nameAnimateAttack);
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.1f);
	auto animateAttack = Animate::create(animationAtack);
	animateAttack->retain();
	this->attackAnimate = animateAttack;
	attackAnimate->retain();

	//Create animate idle
	auto spriteCacheIdle_BHB = SpriteFrameCache::getInstance();
	spriteCacheIdle_BHB->addSpriteFramesWithFile("Resources/sprites/dMiniBoss/Idle/idle.plist", "Resources/sprites/dMiniBoss/Idle/idle.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 1; i < 5; i++)
	{
		sprintf(nameAnimateIdle, "idle-%d.png", i);
		auto frame = spriteCacheIdle_BHB->getSpriteFrameByName(nameAnimateIdle);
		animIdle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, 0.1f);
	auto animateIdle = Animate::create(animationIdle);
	animateIdle->retain();
	this->idleAnimate = animateIdle;
	idleAnimate->retain();

	//Create animate dead
	auto spriteCacheDead_BHB = SpriteFrameCache::getInstance();
	spriteCacheDead_BHB->addSpriteFramesWithFile("Resources/sprites/dMiniBoss/Dead/dead.plist", "Resources/sprites/dMiniBoss/Dead/dead.png");
	char nameAnimateDead[50] = { 0 };
	Vector<SpriteFrame*> animDead;
	for (int i = 1; i < 5; i++)
	{
		sprintf(nameAnimateDead, "dead-%d.png", i);
		auto frame = spriteCacheDead_BHB->getSpriteFrameByName(nameAnimateDead);
		animDead.pushBack(frame);
	}
	Animation* animationDead = Animation::createWithSpriteFrames(animDead, 0.15f);
	auto animateDead = Animate::create(animationDead);
	animateDead->retain();
	this->deadAnimate = animateDead;
	deadAnimate->retain();

	//Create animate run
	auto spriteCacheRun_BHB = SpriteFrameCache::getInstance();
	spriteCacheRun_BHB->addSpriteFramesWithFile("Resources/sprites/dMiniBoss/Walk/walk.plist", "Resources/sprites/dMiniBoss/Walk/walk.png");
	char nameAnimateRun[50] = { 0 };
	Vector<SpriteFrame*> animRun;
	for (int i = 1; i < 7; i++)
	{
		sprintf(nameAnimateRun, "walk-%d.png", i);
		auto frame = spriteCacheRun_BHB->getSpriteFrameByName(nameAnimateRun);
		animRun.pushBack(frame);
	}
	Animation* animationRun = Animation::createWithSpriteFrames(animRun, 0.1f);
	auto animateWalk = Animate::create(animationRun);
	animateWalk->retain();
	this->runAnimate = animateWalk;
	runAnimate->retain();

	//Create animate Hit
	auto spriteCacheHit_BHB = SpriteFrameCache::getInstance();
	spriteCacheHit_BHB->addSpriteFramesWithFile("Resources/sprites/dMiniBoss/Hit/hit.plist", "Resources/sprites/dMiniBoss/Hit/hit.png");
	char nameAnimateHit[50] = { 0 };
	Vector<SpriteFrame*> animHit;
	for (int i = 1; i < 4; i++)
	{
		sprintf(nameAnimateHit, "hit-%d.png", i);
		auto frame = spriteCacheHit_BHB->getSpriteFrameByName(nameAnimateHit);
		animHit.pushBack(frame);
	}
	Animation* animationHit = Animation::createWithSpriteFrames(animHit, 0.1f);
	auto animateHit = Animate::create(animationHit);
	animateHit->retain();
	this->hitAnimate = animateHit;
	hitAnimate->retain();

	// Add physics
	addPhysic();
	// init slash
	this->createSlash();
	// init isAlive
	this->isAlive = true;
}

void KnightBoss::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void KnightBoss::setAttackAnimate(Animate * attackAnimate)
{
	this->attackAnimate = attackAnimate;
}

void KnightBoss::setIdleAnimate(Animate * idleAnimate)
{
	this->idleAnimate = idleAnimate;
}

void KnightBoss::setHitAnimate(Animate * hitAnimate)
{
	this->hitAnimate = hitAnimate;
}

void KnightBoss::setRunAnimate(Animate * runAnimate)
{
	this->runAnimate = runAnimate;
}

void KnightBoss::setDeadAnimate(Animate * deadAnimate)
{
	this->deadAnimate = deadAnimate;
}

void KnightBoss::setHP(float hP)
{
	this->hP = hP;
}

void KnightBoss::setDamage(float  damage)
{
	this->damage = damage;
}

void KnightBoss::setPosSpawn(Point point)
{
	this->posSpawn = point;
}

void KnightBoss::setAIforEnemy()
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

void KnightBoss::evolve()
{
	isEvoled = true;
	this->setDamage(this->getDamage() * 2);
	this->setHP(this->getHP() * 2);
	this->getSprite()->setScale(this->getSprite()->getScale() * 2);
}

void KnightBoss::Stun()
{
	auto delay = DelayTime::create(Update::GetInstance()->getStunTime());
	if (sprite->getNumberOfRunningActionsByTag(TAG_ANIMATE_DIE) == 0)
	{
		sprite->stopAllActions();
	}
	sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
	sprite->runAction(delay);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Monster/freezer.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	//emitter->setScale(m_SCALE / 8);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
}

Sprite * KnightBoss::getSprite()
{
	return this->sprite;
}

Animate * KnightBoss::getAttackAnimate()
{
	return this->attackAnimate;
}

Animate * KnightBoss::getIdleAnimate()
{
	return this->idleAnimate;
}

Animate * KnightBoss::getHitAnimate()
{
	return this->hitAnimate;
}

Animate * KnightBoss::getRunAnimate()
{
	return this->runAnimate;
}

Animate * KnightBoss::getDeadAnimate()
{
	return this->deadAnimate;
}

float  KnightBoss::getHP()
{
	return this->hP;
}

float  KnightBoss::getDamage()
{
	return this->damage;
}

Point KnightBoss::getPosSpawn()
{
	return this->posSpawn;
}

void KnightBoss::normalAttack()
{
	auto isLeft = this->getSprite()->isFlippedX();
	auto distance = this->getSprite()->getContentSize().width / 2;
	auto slash = this->m_slash;
	auto attackPos = this->getSprite()->getPosition();
	auto delay = DelayTime::create(0.3f);
	if (isLeft)
	{
		attackPos -= Vec2(distance, 0);
	}
	else {
		attackPos += Vec2(distance, 0);
	}
	auto attack = CallFunc::create([slash, attackPos]()
	{
		slash->getSprite()->setPosition(attackPos);
	});
	auto rpSequence = Sequence::create(delay, attack, nullptr);
	rpSequence->setTag(TAG_ATTACK);
	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ATTACK) == 0)
	{
		this->getSprite()->runAction(rpSequence);
	}
}

void KnightBoss::gotHit(int damage)
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

void KnightBoss::update(float deltaTime)
{
	if (!this->getAlive())
	{
		return;
	}
	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) == 0)
	{
		this->m_slash->getSprite()->setPosition(Vec2(-1000, -1000));
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

void KnightBoss::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() - Size(80, 30), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_KNIGHTBOSS);
	this->getSprite()->setPhysicsBody(physicsBody);
}

void KnightBoss::setIndex(int index)
{
	this->getSprite()->getPhysicsBody()->setGroup(index);
}

void KnightBoss::Die()
{
	Sound::GetInstance()->soundSkeletonDie();
	this->getSprite()->stopAllActions();
	auto mySprite = this->getSprite();
	auto callbackHide = CallFunc::create([mySprite]()
	{
		mySprite->removeFromParent();
	});
	this->isAlive = false;
	this->m_slash->getSprite()->setPosition(Vec2(-1000, -1000));
	this->m_slash->getSprite()->removeFromParent();
	Update::GetInstance()->getPlayer()->increaseVillager(this->price);
	auto dieAnimation = this->getDeadAnimate();
	auto sequence = Sequence::create(dieAnimation, callbackHide, nullptr);
	sequence->setTag(TAG_ANIMATE_DIE);
	mySprite->runAction(sequence);
}

void KnightBoss::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool KnightBoss::getAlive()
{
	return this->isAlive;
}

bool KnightBoss::getIsEvolved()
{
	return this->isEvoled;
}

void KnightBoss::createSlash()
{
	m_slash = new Slash(100, 100);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_KNIGHT_ATTACK);
	targetScene->addChild(m_slash->getSprite());
	m_slash->setDamge(this->damage);
}

Slash * KnightBoss::getSlash()
{
	return this->m_slash;
}
