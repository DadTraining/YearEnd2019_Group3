#include "MainMenu.h"
#include "Sound.h"
#include "Update.h"
Scene* MainMenu::createScene()
{
	return MainMenu::create();
}

bool MainMenu::init()
{

	if (!Scene::init())
	{
		return false;
	}
	Sound::GetInstance()->soundMainMenu();
	string font = "Resources/fonts/joystix monospace.ttf";
	float fontSize = 48;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto title = Label::createWithTTF("The Fire Keeper", "Resources/fonts/VCR_OSD_MONO.ttf", 128);
	title->enableOutline(Color4B::BLACK, 5);
	title->setAnchorPoint(Vec2(0.5, 0.5));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.9));

	this->addChild(title);

	auto bg = Sprite::create("Resources/ui/main-menu-bg.jpg");
	bg->setPosition(visibleSize / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);

	auto playLabel = Label::create("Play", font, fontSize);
	play = ui::Button::create("Resources/ui/button/ui_ocean_button.png", "Resources/ui/button/ui_blue_button.png");
	play->setAnchorPoint(Vec2(0, 0));
	play->setScale(0.2f);
	play->addChild(playLabel, 0);
	play->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height * 0.1));
	play->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::MOVED:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(LoadMapScene::createScene());
			Sound::GetInstance()->stopSoundBackGround();
			break;
		case ui::Widget::TouchEventType::CANCELED:
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
	itemToggleMusic->setAnchorPoint(Vec2(1, 1));
	pMenu = Menu::create(itemToggleMusic, NULL);
	pMenu->setPosition(visibleSize.width, visibleSize.height / 2);
	this->addChild(pMenu, 1);
	// ------------------------Flame Animation + Touch --------------------------------- //
	auto flameParticle = CCParticleSystemQuad::create("Resources/ui/animation/fire.plist");

	flameParticle->setPosition(Vec2(visibleSize.width*0.665, visibleSize.height*0.4));
	flameParticle->setAutoRemoveOnFinish(true);
	this->addChild(flameParticle);

	flameBtn = ui::Button::create("Resources/ui/button/ui_green_button.png", "Resources/ui/button/ui_blue_button.png");
	flameBtn->setPosition(flameParticle->getPosition());
	flameBtn->setScaleX(0.05);
	flameBtn->setScaleY(0.2);
	flameBtn->setAnchorPoint(Vec2(0.5, 0));
	flameBtn->setOpacity(0);
	flameBtn->addTouchEventListener([&](Ref* Sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::BEGAN) {
			this->curHP = Update::GetInstance()->getHPOfPlayer();
			this->curNorAtk = Update::GetInstance()->getDamageOfPlayer();
			this->curSlowAtk = Update::GetInstance()->getStunTime();
			this->curSlowAtk = (int)(this->curSlowAtk * 100.0) / 100.0;
			auto strSlow = to_string(curSlowAtk);
			int offset = 1;
			if (strSlow.find_last_not_of('0') == strSlow.find('.'))
			{
				offset = 0;
			}
			strSlow.erase(strSlow.find_last_not_of('0') + offset, std::string::npos);
			this->curUltilAtk = Update::GetInstance()->getConditionUlti();
			auto strUltimate = to_string(curUltilAtk);
			offset = 1;
			if (strUltimate.find_last_not_of('0') == strUltimate.find('.'))
			{
				offset = 0;
			}
			strUltimate.erase(strUltimate.find_last_not_of('0') + offset, std::string::npos);
			this->totalVillager = Update::GetInstance()->getSumVillages();
			updateLayer = LayerColor::create(Color4B(0, 0, 0, 100));
			updateLayer->setTag(01);
			//---------------------------//
			auto bg = Sprite::create("Resources/ui/popup/ui_ocean_popup_landscape.png");
			auto title = Label::createWithTTF("Upgrade", "Resources/fonts/joystix monospace.ttf", 172);
			auto titleBoard = Sprite::create("Resources/ui/button/ui_ocean_button.png");
			auto exit = ui::Button::create("Resources/ui/button/ui_ocean_button_exit.png", "Resources/ui/button/ui_blue_button_exit.png");

			auto bgSize = bg->getContentSize();

			auto hp = Sprite::create("Resources/ui/healthbar/heart.png");

			hp->setContentSize(Size(175, 175));
			hp->setPosition(bgSize.width*0.1, bgSize.height*0.75);

			auto normalAtk = Sprite::create("Resources/Buttons/SkillButtonNormal.png");

			normalAtk->setContentSize(Size(200, 200));
			normalAtk->setPosition(bgSize.width*0.6, bgSize.height*0.75);

			auto slowAtk = Sprite::create("Resources/Buttons/SkillButtonSpear.png");

			slowAtk->setContentSize(Size(200, 200));
			slowAtk->setPosition(bgSize.width*0.1, bgSize.height*0.6);

			auto ultiAtk = Sprite::create("Resources/Buttons/SkillButton Ultimate.png");

			ultiAtk->setContentSize(Size(200, 200));
			ultiAtk->setPosition(bgSize.width*0.6, bgSize.height*0.6);


			hpInfo = Label::create(to_string(curHP), "Resources/fonts/VCR_OSD_MONO.ttf", 96);

			hpInfo->setAnchorPoint(Vec2(0, 0));
			hpInfo->setPosition(250, 50);


			norAtkInfo = Label::create(to_string(curNorAtk), "Resources/fonts/VCR_OSD_MONO.ttf", 96);

			norAtkInfo->setAnchorPoint(Vec2(0, 0));
			norAtkInfo->setPosition(250, 50);

			slowAtkInfo = Label::create(strSlow + "s", "Resources/fonts/VCR_OSD_MONO.ttf", 96);

			slowAtkInfo->setAnchorPoint(Vec2(0, 0));
			slowAtkInfo->setPosition(260, 50);

			ultilAtkInfo = Label::create(strUltimate, "Resources/fonts/VCR_OSD_MONO.ttf", 96);

			ultilAtkInfo->setAnchorPoint(Vec2(0, 0));
			ultilAtkInfo->setPosition(250, 50);

			hpUpdate = ui::Button::create("Resources/ui/button/ui_ocean_button_update.png", "Resources/ui/button/ui_blue_button_update.png");
			if (this->totalVillager >= 100 && hpUpdate->isEnabled()) {
				hpUpdate->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
					case ui::Widget::TouchEventType::BEGAN:
					{
						if (this->totalVillager >= 100) {
							curHP += 10;
							totalVillager -= 100;
							updateHPToFile(curHP);
							updateSumVillagesToFile(totalVillager);
							CCLOG("------------ End");
							this->totalVillagerLabel->setString(to_string(totalVillager));
							this->hpInfo->setString(to_string(curHP));
							if (this->totalVillager < 100) {
								hpUpdate->setEnabled(false);
								hpUpdate->setVisible(false);
							}
							if (this->totalVillager<500) {
								slowAtkUpdate->setEnabled(false);
								slowAtkUpdate->setVisible(false);
							}
							if (this->totalVillager < 200) {
								norAtkUpdate->setEnabled(false);
								norAtkUpdate->setVisible(false);
							}
							if (this->totalVillager < 1000) {
								ultilAtkUpdate->setEnabled(false);
								ultilAtkUpdate->setVisible(false);
							}
						}

						break;
					}
					case ui::Widget::TouchEventType::MOVED:
						break;
					case ui::Widget::TouchEventType::ENDED:
						break;
					default:
						break;
					}
				});
			}
			else {
				if (hpUpdate->isEnabled()) {
					hpUpdate->setEnabled(false);
					hpUpdate->setVisible(false);
				}
			}
			hpUpdate->setAnchorPoint(Vec2(0, 0.25));
			hpUpdate->setPosition(Vec2(400, 0));
			hpUpdate->setScale(0.5);

			norAtkUpdate = ui::Button::create("Resources/ui/button/ui_ocean_button_update.png", "Resources/ui/button/ui_blue_button_update.png");
			if (this->totalVillager >= 200 && norAtkUpdate->isEnabled()) {
				norAtkUpdate->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
					case ui::Widget::TouchEventType::BEGAN:
					{
						if (this->totalVillager >= 200) {
							curNorAtk += 5;
							totalVillager -= 200;
							updateDamageToFile(curNorAtk);
							updateSumVillagesToFile(totalVillager);
							CCLOG("------------ End");
							this->totalVillagerLabel->setString(to_string(totalVillager));
							this->norAtkInfo->setString(to_string(curNorAtk));
							if (this->totalVillager < 100) {
								hpUpdate->setEnabled(false);
								hpUpdate->setVisible(false);
							}
							if (this->totalVillager<500) {
								slowAtkUpdate->setEnabled(false);
								slowAtkUpdate->setVisible(false);
							}
							if (this->totalVillager < 200) {
								norAtkUpdate->setEnabled(false);
								norAtkUpdate->setVisible(false);
							}
							if (this->totalVillager < 1000) {
								ultilAtkUpdate->setEnabled(false);
								ultilAtkUpdate->setVisible(false);
							}
						}

						break;
					}
					case ui::Widget::TouchEventType::MOVED:
						break;
					case ui::Widget::TouchEventType::ENDED:
						break;
					default:
						break;
					}
				});
			}
			else {
				if (norAtkUpdate->isEnabled()) {
					norAtkUpdate->setEnabled(false);
					norAtkUpdate->setVisible(false);
				}
			}
			norAtkUpdate->setAnchorPoint(Vec2(0, 0.25));
			norAtkUpdate->setPosition(Vec2(400, 0));
			norAtkUpdate->setScale(0.5);

			slowAtkUpdate = ui::Button::create("Resources/ui/button/ui_ocean_button_update.png", "Resources/ui/button/ui_blue_button_update.png");
			if (this->totalVillager >= 100 && slowAtkUpdate->isEnabled()) {
				slowAtkUpdate->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
					case ui::Widget::TouchEventType::BEGAN:
					{
						if (this->totalVillager >= 500) {
							curSlowAtk += 0.1f;
							curSlowAtk = (int)(curSlowAtk * 100.0) / 100.0;
							totalVillager -= 500;
							auto str = to_string(curSlowAtk);
							int offset = 1;
							if (str.find_last_not_of('0') == str.find('.'))
							{
								offset = 0;
							}
							str.erase(str.find_last_not_of('0') + offset, std::string::npos);
							updateTimeStunToFile(curSlowAtk);
							updateSumVillagesToFile(totalVillager);
							CCLOG("------------ End");

							this->totalVillagerLabel->setString(to_string(totalVillager));
							this->slowAtkInfo->setString(str);
							if (this->totalVillager < 100) {
								hpUpdate->setEnabled(false);
								hpUpdate->setVisible(false);
							}
							if (this->totalVillager<500) {
								slowAtkUpdate->setEnabled(false);
								slowAtkUpdate->setVisible(false);
							}
							if (this->totalVillager < 200) {
								norAtkUpdate->setEnabled(false);
								norAtkUpdate->setVisible(false);
							}
							if (this->totalVillager < 1000) {
								ultilAtkUpdate->setEnabled(false);
								ultilAtkUpdate->setVisible(false);
							}
						}

						break;
					}
					case ui::Widget::TouchEventType::MOVED:
						break;
					case ui::Widget::TouchEventType::ENDED:
						break;
					default:
						break;
					}
				});
			}
			else {
				if (slowAtkUpdate->isEnabled()) {
					slowAtkUpdate->setEnabled(false);
					slowAtkUpdate->setVisible(false);
				}
			}
			slowAtkUpdate->setAnchorPoint(Vec2(0, 0.25));
			slowAtkUpdate->setPosition(Vec2(400, 0));
			slowAtkUpdate->setScale(0.5);

			ultilAtkUpdate = ui::Button::create("Resources/ui/button/ui_ocean_button_update.png", "Resources/ui/button/ui_blue_button_update.png");
			if (this->totalVillager >= 500 && ultilAtkUpdate->isEnabled()) {
				ultilAtkUpdate->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
					case ui::Widget::TouchEventType::BEGAN:
					{
						if (this->totalVillager >= 1000) {
							curUltilAtk += 0.125;
							totalVillager -= 1000;
							auto str = to_string(curUltilAtk);
							int offset = 1;
							if (str.find_last_not_of('0') == str.find('.'))
							{
								offset = 0;
							}
							str.erase(str.find_last_not_of('0') + offset, std::string::npos);
							updateUltiToFile(curUltilAtk);
							updateSumVillagesToFile(totalVillager);
							CCLOG("------------ End");

							this->totalVillagerLabel->setString(to_string(totalVillager));
							this->ultilAtkInfo->setString(str);
							if (this->totalVillager < 100) {
								hpUpdate->setEnabled(false);
								hpUpdate->setVisible(false);
							}
							if (this->totalVillager<500) {
								slowAtkUpdate->setEnabled(false);
								slowAtkUpdate->setVisible(false);
							}
							if (this->totalVillager < 200) {
								norAtkUpdate->setEnabled(false);
								norAtkUpdate->setVisible(false);
							}
							if (this->totalVillager < 1000) {
								ultilAtkUpdate->setEnabled(false);
								ultilAtkUpdate->setVisible(false);
							}
						}

						break;
					}
					case ui::Widget::TouchEventType::MOVED:
						break;
					case ui::Widget::TouchEventType::ENDED:
						break;
					default:
						break;
					}
				});
			}
			else {
				if (ultilAtkUpdate->isEnabled()) {
					ultilAtkUpdate->setEnabled(false);
					ultilAtkUpdate->setVisible(false);
				}
			}
			ultilAtkUpdate->setAnchorPoint(Vec2(0, 0.25));
			ultilAtkUpdate->setPosition(Vec2(400, 0));
			ultilAtkUpdate->setScale(0.5);

			hpInfo->addChild(hpUpdate);
			norAtkInfo->addChild(norAtkUpdate);
			slowAtkInfo->addChild(slowAtkUpdate);
			ultilAtkInfo->addChild(ultilAtkUpdate);

			hp->addChild(hpInfo);
			normalAtk->addChild(norAtkInfo);
			slowAtk->addChild(slowAtkInfo);
			ultiAtk->addChild(ultilAtkInfo);

			totalVillagerLabel = Label::create(to_string(totalVillager), "Resources/fonts/VCR_OSD_MONO.ttf", 196);
			auto totalVillagerBg = Sprite::create("Resources/ui/button/ui_ocean_button.png");
			totalVillagerBg->setScale(0.5);
			totalVillagerLabel->setPosition(totalVillagerBg->getContentSize() / 2);
			totalVillagerBg->setPosition(bgSize.width / 2, bgSize.height*0.3);
			totalVillagerBg->addChild(totalVillagerLabel);

			bg->setAnchorPoint(Vec2(0.5, 0.5));
			bg->setPosition(updateLayer->getContentSize() / 2);
			bg->setScale(0.4);

			title->setAnchorPoint(Vec2(0.5, 0.5));
			title->setPosition(titleBoard->getContentSize() / 2);

			titleBoard->setScale(0.5);
			titleBoard->setPosition(bg->getContentSize().width / 2, bg->getContentSize().height);
			titleBoard->addChild(title);

			exit->setAnchorPoint(Vec2(0.5, 0.4));
			exit->setPosition(Vec2(bgSize.width / 2, 0));
			exit->setScale(0.8);

			play->setVisible(false);
			pMenu->setVisible(false);
			flameBtn->setVisible(false);

			bg->addChild(hp);
			bg->addChild(normalAtk);
			bg->addChild(slowAtk);
			bg->addChild(ultiAtk);
			bg->addChild(totalVillagerBg);

			bg->addChild(titleBoard);
			bg->addChild(exit);
			updateLayer->addChild(bg);
			this->addChild(updateLayer);

			exit->addTouchEventListener([&](Ref* Sender, ui::Widget::TouchEventType type) {
				if (type == ui::Widget::TouchEventType::BEGAN)
				{
					play->setVisible(true);
					pMenu->setVisible(true);
					flameBtn->setVisible(true);
					this->removeChildByTag(01);
				}
			});
		};
	});
	this->addChild(flameBtn);

	scheduleUpdate();
	return true;
}

