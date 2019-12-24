#pragma once
#ifndef __LOADMAP_SCENE_H__
#define __LOADMAP_SCENE_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Player.h"
#include "SneakyJoystickSkinnedBase.h"
#include "HUDLayer.h"

using namespace cocos2d;
class LoadMapScene : public cocos2d::Scene
{
private:
	// Map private object
	TMXTiledMap* m_tileMap;
	TMXLayer* m_meta;
	TMXLayer* m_villagerLayer;
	int _numCollected = 0;
	bool stuck = false;
	Sprite* m_player;
	Player* player;
	// private variable for joystick adding
	Layer* _hudLayer;
	HudLayer* HUD;
	PhysicsBody* physicsBody;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(LoadMapScene);

	// Extra methods for adding the map
	// --------------------------------
	void SpawnPlayer();
	void setViewPointCenter(Vec2 position);
	Vec2 tileCoordForPosition(Vec2 position);
	void isCollision(Vec2 position);
	void isCollectable(Vec2 position);

	// --------------------------------
	// Extra method to create joystick
	// --------------------------------
	void addHud();
	// --------------------------------
	void update(float dt);
};

#endif // __LOADMAP_SCENE_H__
