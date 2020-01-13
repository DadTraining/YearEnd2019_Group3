#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#define TIME_ONE_SPIN 0.1f
USING_NS_CC;
using namespace std;
class Portal
{
private:
	Sprite* sprite;
	Animate* animationIdle;
public:
	Portal();
	void init();
	Animate* getIdleAnimate();
	Sprite* getSprite();
	void InitSprite();
	void addPhysics();
	void returntoMainMenu();
	void returntoCastleScene();
	void returntoIceCastleScene();
	void returntoLavaCastleScene();
	void setIndex(int index);
	~Portal();
};
