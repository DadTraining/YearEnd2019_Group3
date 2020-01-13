#include "HealthBarLayer.h"
#include "Update.h"


cocos2d::Layer * HealthBarLayer::createLayer()
{
	return HealthBarLayer::create();
}

bool HealthBarLayer::init()
{
	if (!LayerColor::initWithColor(cocos2d::Color4B(0, 0, 0, 0))) {
		return false;
	}
	maxHP = Update::GetInstance()->getHPOfPlayer();
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	
	auto bg = cocos2d::Sprite::create("Resources/ui/popup/ui_ocean_popup_landscape.png");
	bg->setScale(0.75);
	
	
	bg->setAnchorPoint(cocos2d::Vec2(0, 1));
	bg->setContentSize(cocos2d::Size(visibleSize.width*0.4, visibleSize.height*0.2));
	bg->setPosition(0, visibleSize.height);
	bg->setOpacity(200);



	auto bgHealthbar = cocos2d::Sprite::create("Resources/ui/healthbar/healthbar_1.png");

	sliderhealth = cocos2d::ui::LoadingBar::create("Resources/ui/healthbar/healthbar_11.png");
	sliderhealth->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
	sliderhealth->setPercent(100);

	auto heart = cocos2d::Sprite::create("Resources/ui/healthbar/heart.png");

	textVillager = cocos2d::Label::createWithTTF(std::to_string(numVillager), "Resources/fonts/joystix monospace.ttf", 38);

	heart->setPosition(bg->getContentSize().width*0.1, bg->getContentSize().height / 2 + 30);
	heart->setScale(0.1);

	bgHealthbar->setAnchorPoint(cocos2d::Vec2(0, 0.5));
	bgHealthbar->setPosition(heart->getPosition().x + 40, heart->getPosition().y);

	sliderhealth->setAnchorPoint(cocos2d::Size(0, 0));

	textVillager->setAnchorPoint(cocos2d::Size(0, 0));
	textVillager->setPosition(bgHealthbar->getPosition().x, bgHealthbar->getPosition().y - 75);

	bg->addChild(heart, 0);
	bgHealthbar->addChild(sliderhealth, 0);
	bg->addChild(bgHealthbar, 0);
	bg->addChild(textVillager, 0);
	this->addChild(bg, 0);

	return true;
}

void HealthBarLayer::update(float dt)
{
	this->numVillager = Update::GetInstance()->getPlayer()->getVillagersNum();
	textVillager->setString(std::to_string(numVillager));
	this->healthPercent = Update::GetInstance()->getPlayer()->getHP() * 100 /maxHP;
	sliderhealth->setPercent(healthPercent);
}




