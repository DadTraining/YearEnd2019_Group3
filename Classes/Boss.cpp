#include "Boss.h"
#include "Update.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Sound.h"
# define TAG_BOSS_ATTACK 999
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
	this->price = 1000;
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
	auto rpAttackAnimate = RepeatForever::create(this->getAttackAnimate());
	rpAttackAnimate->setTag(TAG_ANIMATE_ATTACK);

	auto player = Update::GetInstance()->getPlayer();
	auto range = std::sqrt(pow((this->getSprite()->getPosition().x - player->getSprite()->getPosition().x), 2) + pow((this->getSprite()->getPosition().y - player->getSprite()->getPosition().y), 2));
	if (range < 600) {
		if (player->getHP() > 0) {
			if (player->getSprite()->getPosition().x < this->getSprite()->getPosition().x) {
				this->getSprite()->setFlipX(180);
			}
			if (player->getSprite()->getPosition().x > this->getSprite()->getPosition().x) {
				this->getSprite()->setFlipX(0);
			}
			if (range < 500) {
				if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0) {
					this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
					this->getSprite()->runAction(rpAttackAnimate);
					this->attack();
				}
			}
			else {
				if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) > 0) {
					this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
					this->getSprite()->stopAllActionsByTag(TAG_BOSS_ATTACK);
					fireSlash->getSprite()->setScale(1.0f);
					this->getSprite()->runAction(rpIdleAnimate);
				}
			}
		}
		else {
			if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) > 0) {
				this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
				this->getSprite()->stopAllActionsByTag(TAG_BOSS_ATTACK);
				fireSlash->getSprite()->setScale(1.0f);
				this->getSprite()->runAction(rpIdleAnimate);
			}
		}
	}
	else {
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
				this->getSprite()->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
				fireSlash->getSprite()->setScale(1.0f);
				this->getSprite()->stopAllActionsByTag(TAG_BOSS_ATTACK);
				this->getSprite()->runAction(rpIdleAnimate);
			}
		}
	}
}

void Boss::Stun()
{
	auto delay = DelayTime::create(Update::GetInstance()->getStunTime());
	sprite->stopAllActions();
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
	}
	else {
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
		this->fireSlash->getSprite()->setPosition(Vec2(-200, -200));
		this->fireSlash->getSprite()->setScale(1.0f);
	}
	else {
		this->normalAttack();
	}

	if (this->getSprite()->getNumberOfRunningActions() == 0)
	{
		auto animationIdle = RepeatForever::create(this->getIdleAnimate());
		animationIdle->setTag(TAG_ANIMATE_IDLE1);
		this->getSprite()->runAction(animationIdle);
	}
}

void Boss::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setPositionOffset(Vec2(100, 0));
	this->getSprite()->setAnchorPoint(Vec2(0.5f, 0.5f));
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(Model::BITMASK_BOSS);
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
	auto fade = FadeOut::create(1.5f);
	this->isAlive = false;
	this->fireSlash->getSprite()->setPosition(Vec2(-200, -200));
	//this->fireSlash->getSprite()->removeFromParent();
	Update::GetInstance()->getPlayer()->increaseVillager(this->price);
	auto dieAnimation = this->getDeadAnimate();
	auto spawn = Spawn::create(fade, dieAnimation, nullptr);
	auto sequence = Sequence::create(spawn, callbackHide, nullptr);
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

void Boss::attack()
{
	auto maxHealth = this->getHP() / Update::GetInstance()->getHPOfBoss();
	auto callbackHide = CallFunc::create([this, maxHealth]()
	{
		if (maxHealth < 0.5)
		{
			auto random = rand() % 2;
			switch (random)
			{
			case 0:
				this->AttackFire();
				break;
			case 1:
				this->AttackHeal();
				break;
			}
		}
		else {
			this->AttackFire();
		}
	});
	auto delay = DelayTime::create(2.0f);
	auto sequence = Sequence::create(delay, callbackHide, nullptr);
	auto rpSequence = RepeatForever::create(sequence);
	rpSequence->setTag(TAG_BOSS_ATTACK);
	this->getSprite()->stopAllActionsByTag(TAG_BOSS_ATTACK);
	if (this->getSprite()->getNumberOfRunningActionsByTag(TAG_BOSS_ATTACK) == 0)
	{
		this->getSprite()->runAction(rpSequence);
	}
}

void Boss::AttackFire()
{
	Sound::GetInstance()->soundBossSkillFire();
	auto FireEffect = CCParticleSystemQuad::create("Resources/Effect/SkillBossB/skillFire3.plist");
	FireEffect->setPosition(this->getSprite()->getPosition());
	FireEffect->setScale(1.5f);
	FireEffect->setAnchorPoint(Vec2(0.5f, 0.5f));
	targetScene->addChild(FireEffect);
	FireEffect->setAutoRemoveOnFinish(false);
	// create PhysicBody for the attack
	auto scaleTo = ScaleTo::create(1.4f, 6);
	auto fireSprite = fireSlash->getSprite();
	auto callbackHide = CallFunc::create([fireSprite]()
	{
		fireSprite->setPosition(-200, -200);
		fireSprite->setScale(1.0f);
	});
	auto sequence = Sequence::create(scaleTo, callbackHide, nullptr);
	fireSlash->getSprite()->setPosition(this->getSprite()->getPosition());
	fireSlash->getSprite()->runAction(sequence);

}

void Boss::AttackHeal()
{
	Sound::GetInstance()->soundBossSkillHeal();
	auto healEffect = CCParticleSystemQuad::create("Resources/Effect/SkillBossB/skillHeal.plist");
	healEffect->setPosition(this->getSprite()->getPosition());
	healEffect->setScale(1.5f);
	healEffect->setAnchorPoint(Vec2(0.5f, 0.5f));
	healEffect->setSpeed(0.5f);
	targetScene->addChild(healEffect);

	// define heal number
	auto healNumber = Update::GetInstance()->getHPOfBoss() - this->getHP();
	this->setHP(this->getHP() + healNumber * 0.3);
}

void Boss::createSlash()
{
	fireSlash = new Slash(100, 100);
	auto physicBody = PhysicsBody::createCircle(100.0f);
	physicBody->setContactTestBitmask(true);
	fireSlash->getSprite()->setPhysicsBody(physicBody);
	fireSlash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_BOSS_ATTACK);
	targetScene->addChild(fireSlash->getSprite());
	fireSlash->setDamge(this->damage);
	// create fireSprite
}

Slash * Boss::getSlash()
{
	return this->fireSlash;
}
