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

void Sound::soundBossSkillFire()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Boss/fireSkill.wav", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundBossSkillHeal()
{
	if (this->isMute)
		{
			return;
		}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/Boss/healSkill.wav", false, 1.0f, 1.0f, 1.0f);
}

void Sound::soundKnightBossAbsorb()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Resources/sounds/KnightBoss/absorb.wav", false, 1.0f, 1.0f, 1.0f);
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

void Sound::soundBackGroundCastle()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Resources/sounds/Background/Background_castle.mp3", true);
}

void Sound::soundBackGroundIceCastle()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Resources/sounds/Background/IceCastleScene.mp3", true);
}

void Sound::soundBackGroundLavaCastle()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Resources/sounds/Background/LavaCastleScene.mp3", true);
}

void Sound::soundMainMenu()
{
	if (this->isMute)
	{
		return;
	}
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Resources/sounds/Background/MainMenuTheme.mp3", true);
}


void Sound::stopSoundBackGround()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (this->isMute)
	{
		audio->pauseBackgroundMusic();
	}
	else
	{
		audio->resumeBackgroundMusic();
	}
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
	audio->preloadEffect("Resources/sounds/Boss/fireSkill.wav");
	audio->preloadEffect("Resources/sounds/Boss/healSkill.wav");
	audio->preloadEffect("Resources/sounds/KnightBoss/absorb.wav");

	audio->preloadBackgroundMusic("Resources/sounds/Background/176_Barren_Wastes.mp3");
	audio->preloadBackgroundMusic("Resources/sounds/Background/Background_castle.mp3");
	audio->preloadBackgroundMusic("Resources/sounds/Background/MainMenuTheme.mp3");
	audio->preloadBackgroundMusic("Resources/sounds/Background/IceCastleScene.mp3");
	audio->preloadBackgroundMusic("Resources/sounds/Background/LavaCastleScene.mp3");

	CCLOG("------- Done Sound");

}


