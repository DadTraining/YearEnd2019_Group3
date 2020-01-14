#pragma once
#ifndef __ICECASTLE_SCENE_H__
#define __ICECASTLE_SCENE_H__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Player.h"
#include "HUDLayer.h"
#include "MiniBoss01.h"
#include "Enemy2.h"
#include "Villager.h"
#include "Portal.h"
#include "Enemy4.h"
#include "BlackHandBoss.h"

using namespace cocos2d;
class IceCastleScene : public cocos2d::Scene
{
private:
	TMXTiledMap* m_tileMap;
	TMXLayer* m_meta;
	TMXObjectGroup* m_objectGroup;
	Sprite* m_player;
	Player* player;
	cocos2d::ParticleSystemQuad* snowBackground;

	//enemy
	vector<MiniBoss01*> Skeletons;
	vector<Villager*> villagers;
	vector<Enemy2*> enemys2;
	vector<Enemy4*> enemys4;
	vector<BlackHandBoss*> bhbs;
	BlackHandBoss* bhb;
	Portal* portal;
	vector<Portal*> portals;
	HudLayer* HUD;


public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void addMap();
	void SpawnPlayer();
	void setViewPointCenter(Vec2 position);
	Vec2 tileCoordForPosition(Vec2 position);
	void createPhysics();
	void addListener();
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void enemyMoveToPlayer();
	void addHud();
	void addSnowParticle();
	void update(float dt);


	CREATE_FUNC(IceCastleScene);
};
#endif // __ICECASTLE_SCENE_H__
