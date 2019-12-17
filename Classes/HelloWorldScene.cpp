
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	player = new Player(this);

	auto targetSizePlayer = Size(80, 80);
	auto sizeOrigPlayer = player->getSprite()->getContentSize();

	this->spPlayer = Sprite::createWithSpriteFrame(player->getSprite()->getSpriteFrame());
	spPlayer->setAnchorPoint(Vec2(0.5, 0.5));
	spPlayer->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.5));
	spPlayer->setScale((targetSizePlayer.width / sizeOrigPlayer.width), (targetSizePlayer.height / sizeOrigPlayer.height));
	this->addChild(spPlayer);

	CreateJoystick(this);
	UpdateJoystick();
    return true;
}




void HelloWorld::CreateJoystick(Scene * scene)
{
	int joystickOffset = 10;

	Rect joystickBaseDimensions = Rect(0, 0, 40.0f, 40.0f);
	Point joystickBasePosition = Point(Director::getInstance()->getVisibleSize().width*0.1, Director::getInstance()->getVisibleSize().height*0.2);
	SneakyJoystickSkinnedBase* joystickBase = SneakyJoystickSkinnedBase::create();
	SneakyJoystick* joystick = new SneakyJoystick();
	joystick->initWithRect(joystickBaseDimensions);
	joystickBase->setBackgroundSprite(cocos2d::Sprite::create("sprites/JoyStick/joystick.png"));
	joystickBase->setThumbSprite(cocos2d::Sprite::create("sprites/JoyStick/thumb.png"));
	joystickBase->getThumbSprite()->setScale(0.5f);
	joystickBase->setScale(0.8f);
	joystickBase->setJoystick(joystick);
	joystickBase->setPosition(joystickBasePosition);
	leftJoystick = joystickBase->getJoystick();
	scene->addChild(joystickBase);
}

void HelloWorld::UpdateJoystick()
{
	Point pos = leftJoystick->getStickPosition();
	float radius = std::sqrt(pos.x*pos.x + pos.y*pos.y);
	auto moveUp = MoveBy::create(0.5f, Vec2(800, 100));
	if (radius > 0)
	{
		float degree = std::atan2f(pos.y, pos.x) * 180 / 3.141593;
		
		// GO UP
		if (degree < 120 && degree > 60)
		{
			spPlayer->runAction(RepeatForever::create(moveUp));
			log("ba");
		}
		// GO DOWN
		else if (degree < -60 && degree > -120)
		{
			spPlayer->runAction(RepeatForever::create(moveUp));
			log("ba");
		}
		// GO LEFT
		else if (degree > 150 || degree < -150)
		{
			spPlayer->runAction(RepeatForever::create(moveUp));
			log("ba");
		}
		// GO RIGHT
		else if (degree < 30 && degree > -30)
		{
			spPlayer->runAction(RepeatForever::create(moveUp));
			log("ba");
		}
		// GO LEFT UP
		else if (degree <= 150 && degree >= 120)
		{
			spPlayer->runAction(RepeatForever::create(moveUp));
			log("ba");
		}
		// GO LEFT DOWN
		else if (degree <= -120 && degree >= -150)
		{
			spPlayer->runAction(RepeatForever::create(moveUp));
			log("ba");
		}
		// GO RIGHT UP
		else if (degree <= 60 && degree >= 30)
		{
			spPlayer->runAction(RepeatForever::create(moveUp));
			log("ba");
		}
		// GO RIGHT DOWN
		else
		{
			spPlayer->runAction(RepeatForever::create(moveUp));
			log("ba");
		}
	}
	else
	{
		spPlayer->runAction(RepeatForever::create(player->getAnimateIdle()));
	}
}
