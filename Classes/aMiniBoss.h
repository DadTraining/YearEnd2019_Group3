#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Objects.h"

class aMiniBoss: public Objects
{
public:
	aMiniBoss(cocos2d::Scene* scene);
	~aMiniBoss();
	void init();
	void update(float deltaTime);
};

