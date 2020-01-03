#ifndef __HEALTHBAR_LAYER_H__
#define __HEALTHBAR_LAYER_H__
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Model.h"
class HealthBarLayer : public cocos2d::LayerColor
{
private:
	float healthPercent;
	float maxHP;
	cocos2d::ui::LoadingBar* sliderhealth;
	int numVillager = 0;
	cocos2d::Label* textVillager;
public:
	static cocos2d::Layer* createLayer();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(HealthBarLayer);
};

#endif // __HEALTHBAR_LAYER_H__
