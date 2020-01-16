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
	this->isEvoled = false;
	this->damage = Update::GetInstance()->getPlayer()->getDamage();
	this->hP = Update::GetInstance()->getHPOfPlayer() + 1000;
	this->sprite = Sprite::create("Resources/sprites/Player/idle-with-weapon-1.png");
	this->sprite->retain();
	this->sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->price = 300;
	this->getSprite()->setScale(m_SCALE_32x32 / 2);
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
	this->attackAnimate = animateAttack;
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
	Animation* animationHit = Animation::createWithSpriteFrames(animHit, 0.15f);
	auto animateHit = Animate::create(animationHit);
	animateHit->retain();
	this->hitAnimate = animateHit;
	hitAnimate->retain();

	// Adding the physic to player
	addPhysic();
	createSlash();
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
	if (!this->getAlive())
	{
		return;
	}
	auto rpIdleAnimate = RepeatForever::create(this->getIdleAnimate());
	rpIdleAnimate->setTag(TAG_ANIMATE_IDLE1);
	auto rpAttackAnimate = this->getAttackAnimate();
	rpAttackAnimate->setTag(TAG_ANIMATE_ATTACK);
	auto rpRunAnimate = RepeatForever::create(this->getRunAnimate());
	rpRunAnimate->setTag(TAG_ANIMATE_RUN);

	auto player = Update::GetInstance()->getPlayer();

	auto range = std::sqrt(pow((this->getSprite()->getPosition().x - player->getSprite()->getPosition().x), 2) + pow((this->getSprite()->getPosition().y - player->getSprite()->getPosition().y), 2));
	auto vectorMoveToSpawnPoint = Vec2(this->getPosSpawn().x - this->getSprite()->getPosition().x, this->getPosSpawn().y - this->getSprite()->getPosition().y);
	auto vectorMoveToPlayer = Vec2(player->getSprite()->getPosition() - this->getSprite()->getPosition()) - Vec2(50, 0);
	if (range < VISION_OF_KNIGHT) {
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
			if ((player->getSprite()->getPosition().y < (this->getSprite()->getPosition().y + 200)) &&
				player->getSprite()->getPosition().y >(this->getSprite()->getPosition().y - 200) &&
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

void KnightBoss::setOriginColor(Color3B color)
{
	this->originColor = color;
}

void KnightBoss::evolve()
{
	Sound::GetInstance()->soundKnightBossAbsorb();
	isEvoled = true;
	this->setDamage(this->getDamage() * 2);
	this->setHP(Update::GetInstance()->getHPOfPlayer() * 2);
	auto scaleCurr = this->getSprite()->getScale() * 2;
	auto scaleTo = ScaleTo::create(0.5f, scaleCurr);
	this->getSprite()->runAction(scaleTo);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/KnightBoss/evolve.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	emitter->setScale(m_SCALE_32x32 / 32);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
}

void KnightBoss::Stun()
{
	auto delay = DelayTime::create(Update::GetInstance()->getStunTime());
	sprite->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
	sprite->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
	sprite->stopAllActionsByTag(TAG_ANIMATE_RUN);

	sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
	auto color = this->originColor;
	auto turnBlue = CallFunc::create([this]()
	{
		this->sprite->setColor(Color3B(0, 0, 255));
	});
	auto turnBackColor = CallFunc::create([this, color]()
	{
		this->getSprite()->setColor(color);
	});
	auto sequence = Sequence::create(turnBlue, delay, turnBackColor, nullptr);
	sequence->setTag(TAG_ANIMATE_FREEZER);
	sprite->runAction(sequence);
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
	auto distance = this->getSprite()->getContentSize().width * m_SCALE_32x32 / 4;
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
	this->sprite->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
	this->sprite->stopAllActionsByTag(TAG_ANIMATE_RUN);
	this->sprite->stopAllActionsByTag(TAG_ANIMATE_IDLE1);

	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_FREEZER) == 0)
	{
		auto animation = this->getHitAnimate();
		animation->setTag(TAG_ANIMATE_HIT);
		this->sprite->runAction(animation);
	}
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
	Update::GetInstance()->setStateUlti(1);
	auto stateSlow = to_string(Update::GetInstance()->getStateSlow());
	auto stateUlti = to_string(Update::GetInstance()->getStateUlti());
	FileUtils::getInstance()->writeStringToFile(stateSlow + "\r\n" + stateUlti, Update::GetInstance()->getPathStateSkill());
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
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/KnightBoss/explode.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	emitter->setScale(m_SCALE_32x32 / 8);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
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
	m_slash = new Slash(this->getSprite()->getContentSize().width * m_SCALE_32x32 / 2, this->getSprite()->getContentSize().height * m_SCALE_32x32 / 2);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_KNIGHT_ATTACK);
	targetScene->addChild(m_slash->getSprite());
	m_slash->setDamge(this->damage);
}

Slash * KnightBoss::getSlash()
{
	return this->m_slash;
}
