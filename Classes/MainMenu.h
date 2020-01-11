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

public:
	ui::Button* play;
	Menu* pMenu;
	ui::Button* flameBtn;
	LayerColor* updateLayer;
	int curHP = 100;
	int curSlowAtk = 2;
	int curNorAtk = 100;
	int curUltilAtk = 200;
	int totalVillager = 1000;
    static cocos2d::Scene* createScene();
    virtual bool init();
	void Play();
    CREATE_FUNC(MainMenu);
};

#endif // __MAIN_MENU_H__
