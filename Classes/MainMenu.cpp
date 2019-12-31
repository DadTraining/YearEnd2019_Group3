#include "MainMenu.h"

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
	string font = "Resources/fonts/joystix monospace.ttf";
	float fontSize = 48;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto bg = cocos2d::Sprite::create("Resources/ui/main-menu-bg.jpg");

	auto playLabel = cocos2d::Label::create("Play", font, fontSize);
	auto settingLabel = cocos2d::Label::create("Options", font, fontSize);
	auto exitLabel = cocos2d::Label::create("Exit", font, fontSize);

	auto play = cocos2d::MenuItemImage::create("Resources/ui/button/ui_ocean_button.png", "Resources/ui/button/ui_blue_button.png", CC_CALLBACK_0(MainMenu::Play, this));
	auto setting = cocos2d::MenuItemImage::create("Resources/ui/button/ui_ocean_button.png", "Resources/ui/button/ui_blue_button.png",CC_CALLBACK_0(MainMenu::Options, this));
	auto exit = cocos2d::MenuItemImage::create("Resources/ui/button/ui_ocean_button.png", "Resources/ui/button/ui_blue_button.png", CC_CALLBACK_0(MainMenu::Exit, this));
	
	bg->setPosition(visibleSize / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);

	play->setAnchorPoint(Vec2(0, 0));
	setting->setAnchorPoint(Vec2(0, 0));
	exit->setAnchorPoint(Vec2(0, 0));

	play->setScale(0.3f);
	setting->setScale(0.3f);
	exit->setScale(0.3f);

	play->addChild(playLabel, 0);
	setting->addChild(settingLabel, 0);
	exit->addChild(exitLabel, 0);

	playLabel->setPosition(play->getContentSize() / 2);
	playLabel->setScale(5);

	settingLabel->setPosition(setting->getContentSize() / 2);
	settingLabel->setScale(5);

	exitLabel->setPosition(exit->getContentSize() / 2);
	exitLabel->setScale(5);

	auto mainMenu = Menu::create(play,setting,exit,nullptr);

	mainMenu->setPosition(visibleSize.width*0.02, visibleSize.height*0.4);
	mainMenu->alignItemsVertically();

	bg->addChild(mainMenu, 0);
	this->addChild(bg, -1);
	// --------------------------------------------------------- //
    return true;
}

void MainMenu::Play()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LoadMapScene::createScene()));
}

void MainMenu::Options()
{
	auto options = OptionsLayer::createLayer();
	options->setAnchorPoint(options->getContentSize()/2);
	this->addChild(options, 1);
}

void MainMenu::Exit()
{
	Director::getInstance()->end();
}
