#include "OptionsLayer.h"

cocos2d::Layer * OptionsLayer::createLayer()
{
	return OptionsLayer::create();
}

bool OptionsLayer::init()
{
	if (!LayerColor::initWithColor(cocos2d::Color4B(0, 0, 0, 150))) {
		return false;
	}

	auto bg = cocos2d::Sprite::create("Resources/ui/popup/ui_ocean_popup_landscape.png");
	auto title = cocos2d::Label::createWithTTF("Options", "Resources/fonts/joystix monospace.ttf", 38);
	auto titleLayer = cocos2d::Sprite::create("Resources/ui/button/ui_ocean_button.png");
	auto exit = cocos2d::ui::Button::create("Resources/ui/button/ui_ocean_button_exit.png", "Resources/ui/button/ui_blue_button_exit.png");


	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	this->setContentSize(winSize);

	bg->setPosition(winSize / 2);
	bg->setContentSize(winSize*0.5f);
	auto bgSize = bg->getContentSize();

	titleLayer->addChild(title);
	titleLayer->setContentSize(cocos2d::Size(bgSize.width / 2, bgSize.height / 4));
	titleLayer->setPosition(cocos2d::Vec2(bgSize.width / 2, bgSize.height));
	title->setPosition(titleLayer->getContentSize() / 2);

	auto sound = cocos2d::Label::createWithTTF("Sound", "Resources/fonts/VCR_OSD_MONO.ttf", 48);
	sound->setAnchorPoint(cocos2d::Vec2(0, 0));
	sound->setPosition(bgSize.width*0.2, bgSize.height / 2);

	auto sliderSound = cocos2d::ui::Slider::create();
	sliderSound->loadBarTexture("Resources/ui/sliderbar/slider_bar_bg.png");
	sliderSound->loadSlidBallTextures("Resources/ui/sliderbar/slider_ball_bg.png", "Resources/ui/sliderbar/slider_ball_pressed.png", "ui/sliderbar/slider_ball_bg.png");
	sliderSound->loadProgressBarTexture("Resources/ui/sliderbar/slider_bar_pressed.png");
	sliderSound->setPercent(this->soundPercent);
	sliderSound->setScale(1.5f);
	sliderSound->addClickEventListener([=](Ref* event) {
		//Options sound
		this->setSoundPercent(sliderSound->getPercent());
		log(this->getSoundPercent());
	});
	sliderSound->setAnchorPoint(cocos2d::Vec2(0, 0));
	sliderSound->setPosition(cocos2d::Vec2(sound->getPosition().x + sound->getContentSize().width + 20, sound->getPosition().y));


	auto sfx = cocos2d::Label::createWithTTF("SFX", "Resources/fonts/VCR_OSD_MONO.ttf", 38);
	sfx->setAnchorPoint(cocos2d::Vec2(0, 0));
	sfx->setPosition(sound->getPositionX(), sound->getPositionY() - 50);


	auto sliderSfx = cocos2d::ui::Slider::create();
	sliderSfx->loadBarTexture("Resources/ui/sliderbar/slider_bar_bg.png");
	sliderSfx->loadSlidBallTextures("Resources/ui/sliderbar/slider_ball_bg.png", "Resources/ui/sliderbar/slider_ball_pressed.png", "Resources/ui/sliderbar/slider_ball_bg.png");
	sliderSfx->loadProgressBarTexture("Resources/ui/sliderbar/slider_bar_pressed.png");
	sliderSfx->setPercent(this->getSfxPercent());
	sliderSfx->setScale(1.5f);
	sliderSfx->addClickEventListener([=](Ref* event) {
		//Options sfx
		this->setSfxPercent(sliderSfx->getPercent());
		log(this->getSfxPercent());
	});
	sliderSfx->setAnchorPoint(cocos2d::Vec2(0, 0));
	sliderSfx->setPosition(cocos2d::Vec2(sliderSound->getPosition().x, sfx->getPosition().y));

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
	bg->addChild(sound, 0);
	bg->addChild(sliderSound, 0);
	bg->addChild(sfx, 0);
	bg->addChild(sliderSfx, 0);
	bg->addChild(exit, 0);
	this->addChild(bg, 0);

	return true;
}

void OptionsLayer::setSoundPercent(int percent)
{
	this->soundPercent = percent;
}

int OptionsLayer::getSoundPercent()
{
	return this->soundPercent;
}

void OptionsLayer::setSfxPercent(int percent)
{
	this->sfxPercent = percent;
}

int OptionsLayer::getSfxPercent()
{
	return this->sfxPercent;
}

