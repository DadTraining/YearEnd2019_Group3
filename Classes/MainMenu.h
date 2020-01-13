#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__
#pragma once

#include "cocos2d.h"
#include "LoadMapScene.h"
#include "ResultScene.h"
#include "SimpleAudioEngine.h"

class MainMenu : public cocos2d::Scene
{
private:
	cocos2d::MenuItemImage* itemOn;
	cocos2d::MenuItemImage* itemOff;
	ui::Button* play;
	Menu* pMenu;
	ui::Button* flameBtn;
	LayerColor* updateLayer;
	int curHP;
	float curSlowAtk;
	int curNorAtk;
	float curUltilAtk;
	int totalVillager;
	ui::Button*hpUpdate,*norAtkUpdate,*slowAtkUpdate,*ultilAtkUpdate;
	Label *totalVillagerLabel, *hpInfo, *norAtkInfo, *slowAtkInfo, *ultilAtkInfo;

public:    static cocos2d::Scene* createScene();
    virtual bool init();
	void Play();
    CREATE_FUNC(MainMenu);
	void updateHPToFile(float hp);
	void updateDamageToFile(float damage);
	void updateTimeStunToFile(float timeStun);
	void updateUltiToFile(float ulti);
	void updateSumVillagesToFile(int villages);
	void handlerBtnHpUpdate();
	void handlerBtnNorAtkUpdate();
	void handlerBtnSlowAtkUpdate();
	void handlerBtnUltilAtkUpdate();
	void update(float dt);
};

#endif // __MAIN_MENU_H__
