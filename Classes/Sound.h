#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Update.h"
USING_NS_CC;

class Sound
{
private:
	static Sound* s_instance;
	bool isMute;
public:
	Sound();
	~Sound();
	static Sound* GetInstance();
	void preLoadSound();
	//PlayerSound
	void soundPlayerAttack1();
	void soundPlayerDie();
	void soundPlayerHit();
	void soundCollect();
	void soundBackGroundDesert();
	void Init();
	// SkeletonSound
	void soundSkeletonHit();
	void soundSkeletonDie();
	// getMute
	void setIsMute(bool mute);
	bool getIsMute();
};