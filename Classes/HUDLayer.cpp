# include "Model.h"
# include "HUDLayer.h"
# include "Sound.h"
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
	healthBar = HealthBarLayer::createLayer();
	this->addChild(healthBar);
	//Adding the minimap to the hud
	addMiniMap();
	this->addChild(_hudScore, 0);
	CreateJoystick(this);
	CreateAttackBtn(this);
	CreateSkillABtn(this);
	CreateSkillBBtn(this);
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
	auto rpAnimateIdle = RepeatForever::create(targetPlayer->getIdleAnimate());
	rpAnimateIdle->setTag(TAG_ANIMATE_IDLE1);
	auto rpAnimateRun = RepeatForever::create(targetPlayer->getRunAnimate());
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
		if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_HIT) == 0)
		{
			targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
			if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) == 0)
			{
				targetPlayer->getSprite()->runAction(rpAnimateRun);
			}
		}
		targetPlayer->getSprite()->getPhysicsBody()->setVelocity(pos * SPEED_PLAYER);

		//m_tiledMap->setPosition(m_tiledMap->getPosition() - pos / (SPEED * 2));
	}
	else
	{
		if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_HIT) == 0)
		{
			targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
			if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) == 0)
			{
				targetPlayer->getSprite()->runAction(rpAnimateIdle);
			}
		}
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
		auto spriteCacheAttack = SpriteFrameCache::getInstance();
		spriteCacheAttack->addSpriteFramesWithFile("Resources/sprites/Player/Attacks/attackA.plist", "Resources/sprites/Player/Attacks/attackA.png");
		char nameAnimateAttack[50] = { 0 };
		Vector<SpriteFrame*> animAttack;
		for (int i = 1; i < 8; i++)
		{
			sprintf(nameAnimateAttack, "attack-A%d.png", i);
			auto frame = spriteCacheAttack->getSpriteFrameByName(nameAnimateAttack);
			animAttack.pushBack(frame);
		}
		Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.07f);
		auto animateAttack = Animate::create(animationAtack);
		animateAttack->retain();
		targetPlayer->setAttackAnimate(animateAttack);
		auto rpAnimateAttack = targetPlayer->getAttackAnimate();
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
				targetPlayer->normalAttack();
				Sound::GetInstance()->soundPlayerAttack1();
			}

			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			if (rpAnimateAttack->isDone()) {
				targetPlayer->getSprite()->stopAllActions();
				break;
			}
		}
		default:
			break;
		}
	});

}

void HudLayer::CreateSkillABtn(Layer * layer)
{
	// init attackButton
	skillBtn = ui::Button::create("Resources/Buttons/AttackButtonNormal.png", "Resources/Buttons/AttackButtonPressed.png");
	layer->addChild(skillBtn);
	skillBtn->setPosition(Vec2(1250, 300));

}

void HudLayer::UpdateSkillABtn(float dt)
{
	skillBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto spriteCacheAttack = SpriteFrameCache::getInstance();
		spriteCacheAttack->addSpriteFramesWithFile("Resources/sprites/Player/Attacks/attackB.plist", "Resources/sprites/Player/Attacks/attackB.png");
		char nameAnimateAttack[50] = { 0 };
		Vector<SpriteFrame*> animAttack;
		for (int i = 1; i < 7; i++)
		{
			sprintf(nameAnimateAttack, "attack-B%d.png", i);
			auto frame = spriteCacheAttack->getSpriteFrameByName(nameAnimateAttack);
			animAttack.pushBack(frame);
		}
		Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.07f);
		auto animateAttack = Animate::create(animationAtack);
		animateAttack->retain();
		targetPlayer->setAttackAnimate(animateAttack);
		auto rpAnimateAttack = targetPlayer->getAttackAnimate();
		rpAnimateAttack->setTag(TAG_ANIMATE_ATTACK);
		switch (type)
		{
			// In case when the player press on the screen
		case ui::Widget::TouchEventType::BEGAN:
		{
			// If the player still have the Idle animation or run animation then remove it
			if (targetPlayer->getVillagersNum() >= 10 && targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0 || targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0) {
				targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
				targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
				targetPlayer->getSprite()->runAction(rpAnimateAttack);
				targetPlayer->increaseVillager(-10);
				targetPlayer->normalAttack();
				Sound::GetInstance()->soundPlayerAttack1();
			}
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			if (rpAnimateAttack->isDone()) {
				targetPlayer->getSprite()->stopAllActions();
				break;
			}
		}
		default:
			break;
		}
	});
}

void HudLayer::CreateSkillBBtn(Layer * layer)
{
	// init attackButton
	attackBtn = ui::Button::create("Resources/Buttons/AttackButtonNormal.png", "Resources/Buttons/AttackButtonPressed.png");
	layer->addChild(attackBtn);
	attackBtn->setPosition(Vec2(1150, 100));
	attackBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto spriteCacheAttack = SpriteFrameCache::getInstance();
		spriteCacheAttack->addSpriteFramesWithFile("Resources/sprites/Player/Attacks/attackC.plist", "Resources/sprites/Player/Attacks/attackC.png");
		char nameAnimateAttack[50] = { 0 };
		Vector<SpriteFrame*> animAttack;
		for (int i = 1; i < 8; i++)
		{
			sprintf(nameAnimateAttack, "attack-C%d.png", i);
			auto frame = spriteCacheAttack->getSpriteFrameByName(nameAnimateAttack);
			animAttack.pushBack(frame);
		}
		Animation* animationAtack = Animation::createWithSpriteFrames(animAttack, 0.07f);
		auto animateAttack = Animate::create(animationAtack);
		animateAttack->retain();
		targetPlayer->setAttackAnimate(animateAttack);
		auto rpAnimateAttack = targetPlayer->getAttackAnimate();
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
				targetPlayer->normalAttack();
				Sound::GetInstance()->soundPlayerAttack1();
			}

			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			if (rpAnimateAttack->isDone()) {
				targetPlayer->getSprite()->stopAllActions();
				break;
			}
		}
		default:
			break;
		}
	});
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

void HudLayer::addVilagerPoint()
{
	_numCollected++;
}

void HudLayer::addMiniMap()
{
	miniMap = MiniMapLayer::createLayer();
	this->addChild(miniMap);
}

void HudLayer::createCameraHUD()
{
	cameraHUD = Camera::create();
	cameraHUD->setCameraFlag(CameraFlag::USER2);
	this->setCameraMask((unsigned short)CameraFlag::USER2);
	targetScene->addChild(cameraHUD);
}

void HudLayer::update(float dt)
{
	_hudScore->setString(std::to_string(this->_numCollected));
	// if player still alive
	if (targetPlayer->getAlive())
	{
		UpdateJoystick(dt);
	}
	if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) > 0) {
		targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
		targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
	}
	if (targetPlayer->getVillagersNum() >= 10) {
		UpdateSkillABtn(dt);
	}
		healthBar->update(dt);
	miniMap->update(dt);

}