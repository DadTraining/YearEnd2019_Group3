#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__
#pragma once

#include "cocos2d.h"
#include "PauseLayer.h"
#include "LoadMapScene.h"
#include "ResultScene.h"
#include "SimpleAudioEngine.h"

class MainMenu : public cocos2d::Scene
{
private:
	cocos2d::MenuItemImage* itemOn;
	cocos2d::MenuItemImage* itemOff;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void Play();
    CREATE_FUNC(MainMenu);
};

#endif // __MAIN_MENU_H__
