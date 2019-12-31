#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Slash
{
private:
	Sprite* m_Sprite;
public:
	Slash();
	void init();
	Sprite* getSprite();
	~Slash();
};
