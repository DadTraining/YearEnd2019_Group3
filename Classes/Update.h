#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class Update
{
private:
	static Update* s_instance;
	float damageOfPlayer;
	float hpOfPlayer;
	float damageOfMB1;
	float hpOfMB1;
public:
	Update();
	~Update();
	static Update* GetInstance();
	void Init();
	float getDamageOfPlayer();
	float getHPOfPlayer();
	float getDamageOfMB1();
	float getHPOfMB1();
};
