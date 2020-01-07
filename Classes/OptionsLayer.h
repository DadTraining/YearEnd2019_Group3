#ifndef __OPTIONS_LAYER_H__
#define __OPTIONS_LAYER__
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class OptionsLayer : public cocos2d::LayerColor
{
private:

public:
	static cocos2d::Layer* createLayer();
	virtual bool init();
	void Pause();
	CREATE_FUNC(OptionsLayer);
};

#endif // __OPTIONS_LAYER__
