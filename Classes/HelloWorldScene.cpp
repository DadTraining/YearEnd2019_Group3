#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

PhysicsBody* physicsBody;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
	if (!Scene::initWithPhysics())
		return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	player = new Player(this);

	auto targetSizePlayer = Size(40, 40);
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




void HelloWorld::CreateJoystick(Scene * scene)
{
	auto thumb = Sprite::create("sprites/JoyStick/thumb.png");
	auto joystick = Sprite::create("sprites/JoyStick/joystick.png");
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

void HelloWorld::UpdateJoystick()
{
	Point pos = leftJoystick->getStickPosition();
	float radius = std::sqrt(pos.x*pos.x + pos.y*pos.y);
	auto moveUp = MoveBy::create(0.5f, Vec2(800, 100));
	if (radius > 0)
	{
		spPlayer->stopAllActions();
		physicsBody->setVelocity(pos);
	}
	else
	{
		spPlayer->runAction(RepeatForever::create(player->getAnimateAttack()));
	}
}

void HelloWorld::update(float dt)
{
	UpdateJoystick();
}
