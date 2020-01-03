#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
USING_NS_CC;

class Update
{
private:
	static Update* s_instance;
	float damageOfPlayer;
	float hpOfPlayer;
	float damageOfMB1;
	float hpOfMB1;
	Player* player;
public:
	Update();
	~Update();
	static Update* GetInstance();
	void Init();
	float getDamageOfPlayer();
	float getHPOfPlayer();
	float getDamageOfMB1();
	float getHPOfMB1();
	Player * getPlayer();
	void setPlayer(Player* player);
};
