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
	auto title = cocos2d::Label::createWithTTF("PAUSE", "Resources/fonts/joystix monospace.ttf", 172);
	auto titleBoard = cocos2d::Sprite::create("Resources/ui/button/ui_ocean_button.png");
	auto play = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button_play.png", "Resources/ui/button/ui_blue_button_play.png");
	auto home = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button_home.png", "Resources/ui/button/ui_blue_button_home.png");

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	this->setContentSize(visibleSize);

	bg->setPosition(visibleSize / 2);
	bg->setContentSize(cocos2d::Size(visibleSize.width*0.3f, 150));
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
			this->removeFromParent();
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
			this->removeFromParent();
			Director::getInstance()->replaceScene(MainMenu::createScene());
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});

	// ------------------------Toggle Button--------------------------------- //
	auto itemOn = cocos2d::MenuItemImage::create("Resources/ui/button/ui_ocean_button_soundon.png", "Resources/ui/button/ui_blue_button_soundon.png", [&](Ref* sender) {
	});

	auto itemOff = cocos2d::MenuItemImage::create("Resources/ui/button/ui_ocean_button_soundoff.png", "Resources/ui/button/ui_blue_button_soundoff.png", [&](Ref* sender) {
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


	bg->addChild(pMenu, 1);
	bg->addChild(titleBoard, 0);
	bg->addChild(play, 0);
	bg->addChild(home, 0);
	this->addChild(bg, 0);

	return true;
}
