#pragma once
#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__
#define TAG_ANIMATE_RUN 111
#define TAG_ANIMATE_IDLE1 121
#define TAG_ANIMATE_IDLE2 122
#define TAG_ANIMATE_ATTACK 131
#define SPEED 5.0f
#define m_SCALE 4.0f
#include "cocos2d.h"
#include "ui/CocosGUI.h"
# include "SneakyJoystickSkinnedBase.h"
#include "Player.h"

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
};
#endif	