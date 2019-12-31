#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
class Villager
{
private:
	Sprite* sprite;
	Animate* idleAnimate;
	Scene* targetScene;
public:
	Villager(Scene* scene);
	~Villager();
	void init();
	void update(float dt);
	void createIdleAnimation();
	void addPhysic();
	Sprite* getSprite();
	Animate* getIdleAnimate();
	void Die();
	
};