#pragma once
#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
# include "SneakyJoystickSkinnedBase.h"
#include "Player.h"
#include "HealthBarLayer.h"
#include "MiniMapLayer.h"
#include "PauseLayer.h"

class HudLayer : public cocos2d::Layer
{
private:
	cocos2d::Scene* targetScene;
	Player* targetPlayer;
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
	HudLayer(cocos2d::Scene* scene, Player* player);
	bool init();
	void createHud();
	void CreateAttackNormal(Layer * layer);
	void CreateSkillUltimate(Layer * layer);
	void UpdateSkillUltimate(float dt);
	void CreateSkillSpear(Layer * layer);
	void CreateJoystick(Layer * layer);
	void UpdateJoystick(float dt);
	void update(float deltaTime);
	virtual ~HudLayer();
	void createCameraHUD();
	void addMiniMap();
	void addPauseButton();
};
#endif	