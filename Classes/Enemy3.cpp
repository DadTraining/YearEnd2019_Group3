#include "Enemy3.h"
#include "Update.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Sound.h"
USING_NS_CC;

Enemy3::Enemy3(Scene* scene) {
	//init sprite and Animate
	targetScene = scene;
	this->init();


}

Enemy3::~Enemy3()
{
}

void Enemy3::init()
{
	//Create sprite
	this->sprite = Sprite::create("Resources/sprites/rEnemy/Idle/idle-1.png");
	this->sprite->setScale(m_SCALE_32x32 / 2);

	auto randMiniBoss = rand() % 10;
	if (randMiniBoss == 0) {
		this->damage = Update::GetInstance()->getDamageOfEm3() * 2;
		this->hP = Update::GetInstance()->getHPOfEm3() * 2;
		this->sprite->setScale(this->sprite->getScale() * 1.5);
		this->price = rand() % 21 + 20;
	}
	else {
		this->damage = Update::GetInstance()->getDamageOfEm3();
		this->hP = Update::GetInstance()->getHPOfEm3();
		this->price = rand() % 11 + 10;
	}

	//Create animate attackA
	auto spriteCacheAttack_MB1 = SpriteFrameCache::getInstance();
	spriteCacheAttack_MB1->addSpriteFramesWithFile("Resources/sprites/rEnemy/Attack/attackA.plist", "Resources/sprites/rEnemy/Attack/attackA.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 1; i < 7; i++)
	{
		sprintf(nameAnimateAttack, "attack-A%d.png", i);
		auto frame = spriteCacheAttack_MB1->getSpriteFrameByName(nameAnimateAttack);
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.2f);
	auto animateAttack = Animate::create(animationAtack);
	animateAttack->retain();
	this->attackAnimate = animateAttack;
	attackAnimate->retain();

	//Create animate idle
	auto spriteCacheIdle_MB1 = SpriteFrameCache::getInstance();
	spriteCacheIdle_MB1->addSpriteFramesWithFile("Resources/sprites/rEnemy/Idle/idle.plist", "Resources/sprites/rEnemy/Idle/idle.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 1; i < 3; i++)
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
	spriteCacheDead_MB1->addSpriteFramesWithFile("Resources/sprites/rEnemy/Dead/dead.plist", "Resources/sprites/rEnemy/Dead/dead.png");
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
	spriteCacheRun_MB1->addSpriteFramesWithFile("Resources/sprites/rEnemy/Run/run.plist", "Resources/sprites/rEnemy/Run/run.png");
	char nameAnimateRun[50] = { 0 };
	Vector<SpriteFrame*> animRun;
	for (int i = 1; i < 13; i++)
	{
		sprintf(nameAnimateRun, "run-%d.png", i);
		auto frame = spriteCacheRun_MB1->getSpriteFrameByName(nameAnimateRun);
		animRun.pushBack(frame);
	}
	Animation* animationRun = Animation::createWithSpriteFrames(animRun, TIME_ONE_RUN);
	auto animateWalk = Animate::create(animationRun);
	animateWalk->retain();
	this->runAnimate = animateWalk;

	//Create animate Hit
	auto spriteCacheHit_MB1 = SpriteFrameCache::getInstance();
	spriteCacheHit_MB1->addSpriteFramesWithFile("Resources/sprites/rEnemy/Hit/hit.plist", "Resources/sprites/rEnemy/Hit/hit.png");
	char nameAnimateHit[50] = { 0 };
	Vector<SpriteFrame*> animHit;
	for (int i = 1; i < 5; i++)
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
	
	// init isAlive
	this->isAlive = true;
}

void Enemy3::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void Enemy3::setAttackAnimate(Animate * attackAnimate)
{
	this->attackAnimate = attackAnimate;
}

void Enemy3::setIdleAnimate(Animate * idleAnimate)
{
	this->idleAnimate = idleAnimate;
}

void Enemy3::setHitAnimate(Animate * hitAnimate)
{
	this->hitAnimate = hitAnimate;
}

void Enemy3::setRunAnimate(Animate * runAnimate)
{
	this->runAnimate = runAnimate;
}

void Enemy3::setDeadAnimate(Animate * deadAnimate)
{
	this->deadAnimate = deadAnimate;
}

void Enemy3::setHP(float hP)
{
	this->hP = hP;
}

void Enemy3::setDamage(float  damage)
{
	this->damage = damage;
}

void Enemy3::setPosSpawn(Point point)
{
	this->posSpawn = point;
}

void Enemy3::setAIforEnemy()
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

void Enemy3::Stun()
{
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
	sprite->runAction(sequence);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Monster/freezer.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	//emitter->setScale(m_SCALE / 8);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
}

Sprite * Enemy3::getSprite()
{
	return this->sprite;
}

Animate * Enemy3::getAttackAnimate()
{
	return this->attackAnimate;
}

Animate * Enemy3::getIdleAnimate()
{
	return this->idleAnimate;
}

Animate * Enemy3::getHitAnimate()
{
	return this->hitAnimate;
}

Animate * Enemy3::getRunAnimate()
{
	return this->runAnimate;
}

Animate * Enemy3::getDeadAnimate()
{
	return this->deadAnimate;
}

float  Enemy3::getHP()
{
	return this->hP;
}

float  Enemy3::getDamage()
{
	return this->damage;
}

Point Enemy3::getPosSpawn()
{
	return this->posSpawn;
}

void Enemy3::normalAttack()
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

void Enemy3::gotHit(int damage)
{
	if (!this->getAlive())
	{
		return;
	}
	Sound::GetInstance()->soundSkeletonHit();
	this->sprite->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
	this->sprite->stopAllActionsByTag(TAG_ANIMATE_RUN);
	this->sprite->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
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

void Enemy3::update(float deltaTime)
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

void Enemy3::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() - Size(80, 30), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_ENEMY3);
	this->getSprite()->setPhysicsBody(physicsBody);
}

void Enemy3::setIndex(int index)
{
	this->getSprite()->getPhysicsBody()->setGroup(index);
}

void Enemy3::Die()
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

void Enemy3::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool Enemy3::getAlive()
{
	return this->isAlive;
}

void Enemy3::createSlash()
{
	m_slash = new Slash(100, 100);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_ENEMY3_ATTACK);
	targetScene->addChild(m_slash->getSprite());
	m_slash->setDamge(this->damage);
}

Slash * Enemy3::getSlash()
{
	return this->m_slash;
}
