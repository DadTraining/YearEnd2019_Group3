#pragma once
#include "Objects.h"

class Player : public Objects
{
public:
	// An integer to determine if the player release all the keyCode
	int m_numberOfKeyPress = 0;

	Player(cocos2d::Scene* scene);
	~Player();
	void init();
	void update(float deltaTime);
private:
	Scene* scene;
};