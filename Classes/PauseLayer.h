#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"
#include "MainMenu.h"
#include "Sound.h"

class PauseLayer : public cocos2d::LayerColor
{
private:
	int soundPercent = 0;
	int sfxPercent = 0;
public:
	static cocos2d::Layer* createLayer();
	virtual bool init();
	CREATE_FUNC(PauseLayer);
};

#endif // __PAUSE_LAYER_H__
