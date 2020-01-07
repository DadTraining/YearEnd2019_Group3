#include "OptionsLayer.h"

cocos2d::Layer * OptionsLayer::createLayer()
{
	return OptionsLayer::create();
}

bool OptionsLayer::init()
{
	if (!LayerColor::initWithColor(cocos2d::Color4B(0, 0, 0, 200))) {
		return false;
	}

	auto bg = cocos2d::Sprite::create("ui/popup/ui_ocean_popup_landscape.png");
	auto title = cocos2d::Label::createWithTTF("Pause", "fonts/joystix monospace.ttf", 38);
	auto titleLayer = cocos2d::Sprite::create("ui/button/ui_ocean_button.png");
	auto exit = cocos2d::ui::Button::create("ui/button/ui_ocean_button_exit.png", "ui/button/ui_blue_button_exit.png");

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	this->setContentSize(visibleSize);

	bg->setPosition(visibleSize / 2);
	bg->setContentSize(visibleSize*0.3f);
	auto bgSize = bg->getContentSize();

	titleLayer->addChild(title);
	titleLayer->setContentSize(cocos2d::Size(bgSize.width / 2, bgSize.height / 4));
	titleLayer->setPosition(cocos2d::Vec2(bgSize.width / 2, bgSize.height));
	title->setPosition(titleLayer->getContentSize() / 2);

	exit->setScale(0.25f);
	exit->setPosition(cocos2d::Vec2(bgSize.width / 2, 0));
	exit->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
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

	bg->addChild(titleLayer, 0);
	bg->addChild(exit, 0);
	this->addChild(bg, 0);

	return true;
}