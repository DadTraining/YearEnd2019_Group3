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

	auto title = cocos2d::Label::createWithTTF("The Fire Keeper", "Resources/fonts/VCR_OSD_MONO.ttf", 128);
	title->enableOutline(cocos2d::Color4B::BLACK, 5);
	title->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
	title->setPosition(cocos2d::Vec2(visibleSize.width/2,visibleSize.height*0.9));

	this->addChild(title);

	auto bg = cocos2d::Sprite::create("Resources/ui/main-menu-bg.jpg");
	bg->setPosition(visibleSize / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);

	auto playLabel = cocos2d::Label::create("Play", font, fontSize);
	auto play = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button.png", "Resources/ui/button/ui_blue_button.png");
	play->setAnchorPoint(Vec2(0, 0));
	play->setScale(0.2f);
	play->addChild(playLabel, 0);
	play->setPosition(cocos2d::Vec2(visibleSize.width*0.6, visibleSize.height * 0.1));
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

	this->addChild(play, 0);
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
	itemToggleMusic->setAnchorPoint(cocos2d::Vec2(1,1));
	Menu* pMenu = Menu::create(itemToggleMusic, NULL);
	pMenu->setPosition(visibleSize.width,visibleSize.height/2);
	this->addChild(pMenu, 1);

    return true;
}