#pragma once
#include "Objects.h"

class Player : public Objects
{
public:
	Player(cocos2d::Scene* scene);
	~Player();
	void init();
	void update(float deltaTime);
private:
	Scene* scene;
};