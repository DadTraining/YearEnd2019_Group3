#include "BlackHandBoss.h"
#include "Update.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Sound.h"
USING_NS_CC;

BlackHandBoss::BlackHandBoss(Scene* scene) {
	//init sprite and Animate
	targetScene = scene;
	this->init();


}

BlackHandBoss::~BlackHandBoss()
{
}

void BlackHandBoss::init()
{
	//Create sprite
	this->sprite = Sprite::create("Resources/sprites/Blackhand/Idle/idle-1.png");
	this->sprite->setScale(m_SCALE_32x32 / 2);
	this->price = 500;
	this->damage = Update::GetInstance()->getDamageOfMB1();
	this->hP = Update::GetInstance()->getHPOfMB1();
	
	//Create animate attackA
	auto spriteCacheAttack_BHB = SpriteFrameCache::getInstance();
	spriteCacheAttack_BHB->addSpriteFramesWithFile("Resources/sprites/Blackhand/Attack/attack.plist", "Resources/sprites/Blackhand/Attack/attack.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 0; i < 12; i++)
	{
		sprintf(nameAnimateAttack, "attack-%d.png", i);
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
	spriteCacheIdle_BHB->addSpriteFramesWithFile("Resources/sprites/Blackhand/Idle/idle.plist", "Resources/sprites/Blackhand/Idle/idle.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 0; i < 5; i++)
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
	spriteCacheDead_BHB->addSpriteFramesWithFile("Resources/sprites/Blackhand/Dead/dead.plist", "Resources/sprites/Blackhand/Dead/dead.png");
	char nameAnimateDead[50] = { 0 };
	Vector<SpriteFrame*> animDead;
	for (int i = 0; i < 14; i++)
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
	spriteCacheRun_BHB->addSpriteFramesWithFile("Resources/sprites/Blackhand/Run/run.plist", "Resources/sprites/Blackhand/Run/run.png");
	char nameAnimateRun[50] = { 0 };
	Vector<SpriteFrame*> animRun;
	for (int i = 0; i < 5; i++)
	{
		sprintf(nameAnimateRun, "run-%d.png", i);
		auto frame = spriteCacheRun_BHB->getSpriteFrameByName(nameAnimateRun);
		animRun.pushBack(frame);
	}
	Animation* animationRun = Animation::createWithSpriteFrames(animRun, 0.1f);
	auto animateWalk = Animate::create(animationRun);
	animateWalk->retain();
	this->runAnimate = animateWalk;

	//Create animate Hit
	auto spriteCacheHit_BHB = SpriteFrameCache::getInstance();
	spriteCacheHit_BHB->addSpriteFramesWithFile("Resources/sprites/Blackhand/Hit/hit.plist", "Resources/sprites/Blackhand/Hit/hit.png");
	char nameAnimateHit[50] = { 0 };
	Vector<SpriteFrame*> animHit;
	for (int i = 0; i < 3; i++)
	{
		sprintf(nameAnimateHit, "hit-%d.png", i);
		auto frame = spriteCacheHit_BHB->getSpriteFrameByName(nameAnimateHit);
		animHit.pushBack(frame);
	}
	Animation* animationHit = Animation::createWithSpriteFrames(animHit, 0.1f);
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

void BlackHandBoss::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void BlackHandBoss::setAttackAnimate(Animate * attackAnimate)
{
	this->attackAnimate = attackAnimate;
}

void BlackHandBoss::setIdleAnimate(Animate * idleAnimate)
{
	this->idleAnimate = idleAnimate;
}

void BlackHandBoss::setHitAnimate(Animate * hitAnimate)
{
	this->hitAnimate = hitAnimate;
}

void BlackHandBoss::setRunAnimate(Animate * runAnimate)
{
	this->runAnimate = runAnimate;
}

void BlackHandBoss::setDeadAnimate(Animate * deadAnimate)
{
	this->deadAnimate = deadAnimate;
}

void BlackHandBoss::setHP(float hP)
{
	this->hP = hP;
}

void BlackHandBoss::setDamage(float  damage)
{
	this->damage = damage;
}

void BlackHandBoss::setPosSpawn(Point point)
{
	this->posSpawn = point;
}

void BlackHandBoss::setAIforEnemy()
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

	if (range < VISION_OF_EM2) {
		this->getSprite()->getPhysicsBody()->setVelocity(vectorMoveToPlayer*SPEED_MB01);
		if (player->getHP() > 0) {
			
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
			if ((player->getSprite()->getPosition().y < (this->getSprite()->getPosition().y + 150)) &&
				player->getSprite()->getPosition().y >(this->getSprite()->getPosition().y - 150) &&
				std::sqrt(pow(player->getSprite()->getPosition().x - this->getSprite()->getPosition().x, 2)) < 250) {
				if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0) {
					this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
					this->getSprite()->runAction(rpAttackAnimate);
				}
			}
		}
	}
	else {
		this->getSprite()->getPhysicsBody()->setVelocity(vectorMoveToSpawnPoint*SPEED_MB01);
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
void BlackHandBoss::Stun()
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

Sprite * BlackHandBoss::getSprite()
{
	return this->sprite;
}

Animate * BlackHandBoss::getAttackAnimate()
{
	return this->attackAnimate;
}

Animate * BlackHandBoss::getIdleAnimate()
{
	return this->idleAnimate;
}

Animate * BlackHandBoss::getHitAnimate()
{
	return this->hitAnimate;
}

Animate * BlackHandBoss::getRunAnimate()
{
	return this->runAnimate;
}

Animate * BlackHandBoss::getDeadAnimate()
{
	return this->deadAnimate;
}

float  BlackHandBoss::getHP()
{
	return this->hP;
}

float  BlackHandBoss::getDamage()
{
	return this->damage;
}

Point BlackHandBoss::getPosSpawn()
{
	return this->posSpawn;
}

void BlackHandBoss::normalAttack()
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

void BlackHandBoss::gotHit(int damage)
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

void BlackHandBoss::update(float deltaTime)
{
	if (!this->getAlive())
	{
		return;
	}
	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) == 0)
	{
		this->m_slash->getSprite()->setPosition(Vec2(-100, -100));
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

void BlackHandBoss::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_BHB);
	this->getSprite()->setPhysicsBody(physicsBody);
}

void BlackHandBoss::setIndex(int index)
{
	this->getSprite()->getPhysicsBody()->setGroup(index);
}

void BlackHandBoss::Die()
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

void BlackHandBoss::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool BlackHandBoss::getAlive()
{
	return this->isAlive;
}

void BlackHandBoss::createSlash()
{
	m_slash = new Slash(250, 250);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_BHB_ATTACK);
	targetScene->addChild(m_slash->getSprite());
	m_slash->setDamge(this->damage);
}

Slash * BlackHandBoss::getSlash()
{
	return this->m_slash;
}
