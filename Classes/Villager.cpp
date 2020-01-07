#include "Villager.h"
#include "Model.h"
#include "SimpleAudioEngine.h"
#include "Sound.h"
#define ONE_TIME_IDLE_VILLAGER 0.05f
#define DEFAULT_POINT 30
Villager::Villager(Scene * scene)
{
	targetScene = scene;
	this->init();
}

Villager::~Villager()
{
}

void Villager::init()
{
	this->initPoint();
	this->createIdleAnimation();
	this->addPhysic();
}

void Villager::update(float dt)
{
}

void Villager::createIdleAnimation()
{
	// Create Sprite
	this->sprite = Sprite::create("Resources/sprites/Village/Idle/spr_Idle_strip_1.png");
	float scalePoint = (float)point / (DEFAULT_POINT);
	this->sprite->setScale((m_SCALE_32x32 / 2) * scalePoint);
	auto spriteCacheFrame = SpriteFrameCache::getInstance();
	spriteCacheFrame->addSpriteFramesWithFile("Resources/sprites/Village/Idle/sideCityzen.plist", "Resources/sprites/Village/Idle/sideCityzen.png");
	char nameAnimateIdle[50] = { 0 };
	Vector<SpriteFrame*> animIdle;
	for (int i = 1; i < 17; i++)
	{
		sprintf(nameAnimateIdle, "spr_Idle_strip_%d.png", i);
		auto frame = spriteCacheFrame->getSpriteFrameByName(nameAnimateIdle);
		animIdle.pushBack(frame);
	}
	Animation* animationIdle = Animation::createWithSpriteFrames(animIdle, ONE_TIME_IDLE_VILLAGER);
	auto animateIdle = Animate::create(animationIdle);
	animateIdle->retain();
	this->idleAnimate = animateIdle;
	this->idleAnimate->retain();
}

void Villager::addPhysic()
{
	auto physicBody = PhysicsBody::createBox(this->getSprite()->getContentSize());
	this->sprite->setPhysicsBody(physicBody);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(Model::BITMASK_VILLAGER);
	physicBody->setContactTestBitmask(true);
}

Sprite * Villager::getSprite()
{
	return this->sprite;
}

Animate * Villager::getIdleAnimate()
{
	return this->idleAnimate;
}

void Villager::Die()
{
	Sound::GetInstance()->soundCollect();
	auto villagerSprite = this->getSprite();
	auto callbackHide = CallFunc::create([villagerSprite]()
	{
		villagerSprite->removeFromParent();
	});
	auto fade = FadeOut::create(0.5f);
	auto sequence = Sequence::create(fade, callbackHide, nullptr);
	villagerSprite->runAction(sequence);
	auto emitter = CCParticleSystemQuad::create("Resources/Effect/Villager/collected_effect.plist");
	emitter->setPosition(sprite->getPosition());
	emitter->setScale(m_SCALE_32x32 / 32);
	targetScene->addChild(emitter);
	emitter->setAutoRemoveOnFinish(true);
}

void Villager::initPoint()
{
	point = DEFAULT_POINT + rand() % 10;
}

int Villager::getPoint()
{
	return this->point;
}

void Villager::setPoint(int point)
{
	this->point = point;
}

void Villager::setIndex(int index)
{
	this->getSprite()->getPhysicsBody()->setGroup(index);
}
