#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include <string>
#include <sstream>

USING_NS_CC;

using std::string;
using std::stringstream;

class ResourceManager
{
private:
	static ResourceManager* s_instance;
	string m_dataFolderPath;
	Map<string, Animate*> m_player;
	Map<string, Animate*> m_villager;
	Map<string, Animate*> m_boss;
	Map<string, Animate*> m_rangeEnemy;
	Map<string, Animate*> m_meleeEnemy;
	Map<string, Animate*> m_defMiniBoss;
	Map<string, Animate*> m_atkMiniBoss;
	Map<string, Font*> m_Fonts;
public:
	ResourceManager();
	~ResourceManager();
	static ResourceManager* GetInstance();
	void Init(const string path);
	void Load(string fileName);
	Animate* GetPlayerAction(string nameAnimation);
	Animate* GetVillagerAction(string nameAnimation);
	Animate* GetBossAction(string nameAnimation);
	Animate* GetRangeEnemyAction(string nameAnimation);
	Animate* GetMeleeEnemyAction(string nameAnimation);
	Animate* GetDefMiniBossAction(string nameAnimation);
	Animate* GetAtkMiniBossAction(string nameAnimation);
};