void MainMenu::updateHPToFile(float hp)
{
	Update::GetInstance()->setHpOfPlayer(hp);
	auto hpOfPlayer = to_string(Update::GetInstance()->getHPOfPlayer());
	auto damage = to_string(Update::GetInstance()->getDamageOfPlayer());
	auto sumVillages = to_string(Update::GetInstance()->getSumVillages());
	auto conditionUlti = to_string(Update::GetInstance()->getConditionUlti());
	auto stunTime = to_string(Update::GetInstance()->getStunTime());
	FileUtils::getInstance()->writeStringToFile(hpOfPlayer + "\r\n" + damage + "\r\n" + sumVillages + "\r\n" + conditionUlti + "\r\n" + stunTime, Update::GetInstance()->getPath());
}

void MainMenu::updateDamageToFile(float damage)
{
	Update::GetInstance()->setDamageOfPlayer(damage);
	auto hpOfPlayer = to_string(Update::GetInstance()->getHPOfPlayer());
	auto damageOfPlayer = to_string(Update::GetInstance()->getDamageOfPlayer());
	auto sumVillages = to_string(Update::GetInstance()->getSumVillages());
	auto conditionUlti = to_string(Update::GetInstance()->getConditionUlti());
	auto stunTime = to_string(Update::GetInstance()->getStunTime());
	FileUtils::getInstance()->writeStringToFile(hpOfPlayer + "\r\n" + damageOfPlayer + "\r\n" + sumVillages + "\r\n" + conditionUlti + "\r\n" + stunTime, Update::GetInstance()->getPath());
}

