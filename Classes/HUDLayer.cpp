
# include "HUDLayer.h"

using namespace cocos2d;

HudLayer::HudLayer(Scene* scene, Player* player, TMXTiledMap* map)
{
	targetScene = scene;
	targetPlayer = player;
	m_tiledMap = map;
	this->init();
}

bool HudLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	createHud();
	_numCollected = 0;
	createCameraHUD();
	scheduleUpdate();
	return true;
}

void HudLayer::createHud()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// Init the layer of hud
	// create a label to increase the score
	_hudScore = Label::create(std::to_string(this->_numCollected), "fonts/arial.ttf", 24);
	int margin = 20;

	_hudScore->setPosition(Vec2(visibleSize.width - (_hudScore->getContentSize().width / 2) - margin,
		_hudScore->getContentSize().height / 2 + margin));

	targetScene->addChild(this, 10);
	this->addChild(_hudScore, 0);
	CreateJoystick(this);
	CreateAttackBtn(this);
}

void HudLayer::CreateJoystick(Layer * layer)
{
	auto thumb = Sprite::create("Resources/sprites/JoyStick/thumb.png");
	auto joystick = Sprite::create("Resources/sprites/JoyStick/joystick.png");
	Rect joystickBaseDimensions = Rect(0, 0, 40.f, 40.0f);
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
	activeRunRange = thumb->getBoundingBox().size.height / 2;
	layer->addChild(joystickBase);
}

void HudLayer::UpdateJoystick(float dt)
{
	Point pos = leftJoystick->getStickPosition();
	float radius = std::sqrt(pos.x*pos.x + pos.y*pos.y);
	auto rpAnimateIdle = RepeatForever::create(targetPlayer->getAnimateIdle());
	rpAnimateIdle->setTag(TAG_ANIMATE_IDLE1);
	auto rpAnimateRun = RepeatForever::create(targetPlayer->getAnimateRun());
	rpAnimateRun->setTag(TAG_ANIMATE_RUN);
	if (radius > 0)
	{
		float degree = std::atan2f(pos.y, pos.x) * 180 / 3.141593;
		if (degree > -90 && degree < 90) {
			targetPlayer->getSprite()->setFlipX(false);
		}
		else {
			targetPlayer->getSprite()->setFlipX(true);
		}
		targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
		targetPlayer->getSprite()->runAction(rpAnimateRun);
		targetPlayer->getSprite()->getPhysicsBody()->setVelocity(pos * SPEED);
		//m_tiledMap->setPosition(m_tiledMap->getPosition() - pos / (SPEED * 2));
	}
	else
	{
		targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
		targetPlayer->getSprite()->runAction(rpAnimateIdle);
		targetPlayer->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));

	}
}

void HudLayer::CreateAttackBtn(Layer * layer)
{
	// init attackButton
	attackBtn = ui::Button::create("Resources/Buttons/AttackButtonNormal.png", "Resources/Buttons/AttackButtonPressed.png");
	//add touch event to attackButton
	layer->addChild(attackBtn);
	attackBtn->setPosition(Vec2(1200, 200));
	attackBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto rpAnimateAttack = RepeatForever::create(targetPlayer->getAnimateAttack());
		rpAnimateAttack->setTag(TAG_ANIMATE_ATTACK);
		switch (type)
		{
			// In case when the player press on the screen
		case ui::Widget::TouchEventType::BEGAN:
		{
			// If the player still have the Idle animation or run animation then remove it
			if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0 || targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0) {
				targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
				targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
				targetPlayer->getSprite()->runAction(rpAnimateAttack);
			}

			break;
		}
		case ui::Widget::TouchEventType::MOVED:
		{
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			targetPlayer->getSprite()->stopAllActions();
			break;
		}
		default:
			break;
		}
	});

}

void HudLayer::update(float dt)
{
	_hudScore->setString(std::to_string(this->_numCollected));
	UpdateJoystick(dt);
	if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) > 0) {
		targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
		targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
	}
}

void HudLayer::setMap(TMXTiledMap * map)
{
	m_tiledMap = map;
}

TMXTiledMap * HudLayer::getMap()
{
	return m_tiledMap;
}

HudLayer::~HudLayer()
{
}

void HudLayer::createCameraHUD()
{
	cameraHUD = Camera::create();
	cameraHUD->setCameraFlag(CameraFlag::USER2);
	this->setCameraMask((unsigned short)CameraFlag::USER2);
	targetScene->addChild(cameraHUD);
}

