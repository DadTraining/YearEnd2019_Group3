#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Objects
{
private:
	Sprite* sprite;
	Animate *animateAttack, *animateIdle, *animateMove, *animateDead, *animateRun;
public:
	Objects();
	~Objects();
	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	void setAnimateAttack(Animate* animateAttack);
	Animate* getAnimateAttack();
	void setAnimateIdle(Animate* animateIdle);
	Animate* getAnimateIdle();
	void setAnimateMove(Animate* animateMove);
	Animate* getAnimateMove();
	void setAnimateDead(Animate* animateDead);
	Animate* getAnimateDead();
	void setAnimateRun(Animate* animateRun);
	Animate* getAnimateRun();
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
};
