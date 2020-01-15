#pragma once
#include "LoadMapScene.h"
#include "Model.h"
#include "Update.h"
#include "Sound.h"
#include "CastleScene.h"
#include "MainMenu.h"
#include "IceCastleScene.h"
USING_NS_CC;


Scene* LoadMapScene::createScene()
{
	return LoadMapScene::create();
}

bool LoadMapScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, 0));
	this->getPhysicsWorld()->setSubsteps(2);
	Sound::GetInstance()->soundBackGroundDesert();
	addMap(); // Done
	SpawnPlayer(); // Done
	addHud();
	createPhysics(); // Done
	addListener(); // Done
	addSandParticle(); // Done
	scheduleUpdate(); // Done
	return true;
}

void LoadMapScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

// This method spawn the character at the coordinator of the player in
// the Map
void LoadMapScene::SpawnPlayer()
{
	// ---
	//number of Villager
	int numberOfVillager = 0;
	int numberOfSkeleton = 0;
	int numberOfEnemy2 = 0;
	int numberOfEnemy3 = 0;
	// ---
	auto objects = m_objectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);

		auto properties = object.asValueMap();
		int posX = properties.at("x").asFloat() * m_SCALE_32x32;
		int posY = properties.at("y").asFloat() * m_SCALE_32x32;
		int type = object.asValueMap().at("type").asInt();
		// Case the player is the main character
		if (type == Model::MAIN_CHARACTER_TYPE)
		{
			player = new Player(this);
			Update::GetInstance()->setPlayer(player);
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			m_player = player->getSprite();
			m_player->setPosition(Vec2(posX, posY));
			m_player->setScale(m_SCALE_32x32 / 2);
			addChild(m_player);
		}
		else if (type == Model::MAIN_VILLAGER_TYPE)
		{
			auto villager = new Villager(this);
			villager->setIndex(villagers.size());
			villagers.push_back(villager);
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			villager->getSprite()->setPosition(Vec2(posX, posY));
			auto animation = RepeatForever::create(villager->getIdleAnimate());
			animation->setTag(TAG_ANIMATE_IDLE1);
			villager->getSprite()->runAction(animation);
			addChild(villager->getSprite());
		}
		else if (type == Model::MAIN_MONSTER_TYPE)
		{
			auto boss = new MiniBoss01(this);
			boss->setPosSpawn(Vec2(posX, posY));
			boss->setIndex(Skeletons.size());
			Skeletons.push_back(boss);
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			boss->getSprite()->setPosition(Vec2(posX, posY));
			auto animation = RepeatForever::create(boss->getIdleAnimate());
			animation->setTag(TAG_ANIMATE_IDLE1);
			boss->getSprite()->runAction(animation);
			addChild(boss->getSprite());
		}
		else if (type == Model::MAIN_ENEMY2_TYPE)
		{
			auto enemy = new Enemy2(this);
			enemy->setPosSpawn(Vec2(posX, posY));
			enemy->setIndex(enemys2.size());
			enemys2.push_back(enemy);
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			enemy->getSprite()->setPosition(Vec2(posX, posY));
			auto animation = RepeatForever::create(enemy->getIdleAnimate());
			animation->setTag(TAG_ANIMATE_IDLE1);
			enemy->getSprite()->runAction(animation);
			addChild(enemy->getSprite());
		}
		else if (type == Model::MAIN_ENEMY3_TYPE+100)
		{
			auto enemy = new Enemy3(this);
			enemy->setPosSpawn(Vec2(posX, posY));
			enemy->setIndex(enemys3.size());
			enemys3.push_back(enemy);
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			enemy->getSprite()->setPosition(Vec2(posX, posY));
			auto animation = RepeatForever::create(enemy->getIdleAnimate());
			animation->setTag(TAG_ANIMATE_IDLE1);
			enemy->getSprite()->runAction(animation);
			addChild(enemy->getSprite());
		}
		else if (type == Model::MAIN_ENEMY4_TYPE)
		{
			auto enemy = new Enemy4(this);
			enemy->setPosSpawn(Vec2(posX, posY));
			enemy->setIndex(enemys4.size());
			enemys4.push_back(enemy);
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			enemy->getSprite()->setPosition(Vec2(posX, posY));
			auto animation = RepeatForever::create(enemy->getIdleAnimate());
			animation->setTag(TAG_ANIMATE_IDLE1);
			enemy->getSprite()->runAction(animation);
			addChild(enemy->getSprite());
		}
		else if (type == Model::ICE_BOSS_PORTAL_TYPE)
		{
			auto portal = new Portal();
			portal->InitSprite();
			portal->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_PORTAL_ICEBOSS);
			portal->getSprite()->setPosition(posX, posY);
			addChild(portal->getSprite(), -1);
			portal->setIndex(portals.size());
			portals.push_back(portal);
		}
		else if (type == Model::BASE_PORTAL_TYPE)
		{
			auto portal = new Portal();
			portal->InitSprite();
			portal->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_PORTAL_BASE);
			portal->getSprite()->setPosition(posX, posY);
			addChild(portal->getSprite(), -1);
			portal->setIndex(portals.size());
			portals.push_back(portal);
		}
	}
	CCLOG("------- Done Spawn");
}

