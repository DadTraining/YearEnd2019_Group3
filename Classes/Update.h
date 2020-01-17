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
	float damageOfEm4;
	float hpOfEm4;
	float damageOfBoss;
	float hpOfBoss;

	float damageOfBlueBoss;
	float hpOfBlueBoss;
	Player* player;
	string path;
	vector<float> allData;
	int sumVillages;
	float stunTime;
	float conditionUlti;
	//skill
	int stateUlti, stateSlow;
	string pathStateSkill;
	vector<int> states;

public:
	Update();
	~Update();
	static Update* GetInstance();
	void Init();
	void readFile(string path);
	float getDamageOfPlayer();
	float getHPOfPlayer();
	float getDamageOfMB1();
	float getHPOfMB1();
	float getDamageOfEm2();
	float getHPOfEm2();
	float getDamageOfEm3();
	float getHPOfEm3();
	float getDamageOfEm4();
	float getHPOfEm4();
	float getDamageOfBoss();
	float getHPOfBoss();

	float getDamageOfBlueBoss();
	float getHPOfBlueBoss();
	Player * getPlayer();
	void setPlayer(Player* player);
	string getPath();
	int getSumVillages();
	float getStunTime();
	float getConditionUlti();
	void setSumVillages(int sumVillages);
	void setHpOfPlayer(float hp);
	void setDamageOfPlayer(float damage);
	void setTimeStun(float time);
	void setUltiDame(float i);
	//skill
	string getPathStateSkill();
	void readFileStateSkill(string path);
	int getStateUlti();
	int getStateSlow();
	void setStateUlti(int i);
	void setStatekSlow(int i);
};
