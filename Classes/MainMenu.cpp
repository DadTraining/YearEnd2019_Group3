#include "MainMenu.h"
#include "Sound.h"
Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

bool MainMenu::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
	Sound::GetInstance()->soundMainMenu();
	string font = "Resources/fonts/joystix monospace.ttf";
	float fontSize = 48;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
    Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto bg = cocos2d::Sprite::create("Resources/ui/main-menu-bg.jpg");
	bg->setPosition(visibleSize / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);

	auto playLabel = cocos2d::Label::create("Play", font, fontSize);
	auto play = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button.png", "Resources/ui/button/ui_blue_button.png");
	play->setAnchorPoint(Vec2(0, 0));
	play->setScale(0.2f);
	play->addChild(playLabel, 0);
	play->setPosition(cocos2d::Vec2(visibleSize.width*0.75, visibleSize.height * 0.15));
	play->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			cocos2d::Director::getInstance()->replaceScene(LoadMapScene::createScene());
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});

	playLabel->setPosition(play->getContentSize() / 2);
	playLabel->setScale(5);

	bg->addChild(play, 0);
	this->addChild(bg, -1);
	// ------------------------Toggle Button--------------------------------- //

	itemOn = MenuItemImage::create("Resources/ui/button/ui_ocean_button_soundon.png", "Resources/ui/button/ui_blue_button_soundon.png", [&](Ref* sender) {
	});

	itemOff = MenuItemImage::create("Resources/ui/button/ui_ocean_button_soundoff.png", "Resources/ui/button/ui_blue_button_soundoff.png", [&](Ref* sender) {
	});

	auto itemToggleMusic = MenuItemToggle::createWithCallback([&](Ref* pSender) {
		MenuItemToggle *toggleItem = (MenuItemToggle *)pSender;
		if (toggleItem->getSelectedItem() == itemOn) {
			Sound::GetInstance()->setIsMute(false);
		}
		else if (toggleItem->getSelectedItem() == itemOff) {
			Sound::GetInstance()->setIsMute(true);
		}
	}, itemOn, itemOff, NULL);

	itemToggleMusic->setScale(0.2);
	Menu* pMenu = Menu::create(itemToggleMusic, NULL);
	pMenu->setPosition(visibleSize.width-75,visibleSize.height-75);
	this->addChild(pMenu, 1);
	// --------------------------Lvlup------------------------------- //
	auto bgLvlup = cocos2d::Sprite::create("Resources/ui/popup/ui_ocean_popup_landscape.png");

	auto upHpBtn = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button.png", "Resources/ui/button/ui_blue_button.png");

	bgLvlup->setAnchorPoint(cocos2d::Vec2(0,0));
	bgLvlup->setPosition(visibleSize.width*0.05, visibleSize.height*0.05);
	bgLvlup->setScaleY(0.2);
	bgLvlup->setScaleX(0.3);
	this->addChild(bgLvlup, 0);

    return true;
}