void LoadMapScene::setViewPointCenter(Vec2 position)
{
	this->getDefaultCamera()->setPosition(position);
}

Vec2 LoadMapScene::tileCoordForPosition(Vec2 position)
{
	int x = position.x / (m_tileMap->getTileSize().width * m_SCALE_32x32);
	int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height * m_SCALE_32x32) - position.y)
		/ (m_tileMap->getTileSize().height * m_SCALE_32x32);
	return Vec2(x, y);
}

// indicate collsion between player and object

void LoadMapScene::addMap()
{
	m_tileMap = TMXTiledMap::create("Resources/Map/TileMap2.tmx");
	m_tileMap->setScale(m_SCALE_32x32);
	m_meta = m_tileMap->layerNamed("Meta");
	m_objectGroup = m_tileMap->getObjectGroup("Objects");
	m_meta->setVisible(false);
	auto tree = m_tileMap->layerNamed("TreeTop");
	auto statueTop = m_tileMap->layerNamed("StatueTop");
	statueTop->setGlobalZOrder(Model::TREE_ORDER);
	tree->setGlobalZOrder(Model::TREE_ORDER);
	addChild(m_tileMap, -1);
}

void LoadMapScene::createPhysics()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// Meta
	auto layerSize = m_meta->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = m_meta->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physics = PhysicsBody::createBox(tileSet->getContentSize(),
					PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physics->setCollisionBitmask(Model::BITMASK_GROUND);
				physics->setContactTestBitmask(false);
				physics->setDynamic(false);
				physics->setMass(100);
				tileSet->setPhysicsBody(physics);
			}
		}
	}
}

void LoadMapScene::addListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(LoadMapScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool LoadMapScene::onContactBegin(cocos2d::PhysicsContact & contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();
	// player touch villager
	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_VILLAGER)
		|| (a->getCollisionBitmask() == Model::BITMASK_VILLAGER && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_VILLAGER)
		{
			auto currentVillager = villagers.at(a->getGroup());
			player->increaseVillager(currentVillager->getPoint());
			currentVillager->Die();
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_VILLAGER)
		{
			auto currentVillager = villagers.at(b->getGroup());
			player->increaseVillager(currentVillager->getPoint());
			currentVillager->Die();
		}
	}
	// player attack enemy1
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY && b->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK)
		|| (a->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK && b->getCollisionBitmask() == Model::BITMASK_ENEMY))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_ENEMY)
		{
			auto currentSkeleton = Skeletons.at(a->getGroup());
			currentSkeleton->gotHit(player->getSlash()->getDamge());
			if (b->getTag() == Model::KNOCKBACK)
			{
				currentSkeleton->Stun();
			}
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_ENEMY)
		{
			auto currentSkeleton = Skeletons.at(b->getGroup());
			currentSkeleton->gotHit(player->getSlash()->getDamge());
			if (a->getTag() == Model::KNOCKBACK)
			{
				currentSkeleton->Stun();
			}
		}
	}
	// Skeleton attack player
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY1_ATTACK && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ENEMY1_ATTACK))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_ENEMY1_ATTACK)
		{
			auto currentSkeleton = Skeletons.at(a->getGroup());
			player->gotHit(currentSkeleton->getSlash()->getDamge());
		}
		if (b->getCollisionBitmask() == Model::BITMASK_ENEMY1_ATTACK)
		{
			auto currentSkeleton = Skeletons.at(b->getGroup());
			player->gotHit(currentSkeleton->getSlash()->getDamge());
		}
	}
	// player attack enemy2
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY2 && b->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK)
		|| (a->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK && b->getCollisionBitmask() == Model::BITMASK_ENEMY2))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_ENEMY2)
		{
			auto currentEnemy2 = enemys2.at(a->getGroup());
			currentEnemy2->gotHit(player->getSlash()->getDamge());
			if (b->getTag() == Model::KNOCKBACK)
			{
				currentEnemy2->Stun();
			}
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_ENEMY2)
		{
			auto currentEnemy2 = enemys2.at(b->getGroup());
			currentEnemy2->gotHit(player->getSlash()->getDamge());
			if (a->getTag() == Model::KNOCKBACK)
			{
				currentEnemy2->Stun();
			}
		}
	}
	// enemy2 attack player
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY2_ATTACK && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ENEMY2_ATTACK))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_ENEMY2_ATTACK)
		{
			auto currentEnemy2 = enemys2.at(a->getGroup());
			player->gotHit(currentEnemy2->getSlash()->getDamge());
		}
		if (b->getCollisionBitmask() == Model::BITMASK_ENEMY2_ATTACK)
		{
			auto currentEnemy2 = enemys2.at(b->getGroup());
			player->gotHit(currentEnemy2->getSlash()->getDamge());
		}
	}
	// player attack enemy3
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY3 && b->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK)
		|| (a->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK && b->getCollisionBitmask() == Model::BITMASK_ENEMY3))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_ENEMY3)
		{
			auto currentEnemy3 = enemys3.at(a->getGroup());
			currentEnemy3->gotHit(player->getSlash()->getDamge());
			if (b->getTag() == Model::KNOCKBACK)
			{
				currentEnemy3->Stun();
			}
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_ENEMY3)
		{
			auto currentEnemy3 = enemys3.at(b->getGroup());
			currentEnemy3->gotHit(player->getSlash()->getDamge());
			if (a->getTag() == Model::KNOCKBACK)
			{
				currentEnemy3->Stun();
			}
		}
	}
	// enemy3 attack player
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY3_ATTACK && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ENEMY3_ATTACK))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_ENEMY3_ATTACK)
		{
			auto currentEnemy3 = enemys3.at(a->getGroup());
			player->gotHit(currentEnemy3->getSlash()->getDamge());
		}
		if (b->getCollisionBitmask() == Model::BITMASK_ENEMY3_ATTACK)
		{
			auto currentEnemy3 = enemys3.at(b->getGroup());
			player->gotHit(currentEnemy3->getSlash()->getDamge());
		}
	}

	// player attack enemy4
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY4 && b->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK)
		|| (a->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK && b->getCollisionBitmask() == Model::BITMASK_ENEMY4))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_ENEMY4)
		{
			auto currentEnemy4 = enemys4.at(a->getGroup());
			currentEnemy4->gotHit(player->getSlash()->getDamge());
			if (b->getTag() == Model::KNOCKBACK)
			{
				currentEnemy4->Stun();
			}
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_ENEMY4)
		{
			auto currentEnemy4 = enemys4.at(b->getGroup());
			currentEnemy4->gotHit(player->getSlash()->getDamge());
			if (a->getTag() == Model::KNOCKBACK)
			{
				currentEnemy4->Stun();
			}
		}
	}
	// enemy4 attack player
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY4_ATTACK && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ENEMY4_ATTACK))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_ENEMY4_ATTACK)
		{
			auto currentEnemy4 = enemys4.at(a->getGroup());
			player->gotHit(currentEnemy4->getSlash()->getDamge());
		}
		if (b->getCollisionBitmask() == Model::BITMASK_ENEMY4_ATTACK)
		{
			auto currentEnemy4 = enemys4.at(b->getGroup());
			player->gotHit(currentEnemy4->getSlash()->getDamge());
		}
	}


	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_PORTAL_ICEBOSS)
		|| (a->getCollisionBitmask() == Model::BITMASK_PORTAL_ICEBOSS && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_PORTAL_ICEBOSS)
		{
			portals.at(a->getGroup())->returntoIceCastleScene();
		}
		else
		{
			portals.at(b->getGroup())->returntoIceCastleScene();
		}
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_PORTAL_BASE)
		|| (a->getCollisionBitmask() == Model::BITMASK_PORTAL_BASE && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_PORTAL_BASE)
		{
			portals.at(a->getGroup())->returntoMainMenu();
		}
		else
		{
			portals.at(b->getGroup())->returntoMainMenu();
		}
	}
	return false;
}