void MainMenu::updateTimeStunToFile(float timeStun)
{
	Update::GetInstance()->setTimeStun(timeStun);
	auto hpOfPlayer = to_string(Update::GetInstance()->getHPOfPlayer());
	auto damageOfPlayer = to_string(Update::GetInstance()->getDamageOfPlayer());
	auto sumVillages = to_string(Update::GetInstance()->getSumVillages());
	auto conditionUlti = to_string(Update::GetInstance()->getConditionUlti());
	auto stunTime = to_string(Update::GetInstance()->getStunTime());
	FileUtils::getInstance()->writeStringToFile(hpOfPlayer + "\r\n" + damageOfPlayer + "\r\n" + sumVillages + "\r\n" + conditionUlti + "\r\n" + stunTime, Update::GetInstance()->getPath());
}

void MainMenu::updateUltiToFile(float ulti)
{
	Update::GetInstance()->setUltiDame(ulti);
	auto hpOfPlayer = to_string(Update::GetInstance()->getHPOfPlayer());
	auto damageOfPlayer = to_string(Update::GetInstance()->getDamageOfPlayer());
	auto sumVillages = to_string(Update::GetInstance()->getSumVillages());
	auto conditionUlti = to_string(Update::GetInstance()->getConditionUlti());
	auto stunTime = to_string(Update::GetInstance()->getStunTime());
	FileUtils::getInstance()->writeStringToFile(hpOfPlayer + "\r\n" + damageOfPlayer + "\r\n" + sumVillages + "\r\n" + conditionUlti + "\r\n" + stunTime, Update::GetInstance()->getPath());
}

void MainMenu::updateSumVillagesToFile(int villages)
{
	Update::GetInstance()->setSumVillages(villages);
	auto hpOfPlayer = to_string(Update::GetInstance()->getHPOfPlayer());
	auto damageOfPlayer = to_string(Update::GetInstance()->getDamageOfPlayer());
	auto sumVillages = to_string(Update::GetInstance()->getSumVillages());
	auto conditionUlti = to_string(Update::GetInstance()->getConditionUlti());
	auto stunTime = to_string(Update::GetInstance()->getStunTime());
	FileUtils::getInstance()->writeStringToFile(hpOfPlayer + "\r\n" + damageOfPlayer + "\r\n" + sumVillages + "\r\n" + conditionUlti + "\r\n" + stunTime, Update::GetInstance()->getPath());

}

void MainMenu::handlerBtnHpUpdate()
{

}

void MainMenu::handlerBtnNorAtkUpdate()
{
}

void MainMenu::handlerBtnSlowAtkUpdate()
{
}

void MainMenu::handlerBtnUltilAtkUpdate()
{
}

void MainMenu::update(float dt)
{
}