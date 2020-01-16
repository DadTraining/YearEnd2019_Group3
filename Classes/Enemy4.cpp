#include "Enemy4.h"
#include "Update.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Sound.h"
USING_NS_CC;

Enemy4::Enemy4(Scene* scene) {
	//init sprite and Animate
	targetScene = scene;
	this->init();


}

Enemy4::~Enemy4()
{
}

void Enemy4::init()
{
	//Create sprite
	this->sprite = Sprite::create("Resources/sprites/Enemy4/Idle/idle_0.png");
	this->sprite->setScale(m_SCALE_32x32 / 2);

	auto randEnemy4 = rand() % 10;
	if (randEnemy4 == 0) {
		this->damage = Update::GetInstance()->getDamageOfEm4() * 2;
		this->hP = Update::GetInstance()->getHPOfEm4() * 2;
		this->sprite->setScale(this->sprite->getScale() * 2);
		this->price = rand() % 21 + 20;
	}
	else {
		this->damage = Update::GetInstance()->getDamageOfEm4();
		this->hP = Update::GetInstance()->getHPOfEm4();
		this->price = rand() % 11 + 10;
	}
	//Create animate attackA
	auto spriteCacheAttack_Em4 = SpriteFrameCache::getInstance();
	spriteCacheAttack_Em4->addSpriteFramesWithFile("Resources/sprites/Enemy4/Attack/attack.plist", "Resources/sprites/Enemy4/Attack/attack.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 0; i < 7; i++)
	{
		sprintf(nameAnimateAttack, "attack_%d.png", i);
		auto frame = spriteCacheAttack_Em4->getSpriteFrameByName(nameAnimateAttack);
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.1f);
	auto animateAttack = Animate::create(animationAtack);
	animateAttack->retain();
	this->attackAnimate = animateAttack;
	attackAnimate->retain();

	//Create animate idle
	auto spriteCacheIdle_Em4 = SpriteFrameCache::getInstance();
	spriteCacheIdle_Em4->addSpriteFramesWithFile("Resources/sprites/Enemy4/Idle/idle.plist", "Resources/sprites/Enemy4/Idle/idle.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 0; i < 4; i++)
	{
		sprintf(nameAnimateIdle, "idle_%d.png", i);
		auto frame = spriteCacheIdle_Em4->getSpriteFrameByName(nameAnimateIdle);
		animIdle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, 0.2f);
	auto animateIdle = Animate::create(animationIdle);
	animateIdle->retain();
	this->idleAnimate = animateIdle;
	idleAnimate->retain();

	//Create animate dead
	auto spriteCacheDead_MB1 = SpriteFrameCache::getInstance();
	spriteCacheDead_MB1->addSpriteFramesWithFile("Resources/sprites/Enemy4/Dead/dead.plist", "Resources/sprites/Enemy4/Dead/dead.png");
	char nameAnimateDead[50] = { 0 };
	Vector<SpriteFrame*> animDead;
	for (int i = 0; i < 10; i++)
	{
		sprintf(nameAnimateDead, "dead_%d.png", i);
		auto frame = spriteCacheDead_MB1->getSpriteFrameByName(nameAnimateDead);
		animDead.pushBack(frame);
	}
	Animation* animationDead = Animation::createWithSpriteFrames(animDead, 0.15f);
	auto animateDead = Animate::create(animationDead);
	animateDead->retain();
	this->deadAnimate = animateDead;
	deadAnimate->retain();

	//Create animate Hit
	auto spriteCacheHit_MB1 = SpriteFrameCache::getInstance();
	spriteCacheHit_MB1->addSpriteFramesWithFile("Resources/sprites/Enemy4/Hit/hit.plist", "Resources/sprites/Enemy4/Hit/hit.png");
	char nameAnimateHit[50] = { 0 };
	Vector<SpriteFrame*> animHit;
	for (int i = 0; i < 4; i++)
	{
		sprintf(nameAnimateHit, "hit_%d.png", i);
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

void Enemy4::setSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void Enemy4::setAttackAnimate(Animate * attackAnimate)
{
	this->attackAnimate = attackAnimate;
}

void Enemy4::setIdleAnimate(Animate * idleAnimate)
{
	this->idleAnimate = idleAnimate;
}

void Enemy4::setHitAnimate(Animate * hitAnimate)
{
	this->hitAnimate = hitAnimate;
}

void Enemy4::setRunAnimate(Animate * runAnimate)
{
	this->runAnimate = runAnimate;
}

void Enemy4::setDeadAnimate(Animate * deadAnimate)
{
	this->deadAnimate = deadAnimate;
}

void Enemy4::setHP(float hP)
{
	this->hP = hP;
}

void Enemy4::setDamage(float  damage)
{
	this->damage = damage;
}

void Enemy4::setPosSpawn(Point point)
{
	this->posSpawn = point;
}

void Enemy4::setAIforEnemy()
{
	auto rpIdleAnimate = RepeatForever::create(this->getIdleAnimate());
	rpIdleAnimate->setTag(TAG_ANIMATE_IDLE1);
	auto rpAttackAnimate = RepeatForever::create(this->getAttackAnimate());
	rpAttackAnimate->setTag(TAG_ANIMATE_ATTACK);

	auto player = Update::GetInstance()->getPlayer();

	auto range = std::sqrt(pow((this->getSprite()->getPosition().x - player->getSprite()->getPosition().x), 2) + pow((this->getSprite()->getPosition().y - player->getSprite()->getPosition().y), 2));
	auto vectorMoveToSpawnPoint = Vec2(this->getPosSpawn().x - this->getSprite()->getPosition().x, this->getPosSpawn().y - this->getSprite()->getPosition().y);
	auto vectorMoveToPlayer = Vec2(player->getSprite()->getPosition() - this->getSprite()->getPosition()) - Vec2(50, 0);
	if (range < VISION_OF_EM4) {
		if (player->getHP() > 0) {
			if (player->getSprite()->getPosition().x < this->getSprite()->getPosition().x) {
				this->getSprite()->setFlipX(180);
			}
			if (player->getSprite()->getPosition().x > this->getSprite()->getPosition().x) {
				this->getSprite()->setFlipX(0);
			}
			if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0) {
				this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
				this->getSprite()->runAction(rpAttackAnimate);
				this->normalAttack();
				this->addDust();
			}
		}
		// When player die
		else {
			if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) > 0) {
				this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
				this->getSprite()->stopAllActionsByTag(TAG_ATTACK);
				this->getSprite()->runAction(rpIdleAnimate);
			}
		}
	}
	else {
		if (this->getPosSpawn().x == this->getSprite()->getPosition().x) {
			if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) == 0) {
				this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
				this->getSprite()->stopAllActionsByTag(TAG_ATTACK);
				this->getSprite()->runAction(rpIdleAnimate);
			}
		}
	}
}

