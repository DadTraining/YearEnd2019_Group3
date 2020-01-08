#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MainMenu.h"

class ResultScene:public cocos2d::Scene 
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ResultScene);
	

private:
	bool isAlive;
	int numVillager = 0;
};
