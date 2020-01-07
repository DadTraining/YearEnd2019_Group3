#pragma once
#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
# include "SneakyJoystickSkinnedBase.h"
#include "Player.h"
#include "HealthBarLayer.h"
#include "OptionsLayer.h"
class HudLayer : public cocos2d::Layer
{
private:
	TMXTiledMap* m_tiledMap;
	cocos2d::Scene* targetScene;
	Player* targetPlayer;
	Label* _hudScore;
	int _numCollected;
	ui::Button* attackBtn;
	// Joystick private variable
	SneakyJoystick *leftJoystick;
	SneakyJoystickSkinnedBase* joystickBase;
	float activeRunRange;
	PhysicsBody* physicsBody;
	Camera* cameraHUD;

	Layer* healthBar;
public:
	HudLayer(cocos2d::Scene* scene, Player* player, TMXTiledMap* map);
	bool init();
	void createHud();
	void CreateAttackBtn(Layer * layer);
	void CreateJoystick(Layer * layer);
	void UpdateJoystick(float dt);
	void update(float deltaTime);
	void setMap(TMXTiledMap* map);
	TMXTiledMap* getMap();
	virtual ~HudLayer();
	void createCameraHUD();
	void addVilagerPoint();
	void addPauseButton();
};
#endif	