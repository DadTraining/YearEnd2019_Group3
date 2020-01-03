#include "ResultScene.h"

cocos2d::Scene * ResultScene::createScene()
{
	return ResultScene::create();
}

bool ResultScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto rsLayer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 0, 0, 255));
	rsLayer->setPosition(cocos2d::Vec2(0, visibleSize.height*0.2));
	rsLayer->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height*0.6));
	std::string noti = "";

	if (this->isDead)
	{
		noti = "DEAD!!!";
	}
	else
	{
		noti = "VICTORY!!!";

		auto rsText = cocos2d::Label::create("+" + std::to_string(this->numVillager), "fonts/joystix monospace.ttf", 36);
		rsText->setPosition(rsLayer->getContentSize() / 2);
		rsLayer->addChild(rsText, 0);
	}
	auto notiText = cocos2d::Label::createWithTTF(noti, "fonts/joystix monospace.ttf", 96);

	notiText->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
	notiText->setTextColor(cocos2d::Color4B::BLACK);
	notiText->enableOutline(cocos2d::Color4B::WHITE, 5);
	notiText->setPosition(visibleSize.width / 2, visibleSize.height*0.9);

	auto exit = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button_exit.png", "Resources/ui/button/ui_blue_button_exit.png");


	this->addChild(notiText, 1);
	this->addChild(rsLayer, 0);
	return true;
}
