#pragma once
# include "Model.h"
# include "HUDLayer.h"
# include "Sound.h"
# include "CastleScene.h"
# include "MainMenu.h"

#define MARGIN_JOYSTICK 50
#define SCALE_BUTTON 0.75
using namespace cocos2d;

HudLayer::HudLayer(Scene* scene, Player* player)
{
	targetScene = scene;
	targetPlayer = player;
	this->init();
}

bool HudLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	createHud();
	createCameraHUD();
	scheduleUpdate();
	return true;
}

void HudLayer::createHud()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	targetScene->addChild(this, 10);
	healthBar = HealthBarLayer::createLayer();
	this->addChild(healthBar);
	CCLOG("------- Done createhealthBar");

	//Adding the minimap to the hud
	addMiniMap();
	addPauseButton(this);
	CreateJoystick(this);
	CreateAttackNormal(this);
	CreateSkillUltimate(this);
	CreateSkillSpear(this);
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
	attackBtn->setScale(SCALE_BUTTON);
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
			//If the player still have the Idle animation or run animation then remove it
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
			if (rpAnimateAttack->isDone() && targetPlayer->getAlive()) {
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
	skillABtn->setScale(SCALE_BUTTON);
	layer->addChild(skillABtn);
	skillABtn->setPosition(Vec2(1450, 400));
	skillABtn->setEnabled(false);

}

void HudLayer::UpdateSkillUltimate(float dt)
{
	if (Update::GetInstance()->getStateUlti() == 1 && targetPlayer->getVillagersNum() >= 300) {
		skillABtn->setEnabled(true);
		skillABtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
			auto rpAnimateSkillA = targetPlayer->getSkillAAnimate();
			rpAnimateSkillA->setTag(TAG_ANIMATE_ATTACK);
			switch (type)
			{
				// In case when the player press on the screen
			case ui::Widget::TouchEventType::BEGAN:
			{
				skillABtn->setScale(SCALE_BUTTON*1.1);
				// If the player still have the Idle animation or run animation then remove it
				if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0
					|| targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0
					&& targetPlayer->getAlive()) {
					targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
					targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
					targetPlayer->getSprite()->stopAllActions();
					targetPlayer->getSprite()->runAction(rpAnimateSkillA);
					targetPlayer->increaseVillager(0);
					targetPlayer->UltimateAttack();
					Sound::GetInstance()->soundPlayerAttack1();
				}
				break;
			}
			case ui::Widget::TouchEventType::ENDED:
			{
				skillABtn->setScale(SCALE_BUTTON);
				if (rpAnimateSkillA->isDone() && targetPlayer->getAlive()) {
					targetPlayer->getSprite()->stopAllActions();
					break;
				}
			}
			case ui::Widget::TouchEventType::MOVED:
			{
				skillABtn->setScale(SCALE_BUTTON*1.1);

			}
			case ui::Widget::TouchEventType::CANCELED:
			{
				skillABtn->setScale(SCALE_BUTTON);

			}
			default:
				break;
			}

		});
	}
	else {
		skillABtn->setEnabled(false);
	}

}

void HudLayer::CreateSkillSpear(Layer * layer)
{
	// init attackButton
	skillBBtn = ui::Button::create("Resources/Buttons/SkillButtonSpear.png");
	skillBBtn->setScale(SCALE_BUTTON);
	layer->addChild(skillBBtn);
	skillBBtn->setPosition(Vec2(1200, 150));
	skillBBtn->setEnabled(false);

}

void HudLayer::UpdateSkillSpear(float dt)
{
	if (Update::GetInstance()->getStateSlow() == 1) {
		skillBBtn->setEnabled(true);
		skillBBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
			skillBBtn->setScale(SCALE_BUTTON*1.5);
			auto rpAnimateSkillB = targetPlayer->getSkillBAnimate();
			rpAnimateSkillB->setTag(TAG_ANIMATE_ATTACK);
			switch (type)
			{
				// In case when the player press on the screen
			case ui::Widget::TouchEventType::BEGAN:
			{
				skillBBtn->setScale(SCALE_BUTTON*1.1);
				// If the player still have the Idle animation or run animation then remove it
				if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0 || targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0
					&& targetPlayer->getAlive()) {
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
				skillBBtn->setScale(SCALE_BUTTON);
				if (rpAnimateSkillB->isDone() && targetPlayer->getAlive()) {
					targetPlayer->getSprite()->stopAllActions();
					break;
				}
			}
			case ui::Widget::TouchEventType::MOVED:
			{
				skillBBtn->setScale(SCALE_BUTTON*1.1);

			}
			case ui::Widget::TouchEventType::CANCELED:
			{
				skillBBtn->setScale(SCALE_BUTTON);

			}
			default:
				break;
			}
		});
	}
}

HudLayer::~HudLayer()
{
}

