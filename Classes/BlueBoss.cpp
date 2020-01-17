#include "BlueBoss.h"
#include "Update.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Sound.h"
USING_NS_CC;

BlueBoss::BlueBoss(Scene* scene) {
	//init sprite and Animate
	targetScene = scene;
	this->init();


}

BlueBoss::~BlueBoss()
{
}

void BlueBoss::init()
{
	this->sprite = Sprite::create("Resources/sprites/dMiniBoss/Idle/idle-1.png");
	this->sprite->setScale(m_SCALE_32x32 * 1.5);
	this->price = 500;
	this->damage = Update::GetInstance()->getDamageOfBlueBoss();
	this->hP =Update::GetInstance()->getHPOfBlueBoss();

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
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.15f);
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
	Animation* animationHit = Animation::createWithSpriteFrames(animHit, 0.25f);
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

void BlueBoss::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void BlueBoss::setAttackAnimate(Animate * attackAnimate)
{
	this->attackAnimate = attackAnimate;
}

void BlueBoss::setIdleAnimate(Animate * idleAnimate)
{
	this->idleAnimate = idleAnimate;
}

void BlueBoss::setHitAnimate(Animate * hitAnimate)
{
	this->hitAnimate = hitAnimate;
}

void BlueBoss::setRunAnimate(Animate * runAnimate)
{
	this->runAnimate = runAnimate;
}

void BlueBoss::setDeadAnimate(Animate * deadAnimate)
{
	this->deadAnimate = deadAnimate;
}

void BlueBoss::setHP(float hP)
{
	this->hP = hP;
}

void BlueBoss::setDamage(float  damage)
{
	this->damage = damage;
}

void BlueBoss::setPosSpawn(Point point)
{
	this->posSpawn = point;
}

void BlueBoss::setAIforEnemy()
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
	auto vectorMoveToPlayer = Vec2(player->getSprite()->getPosition() - this->getSprite()->getPosition()) - Vec2(50, 0);
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

Sprite * BlueBoss::getSprite()
{
	return this->sprite;
}

Animate * BlueBoss::getAttackAnimate()
{
	return this->attackAnimate;
}

Animate * BlueBoss::getIdleAnimate()
{
	return this->idleAnimate;
}

Animate * BlueBoss::getHitAnimate()
{
	return this->hitAnimate;
}

Animate * BlueBoss::getRunAnimate()
{
	return this->runAnimate;
}

Animate * BlueBoss::getDeadAnimate()
{
	return this->deadAnimate;
}

float  BlueBoss::getHP()
{
	return this->hP;
}

float  BlueBoss::getDamage()
{
	return this->damage;
}

Point BlueBoss::getPosSpawn()
{
	return this->posSpawn;
}

void BlueBoss::normalAttack()
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

void BlueBoss::gotHit(int damage)
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

void BlueBoss::update(float deltaTime)
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

void BlueBoss::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize()-Size(100, 50), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_BLUEBOSS);
	this->getSprite()->setPhysicsBody(physicsBody);
}

void BlueBoss::setIndex(int index)
{
	this->getSprite()->getPhysicsBody()->setGroup(index);
}

void BlueBoss::Die()
{
	Update::GetInstance()->setStatekSlow(1);
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

void BlueBoss::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool BlueBoss::getAlive()
{
	return this->isAlive;
}

void BlueBoss::createSlash()
{
	m_slash = new Slash(400, 250);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_BLUEBOSS_ATTACK);
	m_slash->getSprite()->getPhysicsBody()->setContactTestBitmask(true);
	targetScene->addChild(m_slash->getSprite());
	m_slash->setDamge(this->damage);
}

Slash * BlueBoss::getSlash()
{
	return this->m_slash;
}

void BlueBoss::Stun()
{
	auto delay = DelayTime::create(Update::GetInstance()->getStunTime());
	sprite->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
	sprite->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
	sprite->stopAllActionsByTag(TAG_ANIMATE_RUN);
	auto turnBlue = CallFunc::create([this]()
	{
		this->sprite->setColor(Color3B(0, 0, 255));
	});
	auto turnBackColor = CallFunc::create([this]()
	{
		this->getSprite()->setColor(Color3B(255, 255, 255));
	});
	auto sequence = Sequence::create(turnBlue, delay, turnBackColor, nullptr);
	sequence->setTag(TAG_ANIMATE_FREEZER);
	sprite->runAction(sequence);
	sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Monster/freezer.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
}