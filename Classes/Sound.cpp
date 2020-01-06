#include "Sound.h"
#include "SimpleAudioEngine.h"

Sound* Sound::s_instance;
Sound::Sound()
{
	Init();
}

Sound::~Sound()
{
}

Sound * Sound::GetInstance()
{
	if (!s_instance)
	{
		s_instance = new Sound();
	}
	return s_instance;
}

void Sound::soundPlayerAttack1()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Player/Sword_Swipe.mp3", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundPlayerDie()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Player/die.mp3", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundPlayerHit()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Player/hit.mp3", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundCollect()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Player/collect.wav", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundBackGroundDesert()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Resources/sounds/Background/176_Barren_Wastes.mp3", true);
}

void Sound::Init()
{
	this->preLoadSound();
}

void Sound::preLoadSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadEffect("Resources/sounds/Player/Sword_Swipe.mp3");
	audio->preloadEffect("Resources/sounds/Player/hit.mp3");
	audio->preloadEffect("Resources/sounds/Player/die.mp3");
	audio->preloadEffect("Resources/sounds/Player/collect.wav");
	audio->preloadBackgroundMusic("Resources/sounds/Background/176_Barren_Wastes.mp3");
}


