
#include "GameStart.h"
#include "SimpleAudioEngine.h"
#define SPEED 2.5
USING_NS_CC;
Scene* GameStart::createScene()
{
    return GameStart::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameStart::init()
{
	if (!Scene::initWithPhysics())
		return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	player = new Player(this);

	auto targetSizePlayer = Size(60, 60);
	auto sizeOrigPlayer = player->getSprite()->getContentSize();

	this->spPlayer = Sprite::createWithSpriteFrame(player->getSprite()->getSpriteFrame());
	spPlayer->setAnchorPoint(Vec2(0.5, 0.5));
	spPlayer->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.5));
	spPlayer->setScale((targetSizePlayer.width / sizeOrigPlayer.width), (targetSizePlayer.height / sizeOrigPlayer.height));

	physicsBody = PhysicsBody::createBox(spPlayer->getContentSize());
	physicsBody->setDynamic(false);
	spPlayer->setPhysicsBody(physicsBody);
	this->addChild(spPlayer);

	CreateJoystick(this);
	scheduleUpdate();
    return true;
}


void GameStart::CreateJoystick(Scene * scene)
{
	auto thumb = Sprite::create("Resources/sprites/JoyStick/thumb.png");
	auto joystick = Sprite::create("Resources/sprites/JoyStick/joystick.png");
	Rect joystickBaseDimensions;
	joystickBaseDimensions = Rect(0, 0, 40.f, 40.0f);
	Point joystickBasePosition;
	joystickBasePosition = Vec2(thumb->getBoundingBox().size.width / 2 + joystick->getBoundingBox().size.width / 2
		, thumb->getBoundingBox().size.height / 2 + joystick->getBoundingBox().size.height / 2);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite(thumb);
	joystickBase->setThumbSprite(joystick);
	joystickBase->getThumbSprite()->setScale(0.5f);
	joystick->setScale(0.5f);
	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);
	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	this->addChild(joystickBase, 4);
	//joystickBase->setCameraMask(2);

	activeRunRange = thumb->getBoundingBox().size.height / 2;
}

void GameStart::UpdateJoystick(float dt)
{
	Point pos = leftJoystick->getStickPosition();
	float radius = std::sqrt(pos.x*pos.x + pos.y*pos.y);
	auto rpAnimateIdle = RepeatForever::create(player->getAnimateIdle());
	rpAnimateIdle->setTag(1);
	auto rpAnimateRun = RepeatForever::create(player->getAnimateRun());
	rpAnimateRun->setTag(2);
	if (radius > 0)
	{
		float degree = std::atan2f(pos.y, pos.x) * 180 / 3.141593;
		if(degree>-90 && degree<90){
			spPlayer->setFlipX(false);
		}
		else {
			spPlayer->setFlipX(true);
		}
		spPlayer->stopActionByTag(1);
		spPlayer->runAction(rpAnimateRun);
		physicsBody->setVelocity(pos*SPEED);
	}
	else
	{
		spPlayer->runAction(rpAnimateIdle);
		physicsBody->setVelocity(Vec2(0, 0));
		
	}
}

void GameStart::update(float dt)
{
	UpdateJoystick(dt);
}
