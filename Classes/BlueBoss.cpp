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
	//Create sprite
	this->sprite = Sprite::create("Resources/sprites/BlueBoss/Run/run1.png");
	this->sprite->setScale(m_SCALE_32x32);
	this->damage = Update::GetInstance()->getDamageOfBoss();
	this->hP = Update::GetInstance()->getHPOfBoss();
	
	//Create animate attackA
	auto spriteCacheAttack_BB = SpriteFrameCache::getInstance();
	spriteCacheAttack_BB->addSpriteFramesWithFile("Resources/sprites/BlueBoss/Attacks/attack.plist", "Resources/sprites/BlueBoss/Attacks/attack.png");
	char nameAnimateAttack[50] = { 0 };
	Vector<SpriteFrame*> animAttack;
	for (int i = 1; i < 15; i++)
	{
		sprintf(nameAnimateAttack, "attack%d.png", i);
		auto frame = spriteCacheAttack_BB->getSpriteFrameByName(nameAnimateAttack);
		animAttack.pushBack(frame);
	}
	Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.1f);
	auto animateAttack = Animate::create(animationAtack);
	animateAttack->retain();
	this->attackAnimate = animateAttack;
	attackAnimate->retain();

	//Create animate run
	auto spriteCacheRun_BB = SpriteFrameCache::getInstance();
	spriteCacheRun_BB->addSpriteFramesWithFile("Resources/sprites/BlueBoss/Run/run.plist", "Resources/sprites/BlueBoss/Run/run.png");
	char nameAnimateRun[50] = { 0 };
	Vector<SpriteFrame*> animRun;
	for (int i = 1; i < 4; i++)
	{
		sprintf(nameAnimateRun, "run%d.png", i);
		auto frame = spriteCacheRun_BB->getSpriteFrameByName(nameAnimateRun);
		animRun.pushBack(frame);
	}
	Animation* animationRun = Animation::createWithSpriteFrames(animRun, 0.1f);
	auto animateWalk = Animate::create(animationRun);
	animateWalk->retain();
	this->runAnimate = animateWalk;

	//Create animate defence 
	auto spriteCacheDefence_BB = SpriteFrameCache::getInstance();
	spriteCacheDefence_BB->addSpriteFramesWithFile("Resources/sprites/BlueBoss/Defence/defence.plist", "Resources/sprites/BlueBoss/Defence/defence.png");
	char nameAnimateDefence[50] = { 0 };
	Vector<SpriteFrame*> animDefence;
	for (int i = 1; i < 4; i++)
	{
		sprintf(nameAnimateDefence, "run%d.png", i);
		auto frame = spriteCacheDefence_BB->getSpriteFrameByName(nameAnimateDefence);
		animDefence.pushBack(frame);
	}
	Animation* animationDefence = Animation::createWithSpriteFrames(animDefence, 0.1f);
	auto animateDefence = Animate::create(animationDefence);
	animateDefence->retain();
	this->defenceAnimate = animateDefence;

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

void BlueBoss::setDefenceAnimate(Animate * defenceAnimate)
{
	this->defenceAnimate = defenceAnimate;
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
	auto rpAttackAnimate = this->getAttackAnimate();
	rpAttackAnimate->setTag(TAG_ANIMATE_ATTACK);
	auto rpRunAnimate = RepeatForever::create(this->getRunAnimate());
	rpRunAnimate->setTag(TAG_ANIMATE_RUN);

	auto player = Update::GetInstance()->getPlayer();

	auto range = std::sqrt(pow((this->getSprite()->getPosition().x - player->getSprite()->getPosition().x), 2) + pow((this->getSprite()->getPosition().y - player->getSprite()->getPosition().y), 2));
	auto vectorMoveToSpawnPoint = Vec2(this->getPosSpawn().x - this->getSprite()->getPosition().x, this->getPosSpawn().y - this->getSprite()->getPosition().y);
	auto vectorMoveToPlayer = Vec2(player->getSprite()->getPosition().x - this->getSprite()->getPosition().x, player->getSprite()->getPosition().y - this->getSprite()->getPosition().y);

	if (range < VISION_OF_EM2) {
		if (player->getHP() > 0) {
			this->getSprite()->getPhysicsBody()->setVelocity(vectorMoveToPlayer*SPEED_MB01);
			if (player->getSprite()->getPosition().x < this->getSprite()->getPosition().x) {
				this->getSprite()->setFlipX(180);
			}
			if (player->getSprite()->getPosition().x > this->getSprite()->getPosition().x) {
				this->getSprite()->setFlipX(0);
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

Animate * BlueBoss::getDefenceAnimate()
{
	return this->defenceAnimate;
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
	this->sprite->stopAllActions();
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

void BlueBoss::addPhysic()
{
	auto physicsBody = PhysicsBody::createBox(this->getSprite()->getContentSize() - Size(80, 30), PhysicsMaterial(1.0f, 0.0f, 1.0f));
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
	auto fade = FadeOut::create(1.5f);
	auto spawn = Spawn::create(fade, callbackHide, nullptr);
	spawn->setTag(TAG_ANIMATE_DIE);
	mySprite->runAction(spawn);
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
	m_slash = new Slash(150, 50);
	m_slash->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_BLUEBOSS_ATTACK);
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
	sprite->stopAllActions();
	sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
	sprite->runAction(delay);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Monster/freezer.plist");
	emitter->setPosition(this->getSprite()->getPosition());
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
}