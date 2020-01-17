#include "ResultScene.h"
#include "Update.h"
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
	isAlive = Update::GetInstance()->getPlayer()->getAlive();
	if (isAlive) {
	numVillager = Update::GetInstance()->getPlayer()->getVillagersNum();
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto rsLayer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 0, 0, 255));
	rsLayer->setPosition(cocos2d::Vec2(0, visibleSize.height*0.2));
	rsLayer->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height*0.6));
	std::string noti = (!isAlive)?"DEAD!!!":"YOU'RE SAFE!!!";
	if (isAlive) {
		auto hp = to_string(Update::GetInstance()->getHPOfPlayer());
		auto damage = to_string(Update::GetInstance()->getDamageOfPlayer());
		Update::GetInstance()->setSumVillages(Update::GetInstance()->getSumVillages() + this->numVillager);
		auto sumVillages = to_string(Update::GetInstance()->getSumVillages());
		auto conditionUlti = to_string(Update::GetInstance()->getConditionUlti());
		auto stunTime = to_string(Update::GetInstance()->getStunTime());
		FileUtils::getInstance()->writeStringToFile(hp + "\r\n" + damage + "\r\n" + sumVillages + "\r\n" + conditionUlti + "\r\n" +stunTime, Update::GetInstance()->getPath());
	}

	auto rsText = cocos2d::Label::create("+" + std::to_string(this->numVillager), "Resources/fonts/joystix monospace.ttf", 36);
	rsText->setPosition(rsLayer->getContentSize() / 2);
	rsLayer->addChild(rsText, 0);
	auto notiText = cocos2d::Label::createWithTTF(noti, "Resources/fonts/joystix monospace.ttf", 96);

	notiText->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	notiText->setTextColor(cocos2d::Color4B::BLACK);
	notiText->enableOutline(cocos2d::Color4B::WHITE, 5);
	notiText->setPosition(visibleSize.width / 2, visibleSize.height*0.9);

	auto returnBaseBtn = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button.png", "Resources/ui/button/ui_blue_button.png");
	returnBaseBtn->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height*0.1));
	returnBaseBtn->setScale(0.2);
	returnBaseBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			cocos2d::Director::getInstance()->replaceScene(MainMenu::createScene());
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});

	auto btnContent = cocos2d::Label::createWithTTF("Home", "Resources/fonts/joystix monospace.ttf", 128);
	btnContent->setPosition(returnBaseBtn->getContentSize() / 2);

	returnBaseBtn->addChild(btnContent, 0);

	this->addChild(notiText, 1);
	this->addChild(rsLayer, 0);
	this->addChild(returnBaseBtn, 1);
	return true;
}