Sprite * Enemy4::getSprite()
{
	return this->sprite;
}

Animate * Enemy4::getAttackAnimate()
{
	return this->attackAnimate;
}

Animate * Enemy4::getIdleAnimate()
{
	return this->idleAnimate;
}

Animate * Enemy4::getHitAnimate()
{
	return this->hitAnimate;
}

Animate * Enemy4::getRunAnimate()
{
	return this->runAnimate;
}

Animate * Enemy4::getDeadAnimate()
{
	return this->deadAnimate;
}

float  Enemy4::getHP()
{
	return this->hP;
}

float  Enemy4::getDamage()
{
	return this->damage;
}

Point Enemy4::getPosSpawn()
{
	return this->posSpawn;
}

void Enemy4::normalAttack()
{
	auto scene = this->targetScene;
	auto slash = this->m_slash;
	auto delay = DelayTime::create(0.5f);
	auto delayRefesh = DelayTime::create(0.25f);
	auto attack = CallFunc::create([scene, slash]()
	{
		auto playerPosition = Update::GetInstance()->getPlayer()->getSprite()->getPosition();
		auto emitter = CCParticleSystemQuad::create("Resources/Effect/SkillEm4/attackEnemy4.plist");
		emitter->setPosition(playerPosition);
		emitter->setScale(m_SCALE_32x32 / 8);
		scene->addChild(emitter);
		emitter->setAutoRemoveOnFinish(true);
		slash->getSprite()->setPosition(playerPosition);
	});

	auto refreshAttack = CallFunc::create([slash]()
	{
		slash->getSprite()->setPosition(Vec2(-100, -100));
	});
	auto sequence = Sequence::create(delay, attack, delayRefesh, refreshAttack, nullptr);
	auto rpSequence = RepeatForever::create(sequence);
	rpSequence->setTag(TAG_ATTACK);
	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ATTACK) == 0)
	{
		this->getSprite()->runAction(rpSequence);
	}
}

void Enemy4::gotHit(int damage)
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

void Enemy4::update(float deltaTime)
{
	if (!this->getAlive())
	{
		return;
	}
	//this->m_slash->getSprite()->setPosition(Vec2(-100, -100));

	if (this->getSprite()->getNumberOfRunningActions() == 0)
	{
		auto animationIdle = RepeatForever::create(this->getIdleAnimate());
		animationIdle->setTag(TAG_ANIMATE_IDLE1);
		this->getSprite()->runAction(animationIdle);
	}
}

void Enemy4::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_ENEMY4);
	this->getSprite()->setPhysicsBody(physicsBody);
}

void Enemy4::setIndex(int index)
{
	this->getSprite()->getPhysicsBody()->setGroup(index);
}

void Enemy4::Die()
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
	mySprite->runAction(sequence);
}

void Enemy4::setAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool Enemy4::getAlive()
{
	return this->isAlive;
}

void Enemy4::addDust()
{
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/SkillEm4/smokeEffect.plist");
	auto emitterPosition = Vec2(this->getSprite()->getPosition().x, this->getSprite()->getPosition().y
		- this->getSprite()->getContentSize().height);
	emitter->setPosition(emitterPosition);
	emitter->setScale(0.25f);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
}

void Enemy4::createSlash()
{
	m_slash = new Slash(10, 10);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_ENEMY4_ATTACK);
	targetScene->addChild(m_slash->getSprite());
	m_slash->setDamge(this->damage);
}

Slash * Enemy4::getSlash()
{
	return this->m_slash;
}

void Enemy4::Stun()
{
	if (this->isAlive == false)
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