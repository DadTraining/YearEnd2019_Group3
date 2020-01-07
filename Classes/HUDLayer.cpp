# include "Model.h"
# include "HUDLayer.h"
# include "Sound.h"
#define MARGIN_JOYSTICK 50
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
	_hudScore = Label::create(std::to_string(this->_numCollected), "Resources/fonts/arial.ttf", 24);
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
	CreateAttackNormal(this);
	CreateSkillUltimate(this);
	CreateSkillSpear(this);
	addPauseButton();
}

void HudLayer::CreateJoystick(Layer * layer)
{
	auto thumb = Sprite::create("Resources/sprites/JoyStick/thumb.png");
	auto joystick = Sprite::create("Resources/sprites/JoyStick/joystick.png");
	Rect joystickBaseDimensions = Rect(0, 0, 40.f, 40.0f);
	Point joystickBasePosition;
	joystickBasePosition = Vec2(MARGIN_JOYSTICK + thumb->getBoundingBox().size.width / 2 + joystick->getBoundingBox().size.width / 2
		, MARGIN_JOYSTICK + thumb->getBoundingBox().size.height / 2 + joystick->getBoundingBox().size.height / 2);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite(thumb);
	joystickBase->setAnchorPoint(Vec2(0, 0));
	joystickBase->setThumbSprite(joystick);
	joystickBase->getThumbSprite()->setScale(0.5f);
	joystickBase->setScale(2.0f);
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

void HudLayer::CreateAttackNormal(Layer * layer)
{
	// init attackButton
	attackBtn = ui::Button::create("Resources/Buttons/SkillButtonNormal.png");
	attackBtn->setScale(0.5f);
	//add touch event to attackButton
	layer->addChild(attackBtn);
	attackBtn->setPosition(Vec2(1450, 150));
	attackBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
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

void HudLayer::CreateSkillUltimate(Layer * layer)
{
	// init attackButton
	skillABtn = ui::Button::create("Resources/Buttons/SkillButton Ultimate.png");
	skillABtn->setScale(0.5f);
	layer->addChild(skillABtn);
	skillABtn->setPosition(Vec2(1450, 300));

}

void HudLayer::UpdateSkillUltimate(float dt)
{
	skillABtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto rpAnimateSkillA = targetPlayer->getSkillAAnimate();
		rpAnimateSkillA->setTag(TAG_ANIMATE_ATTACK);
		switch (type)
		{
			// In case when the player press on the screen
		case ui::Widget::TouchEventType::BEGAN:
		{
			// If the player still have the Idle animation or run animation then remove it
			if (targetPlayer->getVillagersNum() >= 10 
				&&(targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0 
				|| targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0)) {
				targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
				targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
				targetPlayer->getSprite()->stopAllActions();
				targetPlayer->getSprite()->runAction(rpAnimateSkillA);
				targetPlayer->increaseVillager(-50);
				targetPlayer->UltimateAttack();
				Sound::GetInstance()->soundPlayerAttack1();
			}
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			if (rpAnimateSkillA->isDone()) {
				targetPlayer->getSprite()->stopAllActions();
				break;
			}
		}
		default:
			break;
		}
	});
}

void HudLayer::CreateSkillSpear(Layer * layer)
{
	// init attackButton
	skillBBtn = ui::Button::create("Resources/Buttons/SkillButtonSpear.png");
	skillBBtn->setScale(0.5f);
	layer->addChild(skillBBtn);
	skillBBtn->setPosition(Vec2(1300, 150));
	skillBBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto rpAnimateSkillB = targetPlayer->getSkillBAnimate();
		rpAnimateSkillB->setTag(TAG_ANIMATE_ATTACK);
		switch (type)
		{
			// In case when the player press on the screen
		case ui::Widget::TouchEventType::BEGAN:
		{
			// If the player still have the Idle animation or run animation then remove it
			if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0 || targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0) {
				targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
				targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
				targetPlayer->getSprite()->stopAllActions();
				targetPlayer->getSprite()->runAction(rpAnimateSkillB);
				targetPlayer->spearAttack();
				Sound::GetInstance()->soundPlayerAttack1();
			}

			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			if (rpAnimateSkillB->isDone()) {
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
void HudLayer::addPauseButton()
{
	auto pauseBtn = cocos2d::ui::Button::create("ui/button/ui_ocean_button_pause.png", "ui/button/ui_blue_button_pause.png");
	
	pauseBtn->setScale(0.2);
	pauseBtn->setAnchorPoint(cocos2d::Vec2(0,1));
	pauseBtn->setPosition(cocos2d::Vec2(0,this->getContentSize().height*0.85));
	this->addChild(pauseBtn, 0);


	pauseBtn->addTouchEventListener([&](Ref* Sender,cocos2d::ui::Widget::TouchEventType type) {
		if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
			//auto pauseLayer = OptionsLayer::createLayer();
			//this->addChild(pauseLayer, 2);
			cocos2d::Director::getInstance()->pause();

		}
	});
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
		UpdateSkillUltimate(dt);
	}
	healthBar->update(dt);
	miniMap->update(dt);

}