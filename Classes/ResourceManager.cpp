#include "ResourceManager.h"

ResourceManager* ResourceManager::s_instance;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager * ResourceManager::GetInstance()
{
	if (!s_instance) {
		s_instance = new ResourceManager();
	}
	return s_instance;
}

void ResourceManager::Init(const string path)
{
	m_dataFolderPath = path;
	Load(m_dataFolderPath + "Data.bin");
}

void ResourceManager::Load(string fileName)
{
	auto file = FileUtils::getInstance();
	string content, token, png, plist, nameAnimate, pngAnimation;
	int size, sizeS, numAnimation;
	Vector<SpriteFrame*> anims;
	if (file->isFileExist("Data.bin")) {
		content = FileUtils::getInstance()->getStringFromFile(fileName);
	}
	std::stringstream ss(content);

	while (ss >> token)
	{
		if (token == "#ANIMATION")
		{
			ss >> size;
			for (int i = 0; i < size; i++)
			{
				ss >> token;
				ss >> sizeS;
				for (int j = 0; j < sizeS; j++)
				{
					ss >> nameAnimate;
					ss >> numAnimation;
					ss >> png;
					ss >> plist;

					auto spriteCache = SpriteFrameCache::getInstance();
					spriteCache->addSpriteFramesWithFile(plist, png);
					if (token == "Player")
					{
						for (int i = 1; i < numAnimation; i++)
						{
							if (nameAnimate == "atkA")
							{
								pngAnimation = "attack-A" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "atkB")
							{
								pngAnimation = "attack-B" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "atkC")
							{
								pngAnimation = "attack-C" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "atkD")
							{
								pngAnimation = "attack-D" + std::to_string(i) + ".png";
								
							}
							else if (nameAnimate == "kick")
							{
								pngAnimation = "kick-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "dead")
							{
								pngAnimation = "dead-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "kick")
							{
								pngAnimation = "kick-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "hit-idle-b")
							{
								pngAnimation = "hit-idle-behind-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "hit-idle-f")
							{
								pngAnimation = "hit-idle-behind-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "hit-idle-f")
							{
								pngAnimation = "hit-idle-front-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "hit-wp-b")
							{
								pngAnimation = "hit-with-weapon-behind-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "hit-wp-f")
							{
								pngAnimation = "hit-with-weapon-front-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "dead")
							{
								pngAnimation = "dead-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "idle")
							{
								pngAnimation = "idle-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "idle-wp")
							{
								pngAnimation = "idle-with-weapon-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "run")
							{
								pngAnimation = "run-" + std::to_string(i) + ".png";
							}
							else if (nameAnimate == "walk-wp")
							{
								pngAnimation = "walk-with-weapon-" + std::to_string(i) + ".png";
							}
							auto frame = spriteCache->getSpriteFrameByName(pngAnimation);

							anims.pushBack(frame);
						}
						auto animate = Animate::create(Animation::createWithSpriteFrames(anims, 0.1f));
						m_player.insert(nameAnimate, animate);
						animate->retain();
					}
					anims.clear();
					spriteCache->destroyInstance();
				}
			}
		}
	}
}

Animate * ResourceManager::GetPlayerAction(string nameAnimation)
{
	return m_player.at(nameAnimation);
}

Animate * ResourceManager::GetVillagerAction(string nameAnimation)
{
	return m_villager.at(nameAnimation);
}

Animate * ResourceManager::GetBossAction(string nameAnimation)
{
	return m_boss.at(nameAnimation);
}

Animate * ResourceManager::GetRangeEnemyAction(string nameAnimation)
{
	return m_rangeEnemy.at(nameAnimation);
}

Animate * ResourceManager::GetMeleeEnemyAction(string nameAnimation)
{
	return m_meleeEnemy.at(nameAnimation);
}

Animate * ResourceManager::GetDefMiniBossAction(string nameAnimation)
{
	return m_defMiniBoss.at(nameAnimation);
}

Animate * ResourceManager::GetAtkMiniBossAction(string nameAnimation)
{
	return m_atkMiniBoss.at(nameAnimation);
}
