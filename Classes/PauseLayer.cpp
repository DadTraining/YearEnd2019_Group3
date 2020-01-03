#include "PauseLayer.h"

cocos2d::Layer * PauseLayer::createLayer()
{
	return PauseLayer::create();
}

bool PauseLayer::init()
{
	if (!LayerColor::initWithColor(cocos2d::Color4B(0, 0, 0, 150))) {
		return false;
	}

	auto bg = cocos2d::Sprite::create("Resources/ui/popup/ui_ocean_popup_landscape.png");
	auto title = cocos2d::Label::createWithTTF("PAUSE", "Resources/fonts/joystix monospace.ttf", 38);
	auto play = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button_play.png", "Resources/ui/button/ui_blue_button_play.png");
	auto setting = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button_play.png", "Resources/ui/button/ui_blue_button_play.png");

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	this->setContentSize(visibleSize);

	bg->setPosition(visibleSize / 2);
	bg->setContentSize(visibleSize*0.5f);
	auto bgSize = bg->getContentSize();

	title->setPosition(bg->getContentSize() / 2);

	play->setScale(0.25f);
	play->setPosition(cocos2d::Vec2(bgSize.width / 2, 0));
	play->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			this->removeFromParent();
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});

	this->addChild(bg, 0);

	return true;
}