void LoadMapScene::addHud()
{
	HUD = new HudLayer(this, player);
}

void LoadMapScene::addSandParticle()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	sandBackground = CCParticleSystemQuad::create("Resources/Effect/backgroundSand.plist");
	sandBackground->setAnchorPoint(Vec2(0, 0));
	sandBackground->setContentSize(visibleSize);
	this->addChild(sandBackground);
	sandBackground->setGlobalZOrder(Model::TREE_ORDER + 1);
}

void LoadMapScene::enemyMoveToPlayer()
{
	for (int i = 0; i < Skeletons.size(); i++) {
		if (!Skeletons[i]->getAlive())
		{
			continue;
		}
		Skeletons[i]->setAIforEnemy();
	}
	for (int i = 0; i < enemys2.size(); i++) {
		if (!enemys2[i]->getAlive())
		{
			continue;
		}
		enemys2[i]->setAIforEnemy();
	}
	for (int i = 0; i < enemys3.size(); i++) {
		if (!enemys3[i]->getAlive())
		{
			continue;
		}
		enemys3[i]->setAIforEnemy();
	}
	for (int i = 0; i < enemys4.size(); i++) {
		if (!enemys4[i]->getAlive())
		{
			continue;
		}
		enemys4[i]->setAIforEnemy();
	}
}

void LoadMapScene::update(float dt)
{
	setViewPointCenter(this->m_player->getPosition());
	player->update(dt);
	for (int i = 0; i < Skeletons.size(); i++)
	{
		Skeletons[i]->update(dt);
	}
	for (int i = 0; i < enemys2.size(); i++)
	{
		enemys2[i]->update(dt);
	}
	for (int i = 0; i < enemys3.size(); i++)
	{
		enemys3[i]->update(dt);
	}
	for (int i = 0; i < enemys4.size(); i++)
	{
		enemys4[i]->update(dt);
	}
	enemyMoveToPlayer();
	for (int i = 0; i < villagers.size(); i++)
	{
		villagers[i]->update(dt);
	}
	sandBackground->setPosition(m_player->getPosition()
		+ Vec2(m_player->getContentSize().width, m_player->getContentSize().height));
}


