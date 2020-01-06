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

void Sound::Init()
{
	this->preLoadSound();
	this->isMute = false;
}

void Sound::soundSkeletonHit()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Skeleton/attacked.wav", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundSkeletonDie()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Skeleton/die.wav", false, 1.0f, 1.0f, 1.0f);
}

void Sound::setIsMute(bool mute)
{
	this->isMute = mute;
}

bool Sound::getIsMute()
{
	return this->isMute;
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
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Player/Sword_Swipe.mp3", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundPlayerDie()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Player/die.mp3", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundPlayerHit()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Player/hit.mp3", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundCollect()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Player/collect.wav", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundBackGroundDesert()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Resources/sounds/Background/176_Barren_Wastes.mp3", true);
}

void Sound::preLoadSound()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadEffect("Resources/sounds/Player/Sword_Swipe.mp3");
	audio->preloadEffect("Resources/sounds/Player/hit.mp3");
	audio->preloadEffect("Resources/sounds/Player/die.mp3");
	audio->preloadEffect("Resources/sounds/Player/collect.wav");
	// Preload Skeleton sound
	audio->preloadEffect("Resources/sounds/Skeleton/attacked.wav");
	audio->preloadEffect("Resources/sounds/Skeleton/die.wav");

	audio->preloadBackgroundMusic("Resources/sounds/Background/176_Barren_Wastes.mp3");
}