void HudLayer::addMiniMap()
{
	if (this->targetScene->getTag() == Model::FINAL_BOSS_PORTAL_TYPE)
	{
		return;
	}
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

void HudLayer::addPauseButton(Layer * layer)
{
	auto pauseButton = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button_setting.png", "Resources/ui/button/ui_blue_button_setting.png");
	pauseButton->addTouchEventListener([&](cocos2d::Ref* Sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			pauseLayer = cocos2d::LayerColor::create(Color4B(0, 0, 0, 150));
			//---------------------------//
			auto bg = cocos2d::Sprite::create("Resources/ui/popup/ui_ocean_popup_landscape.png");
			auto title = cocos2d::Label::createWithTTF("PAUSE", "Resources/fonts/joystix monospace.ttf", 172);
			auto titleBoard = cocos2d::Sprite::create("Resources/ui/button/ui_ocean_button.png");
			auto play = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button_play.png", "Resources/ui/button/ui_blue_button_play.png");
			auto home = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button_home.png", "Resources/ui/button/ui_blue_button_home.png");

			auto winSize = cocos2d::Director::getInstance()->getWinSize();
			this->setContentSize(winSize);

			bg->setPosition(winSize / 2);
			bg->setContentSize(cocos2d::Size(winSize.width*0.3f, 150));
			auto bgSize = bg->getContentSize();

			title->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
			title->setPosition(titleBoard->getContentSize() / 2);

			titleBoard->setScale(0.15);
			titleBoard->setPosition(bg->getContentSize().width / 2, bg->getContentSize().height);
			titleBoard->addChild(title);

			play->setScale(0.35f);
			play->setPosition(cocos2d::Vec2(bgSize.width / 2, 0));
			play->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
				switch (type)
				{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					break;
				case cocos2d::ui::Widget::TouchEventType::MOVED:
					break;
				case cocos2d::ui::Widget::TouchEventType::ENDED:
					pauseLayer->removeFromParent();
					this->setVisible(true);
					Director::getInstance()->resume();
					Sound::GetInstance()->stopSoundBackGround();
					break;
				case cocos2d::ui::Widget::TouchEventType::CANCELED:
					break;
				default:
					break;
				}
			});

			home->setScale(0.25f);
			home->setPosition(cocos2d::Vec2(play->getPositionX() + 125, play->getPositionY()));
			home->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
				switch (type)
				{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					break;
				case cocos2d::ui::Widget::TouchEventType::MOVED:
					break;
				case cocos2d::ui::Widget::TouchEventType::ENDED:
					this->setVisible(true);
					pauseLayer->removeFromParent();
					Director::getInstance()->resume();
					Sound::GetInstance()->stopSoundBackGround();
					Director::getInstance()->replaceScene(MainMenu::createScene());
					break;
				case cocos2d::ui::Widget::TouchEventType::CANCELED:
					break;
				default:
					break;
				}
			});

			// ------------------------Toggle Button--------------------------------- //
			itemOn = cocos2d::MenuItemImage::create("Resources/ui/button/ui_ocean_button_soundon.png", "Resources/ui/button/ui_blue_button_soundon.png", [&](Ref* sender) {
			});

			itemOff = cocos2d::MenuItemImage::create("Resources/ui/button/ui_ocean_button_soundoff.png", "Resources/ui/button/ui_blue_button_soundoff.png", [&](Ref* sender) {
			});

			auto itemToggleMusic = cocos2d::MenuItemToggle::createWithCallback([&](Ref* pSender) {
				cocos2d::MenuItemToggle *toggleItem = (cocos2d::MenuItemToggle *)pSender;
				if (toggleItem->getSelectedItem() == itemOn) {
					Sound::GetInstance()->setIsMute(false);
				}
				else if (toggleItem->getSelectedItem() == itemOff) {
					Sound::GetInstance()->setIsMute(true);
				}
			}, itemOn, itemOff, NULL);

			itemToggleMusic->setScale(0.25f);
			cocos2d::Menu* pMenu = cocos2d::Menu::create(itemToggleMusic, NULL);
			pMenu->setPosition(play->getPositionX() - 125, play->getPositionY());

			Director::getInstance()->pause();

			bg->addChild(pMenu, 1);
			bg->addChild(titleBoard, 0);
			bg->addChild(play, 0);
			bg->addChild(home, 0);
			pauseLayer->addChild(bg, 0);
			//---------------------------//

			auto visibleSize = Director::getInstance()->getVisibleSize();
			pauseLayer->setPosition(Update::GetInstance()->getPlayer()->getSprite()->getPosition() - Vec2(visibleSize.width / 2, visibleSize.height / 2));
			targetScene->addChild(pauseLayer, 1);
			this->setVisible(false);
		}
	});
	pauseButton->setScale(0.2);
	pauseButton->setAnchorPoint(cocos2d::Vec2(0, 1));
	pauseButton->setPosition(cocos2d::Vec2(0, layer->getContentSize().height*0.85));
	layer->addChild(pauseButton, 5);

}

void HudLayer::update(float dt)
{
	if (targetPlayer->getAlive())
	{
		UpdateJoystick(dt);
	}
	if (targetPlayer->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) > 0) {
		targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
		targetPlayer->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
	}
	UpdateSkillUltimate(dt);
	UpdateSkillSpear(dt);
	healthBar->update(dt);

	if (this->targetScene->getTag() != Model::FINAL_BOSS_PORTAL_TYPE)
	{
		miniMap->update(dt);
	}
}