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
	float damageOfEm2;
	float hpOfEm2;
	float damageOfEm3;
	float hpOfEm3;
	float num_Villager;
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
	float getDamageOfEm2();
	float getHPOfEm2();
	float getDamageOfEm3();
	float getHPOfEm3();
	Player * getPlayer();

	int getCurrentVillager();
	void setCurrentVillager(int villager);
	void setPlayer(Player* player);
};
