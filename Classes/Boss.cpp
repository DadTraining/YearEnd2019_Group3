#include "Boss.h"
#include "Update.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Sound.h"
USING_NS_CC;

Boss::Boss(Scene* scene) {
	targetScene = scene;
	this->init();
}

Boss::~Boss()
{
}

void Boss::init()
{
	this->damage = Update::GetInstance()->getDamageOfBoss();
	this->hP = Update::GetInstance()->getHPOfBoss();
	//Create sprite
	this->sprite = Sprite::create("Resources/sprites/BossB/Idle/nyt1.png");
	this->sprite->setScale(m_SCALE_32x32);
	//Create animate attackA
	auto spriteCacheAttack_Boss = SpriteFrameCache::getInstance();
	spriteCacheAttack_Boss->addSpriteFramesWithFile("Resources/sprites/BossB/Attacks/nyh.plist", "Resources/sprites/BossB/Attacks/nyh.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 1; i < 9; i++)
	{
		sprintf(nameAnimateAttack, "nyh%d.png", i);
		auto frame = spriteCacheAttack_Boss->getSpriteFrameByName(nameAnimateAttack);
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, TIME_ONE_ATTACK);
	auto animateAttack = Animate::create(animationAtack);
	animateAttack->retain();
	this->attackAnimate = animateAttack;
	attackAnimate->retain();

	//Create animate idle
	auto spriteCacheIdle_Boss = SpriteFrameCache::getInstance();
	spriteCacheIdle_Boss->addSpriteFramesWithFile("Resources/sprites/BossB/Idle/nyt.plist", "Resources/sprites/BossB/Idle/nyt.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 1; i < 7; i++)
	{
		sprintf(nameAnimateIdle, "nyt%d.png", i);
		auto frame = spriteCacheIdle_Boss->getSpriteFrameByName(nameAnimateIdle);
		animIdle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, TIME_ONE_IDLE);
	auto animateIdle = Animate::create(animationIdle);
	animateIdle->retain();
	this->idleAnimate = animateIdle;
	idleAnimate->retain();

	//Create animate dead
	auto spriteCacheDead_MB1 = SpriteFrameCache::getInstance();
	spriteCacheDead_MB1->addSpriteFramesWithFile("Resources/sprites/BossB/Dead/nym.plist", "Resources/sprites/BossB/Dead/nym.png");
	char nameAnimateDead[50] = { 0 };
	Vector<SpriteFrame*> animDead;
	for (int i = 1; i < 9; i++)
	{
		sprintf(nameAnimateDead, "nym%d.png", i);
		auto frame = spriteCacheDead_MB1->getSpriteFrameByName(nameAnimateDead);
		animDead.pushBack(frame);
	}
	Animation* animationDead = Animation::createWithSpriteFrames(animDead, TIME_ONE_DEAD);
	auto animateDead = Animate::create(animationDead);
	animateDead->retain();
	this->deadAnimate = animateDead;
	deadAnimate->retain();

	
	// Add physics
	addPhysic();
	// init slash
	this->createSlash();
	// init isAlive
	this->isAlive = true;
}

void Boss::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void Boss::setAttackAnimate(Animate * attackAnimate)
{
	this->attackAnimate = attackAnimate;
}

void Boss::setIdleAnimate(Animate * idleAnimate)
{
	this->idleAnimate = idleAnimate;
}

void Boss::setHitAnimate(Animate * hitAnimate)
{
	this->hitAnimate = hitAnimate;
}

void Boss::setRunAnimate(Animate * runAnimate)
{
	this->runAnimate = runAnimate;
}

void Boss::setDeadAnimate(Animate * deadAnimate)
{
	this->deadAnimate = deadAnimate;
}

void Boss::setHP(float hP)
{
	this->hP = hP;
}

void Boss::setDamage(float  damage)
{
	this->damage = damage;
}

void Boss::setPosSpawn(Point point)
{
	this->posSpawn = point;
}

void Boss::setAIforEnemy()
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

void Boss::Stun()
{
	auto delay = DelayTime::create(1.5f);
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

Sprite * Boss::getSprite()
{
	return this->sprite;
}

Animate * Boss::getAttackAnimate()
{
	return this->attackAnimate;
}

Animate * Boss::getIdleAnimate()
{
	return this->idleAnimate;
}

Animate * Boss::getHitAnimate()
{
	return this->hitAnimate;
}

Animate * Boss::getRunAnimate()
{
	return this->runAnimate;
}

Animate * Boss::getDeadAnimate()
{
	return this->deadAnimate;
}

float  Boss::getHP()
{
	return this->hP;
}

float  Boss::getDamage()
{
	return this->damage;
}

Point Boss::getPosSpawn()
{
	return this->posSpawn;
}

void Boss::normalAttack()
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

void Boss::gotHit(int damage)
{
	if (!this->getAlive())
	{
		return;
	}
	Sound::GetInstance()->soundSkeletonHit();
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

void Boss::update(float deltaTime)
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

void Boss::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() - Size(80, 30), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_ENEMY);
	this->getSprite()->setPhysicsBody(physicsBody);
}

void Boss::setIndex(int index)
{
	this->getSprite()->getPhysicsBody()->setGroup(index);
}

void Boss::Die()
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
	sequence->setTag(TAG_ANIMATE_DIE);
	mySprite->runAction(sequence);
}

void Boss::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool Boss::getAlive()
{
	return this->isAlive;
}

void Boss::createSlash()
{
	m_slash = new Slash(100, 100);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_ENEMY1_ATTACK);
	targetScene->addChild(m_slash->getSprite());
	m_slash->setDamge(this->damage);
}

Slash * Boss::getSlash()
{
	return this->m_slash;
}
