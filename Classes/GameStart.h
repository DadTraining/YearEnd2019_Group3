

#ifndef __GAME_START_H__
#define __GAME_START_H__

#include "Player.h"
#include "cocos2d.h"
#include "SneakyJoystickSkinnedBase.h"

class GameStart : public cocos2d::Scene
{
private: 
	SneakyJoystick *leftJoystick;
	SneakyJoystickSkinnedBase* joystickBase;
	float activeRunRange;
	Player* player;
	Sprite* spPlayer;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void CreateJoystick(Scene * scene);
	void UpdateJoystick(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(GameStart);
};

#endif // __GAME_START_H__
