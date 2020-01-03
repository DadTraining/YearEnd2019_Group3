#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
class Objects
{
public:
	Objects();
	~Objects();
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;

	virtual void setSprite(Sprite* sprite) = 0;
	virtual void setAttackAnimate(Animate* attackAnimate) = 0;
	virtual void setIdleAnimate(Animate* aidleAnimate) = 0;
	virtual void setHitAnimate(Animate* hitAnimate) = 0;
	virtual void setRunAnimate(Animate* runAnimate) = 0;
	virtual void setDeadAnimate(Animate* deadAnimate) = 0;
	virtual void setHP(float hP) = 0;
	virtual void setDamage(float damage) = 0;

	virtual Sprite* getSprite() = 0;
	virtual Animate* getAttackAnimate() = 0;
	virtual Animate* getIdleAnimate() = 0;
	virtual Animate* getHitAnimate() = 0;
	virtual Animate* getRunAnimate() = 0;
	virtual Animate* getDeadAnimate() = 0;
	virtual void Die() = 0;
	virtual float getHP() = 0;
	virtual float getDamage() = 0;
	
};
