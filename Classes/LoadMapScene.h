#pragma once
#ifndef __LOADMAP_SCENE_H__
#define __LOADMAP_SCENE_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Player.h"
#include "SneakyJoystickSkinnedBase.h"
#include "HUDLayer.h"
#include "MiniBoss01.h"
#include "Villager.h"

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
	//enemy
	vector<MiniBoss01*> Skeletons;
	vector<Villager*> villagers;
	TMXObjectGroup* m_objectGroup;
	// private variable for joystick adding
	HudLayer* HUD;
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
	void addMap();
	// Physics layer
	void createPhysics();
	void addListener();
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	// A method to hide the villager
	void playerGotHit();
	// --------------------------------
	// Extra method to create joystick
	// --------------------------------
	void addHud();
	// --------------------------------
	void update(float dt);
};

#endif // __LOADMAP_SCENE_H__
