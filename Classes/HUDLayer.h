#pragma once
#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
# include "SneakyJoystickSkinnedBase.h"
#include "Player.h"
#include "HealthBarLayer.h"
#include "MiniMapLayer.h"


class HudLayer : public cocos2d::Layer
{
private:
	TMXTiledMap* m_tiledMap;
	cocos2d::Scene* targetScene;
	Player* targetPlayer;
	Label* _hudScore;
	int _numCollected;
	ui::Button *attackBtn, *skillABtn, *skillBBtn;
	// Joystick private variable
	SneakyJoystick *leftJoystick;
	SneakyJoystickSkinnedBase* joystickBase;
	float activeRunRange;
	PhysicsBody* physicsBody;
	Camera* cameraHUD;
	// Init minimap and healthBar
	Layer* healthBar;
	Layer* miniMap;
public:
	HudLayer(cocos2d::Scene* scene, Player* player, TMXTiledMap* map);
	bool init();
	void createHud();
	void CreateAttackBtn(Layer * layer);
	void CreateSkillABtn(Layer * layer);
	void UpdateSkillABtn(float dt);
	void CreateSkillBBtn(Layer * layer);
	void CreateJoystick(Layer * layer);
	void UpdateJoystick(float dt);
	void update(float deltaTime);
	void setMap(TMXTiledMap* map);
	TMXTiledMap* getMap();
	virtual ~HudLayer();
	void createCameraHUD();
	void addVilagerPoint();
	void addMiniMap();
};
#endif	