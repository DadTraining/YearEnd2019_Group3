#ifndef __OPTIONS_LAYER_H__
#define __OPTIONS_LAYER__
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class OptionsLayer : public cocos2d::LayerColor
{
private:
	int soundPercent = 0;
	int sfxPercent = 0;
public:
	static cocos2d::Layer* createLayer();
	virtual bool init();
	void setSoundPercent(int percent);
	int getSoundPercent();
	void setSfxPercent(int percent);
	int getSfxPercent();
	CREATE_FUNC(OptionsLayer);
};

#endif // __OPTIONS_LAYER__
