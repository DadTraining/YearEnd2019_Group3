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
	int m_width;
	int m_height;
	int damage;
public:
	Slash(int width, int height);
	void init();
	Sprite* getSprite();
	void createPhysics();
	int getDamge();
	void setDamge(int damage);
	~Slash();
};
