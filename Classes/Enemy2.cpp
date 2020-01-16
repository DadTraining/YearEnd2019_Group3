#include "Enemy2.h"
#include "Update.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Sound.h"
USING_NS_CC;

Enemy2::Enemy2(Scene* scene) {
	//init sprite and Animate
	targetScene = scene;
	this->init();


}

Enemy2::~Enemy2()
{
}

void Enemy2::init()
{
	//Create sprite
	this->sprite = Sprite::create("Resources/sprites/mEnemy/Idle/idle-1.png");
	this->sprite->setScale(m_SCALE_32x32 / 2);

	auto randMiniBoss = rand() % 10;
	if (randMiniBoss == 0) {
		this->damage = Update::GetInstance()->getDamageOfEm2() * 2;
		this->hP = Update::GetInstance()->getHPOfEm2() * 2;
		this->sprite->setScale(this->sprite->getScale() * 2);
		this->price = rand() % 21 + 20;
	}
	else {
		this->damage = Update::GetInstance()->getDamageOfEm2();
		this->hP = Update::GetInstance()->getHPOfEm2();
		this->price = rand() % 11 + 10;
	}
	//Create animate attackA
	auto spriteCacheAttack_Em2 = SpriteFrameCache::getInstance();
	spriteCacheAttack_Em2->addSpriteFramesWithFile("Resources/sprites/mEnemy/Attack/attackB.plist", "Resources/sprites/mEnemy/Attack/attackB.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 1; i < 11; i++)
	{
		sprintf(nameAnimateAttack, "attack-B%d.png", i);
		auto frame = spriteCacheAttack_Em2->getSpriteFrameByName(nameAnimateAttack);
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.1f);
	auto animateAttack = Animate::create(animationAtack);
	animateAttack->retain();
	this->attackAnimate = animateAttack;
	attackAnimate->retain();

	//Create animate idle
	auto spriteCacheIdle_Em2 = SpriteFrameCache::getInstance();
	spriteCacheIdle_Em2->addSpriteFramesWithFile("Resources/sprites/mEnemy/Idle/idle.plist", "Resources/sprites/mEnemy/Idle/idle.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 1; i < 3; i++)
	{
		sprintf(nameAnimateIdle, "idle-%d.png", i);
		auto frame = spriteCacheIdle_Em2->getSpriteFrameByName(nameAnimateIdle);
		animIdle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, 0.2f);
	auto animateIdle = Animate::create(animationIdle);
	animateIdle->retain();
	this->idleAnimate = animateIdle;
	idleAnimate->retain();

	//Create animate dead
	auto spriteCacheDead_MB1 = SpriteFrameCache::getInstance();
	spriteCacheDead_MB1->addSpriteFramesWithFile("Resources/sprites/mEnemy/Dead/dead.plist", "Resources/sprites/mEnemy/Dead/dead.png");
	char nameAnimateDead[50] = { 0 };
	Vector<SpriteFrame*> animDead;
	for (int i = 1; i < 5; i++)
	{
		sprintf(nameAnimateDead, "dead-%d.png", i);
		auto frame = spriteCacheDead_MB1->getSpriteFrameByName(nameAnimateDead);
		animDead.pushBack(frame);
	}
	Animation* animationDead = Animation::createWithSpriteFrames(animDead, 0.15f);
	auto animateDead = Animate::create(animationDead);
	animateDead->retain();
	this->deadAnimate = animateDead;
	deadAnimate->retain();

	//Create animate run
	auto spriteCacheRun_MB1 = SpriteFrameCache::getInstance();
	spriteCacheRun_MB1->addSpriteFramesWithFile("Resources/sprites/mEnemy/Walk/walk.plist", "Resources/sprites/mEnemy/Walk/walk.png");
	char nameAnimateRun[50] = { 0 };
	Vector<SpriteFrame*> animRun;
	for (int i = 1; i < 7; i++)
	{
		sprintf(nameAnimateRun, "walk-%d.png", i);
		auto frame = spriteCacheRun_MB1->getSpriteFrameByName(nameAnimateRun);
		animRun.pushBack(frame);
	}
	Animation* animationRun = Animation::createWithSpriteFrames(animRun, 0.1f);
	auto animateWalk = Animate::create(animationRun);
	animateWalk->retain();
	this->runAnimate = animateWalk;

	//Create animate Hit
	auto spriteCacheHit_MB1 = SpriteFrameCache::getInstance();
	spriteCacheHit_MB1->addSpriteFramesWithFile("Resources/sprites/mEnemy/Hit/hit.plist", "Resources/sprites/mEnemy/Hit/hit.png");
	char nameAnimateHit[50] = { 0 };
	Vector<SpriteFrame*> animHit;
	for (int i = 1; i < 4; i++)
	{
		sprintf(nameAnimateHit, "hit-%d.png", i);
		auto frame = spriteCacheHit_MB1->getSpriteFrameByName(nameAnimateHit);
		animHit.pushBack(frame);
	}
	Animation* animationHit = Animation::createWithSpriteFrames(animHit, 0.2f);
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

void Enemy2::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void Enemy2::setAttackAnimate(Animate * attackAnimate)
{
	this->attackAnimate = attackAnimate;
}

void Enemy2::setIdleAnimate(Animate * idleAnimate)
{
	this->idleAnimate = idleAnimate;
}

void Enemy2::setHitAnimate(Animate * hitAnimate)
{
	this->hitAnimate = hitAnimate;
}

void Enemy2::setRunAnimate(Animate * runAnimate)
{
	this->runAnimate = runAnimate;
}

void Enemy2::setDeadAnimate(Animate * deadAnimate)
{
	this->deadAnimate = deadAnimate;
}

void Enemy2::setHP(float hP)
{
	this->hP = hP;
}

void Enemy2::setDamage(float  damage)
{
	this->damage = damage;
}

void Enemy2::setPosSpawn(Point point)
{
	this->posSpawn = point;
}

void Enemy2::setAIforEnemy()
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
	auto vectorMoveToPlayer = Vec2(player->getSprite()->getPosition()- this->getSprite()->getPosition())- Vec2(50, 0);

	if (range < VISION_OF_EM2) {
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
					this->getSprite()->stopAllActionsByTag(TAG_ATTACK);
					this->getSprite()->runAction(rpRunAnimate);
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

Sprite * Enemy2::getSprite()
{
	return this->sprite;
}

Animate * Enemy2::getAttackAnimate()
{
	return this->attackAnimate;
}

Animate * Enemy2::getIdleAnimate()
{
	return this->idleAnimate;
}

Animate * Enemy2::getHitAnimate()
{
	return this->hitAnimate;
}

Animate * Enemy2::getRunAnimate()
{
	return this->runAnimate;
}

Animate * Enemy2::getDeadAnimate()
{
	return this->deadAnimate;
}

float  Enemy2::getHP()
{
	return this->hP;
}

float  Enemy2::getDamage()
{
	return this->damage;
}

Point Enemy2::getPosSpawn()
{
	return this->posSpawn;
}

void Enemy2::normalAttack()
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

void Enemy2::gotHit(int damage)
{
	if (!this->getAlive())
	{
		return;
	}
	Sound::GetInstance()->soundSkeletonHit();
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

void Enemy2::update(float deltaTime)
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

void Enemy2::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() - Size(80, 30), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_ENEMY2);
	this->getSprite()->setPhysicsBody(physicsBody);
}

void Enemy2::setIndex(int index)
{
	this->getSprite()->getPhysicsBody()->setGroup(index);
}

void Enemy2::Die()
{
	Sound::GetInstance()->soundSkeletonDie();
	this->getSprite()->stopAllActions();
	auto mySprite = this->getSprite();
	auto callbackHide = CallFunc::create([mySprite]()
	{
		mySprite->removeFromParent();
	});
	this->isAlive = false;
	this->m_slash->getSprite()->setPosition(Vec2(-100, -100));
	this->m_slash->getSprite()->removeFromParent();
	Update::GetInstance()->getPlayer()->increaseVillager(this->price);
	auto dieAnimation = this->getDeadAnimate();
	auto sequence = Sequence::create(dieAnimation, callbackHide, nullptr);
	sequence->setTag(TAG_ANIMATE_DIE);
	mySprite->runAction(sequence);
}

void Enemy2::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool Enemy2::getAlive()
{
	return this->isAlive;
}

void Enemy2::createSlash()
{
	m_slash = new Slash(150, 50);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_ENEMY2_ATTACK);
	targetScene->addChild(m_slash->getSprite());
	m_slash->setDamge(this->damage);
}

Slash * Enemy2::getSlash()
{
	return this->m_slash;
}

void Enemy2::Stun()
{
	if (!this->isAlive)
	{
		return;
	}
	auto delay = DelayTime::create(Update::GetInstance()->getStunTime());
	sprite->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
	sprite->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
	sprite->stopAllActionsByTag(TAG_ANIMATE_RUN);
	sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
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
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Monster/freezer.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
}