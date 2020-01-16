#pragma once
#include "Model.h"
#include "Update.h"
#include "Sound.h"
#include "CastleScene.h"
#include "MainMenu.h"
#include "IceCastleScene.h"
USING_NS_CC;

cocos2d::Scene * IceCastleScene::createScene()
{
	return IceCastleScene::create();
}

bool IceCastleScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, 0));
	this->getPhysicsWorld()->setSubsteps(3);
	this->setTag(Model::FINAL_BOSS_PORTAL_TYPE);
	Sound::GetInstance()->soundBackGroundIceCastle();
	addMap();
	SpawnPlayer();
	addHud();
	createPhysics();
	addListener();
	addSnowParticle();
	scheduleUpdate();
	return true;
}

void IceCastleScene::addMap()
{
	m_tileMap = TMXTiledMap::create("Resources/Map/CastleMap/IceCastle.tmx");
	m_tileMap->setScale(2);
	m_meta = m_tileMap->layerNamed("Meta");
	m_objectGroup = m_tileMap->getObjectGroup("Objects");
	m_meta->setVisible(false);
	addChild(m_tileMap, -1);
}

void IceCastleScene::SpawnPlayer()
{
	//number of Villager
	int numberOfVillager = 0;
	int numberOfSkeleton = 0;
	int numberOfEnemy2 = 0;
	int numberOfEnemy3 = 0;
	int numberOfBoss = 0;
	// ---
	auto objects = m_objectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);

		auto properties = object.asValueMap();
		int posX = properties.at("x").asFloat() * m_SCALE_16x16;
		int posY = properties.at("y").asFloat() * m_SCALE_16x16;
		int type = object.asValueMap().at("type").asInt();
		// Case the player is the main character
		if (type == Model::MAIN_CHARACTER_TYPE)
		{
			player = new Player(this);
			player->setHP(Update::GetInstance()->getPlayer()->getHP());
			player->setDamage(Update::GetInstance()->getPlayer()->getDamage());
			player->increaseVillager(Update::GetInstance()->getPlayer()->getVillagersNum());
			Update::GetInstance()->setPlayer(player);
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			m_player = player->getSprite();
			m_player->removeFromParent();
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
		else if (type == Model::LAVA_BOSS_PORTAL_TYPE)
		{
			auto portal = new Portal();
			portal->InitSprite();
			portal->getSprite()->getPhysicsBody()->setCollisionBitmask(Model::BITMASK_PORTAL_LAVABOSS);
			portal->getSprite()->setPosition(posX, posY);
			addChild(portal->getSprite(), -1);
			portal->setIndex(portals.size());
			portals.push_back(portal);			
			portal->getSprite()->setVisible(false);
			portal->getSprite()->getPhysicsBody()->setEnabled(false);
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
			portal->getSprite()->setVisible(false);
			portal->getSprite()->getPhysicsBody()->setEnabled(false);
		}
		else if (type == Model::MAIN_BLUEBOSS_TYPE)
		{
			blueBoss = new BlueBoss(this);
			blueBoss->setPosSpawn(Vec2(posX, posY));
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			blueBoss->getSprite()->setPosition(Vec2(posX, posY));
			auto animation = RepeatForever::create(blueBoss->getIdleAnimate());
			animation->setTag(TAG_ANIMATE_IDLE1);
			addChild(blueBoss->getSprite());
		}
	}
}

void IceCastleScene::setViewPointCenter(Vec2 position)
{
	this->getDefaultCamera()->setPosition(position);
}

Vec2 IceCastleScene::tileCoordForPosition(Vec2 position)
{
	int x = position.x / (m_tileMap->getTileSize().width * m_SCALE_32x32);
	int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height * m_SCALE_32x32) - position.y)
		/ (m_tileMap->getTileSize().height * m_SCALE_32x32);
	return Vec2(x, y);
}

void IceCastleScene::createPhysics()
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

void IceCastleScene::addListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(IceCastleScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool IceCastleScene::onContactBegin(cocos2d::PhysicsContact & contact)
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
	
	//Player attack boss
	if ((a->getCollisionBitmask() == Model::BITMASK_BLUEBOSS && b->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK)
		|| (a->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK && b->getCollisionBitmask() == Model::BITMASK_BLUEBOSS))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_BLUEBOSS)
		{
			blueBoss->gotHit(player->getSlash()->getDamge());
			if (b->getTag() == Model::KNOCKBACK)
			{
				blueBoss->Stun();
			}
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_BLUEBOSS)
		{
			blueBoss->gotHit(player->getSlash()->getDamge());
			if (a->getTag() == Model::KNOCKBACK)
			{
				blueBoss->Stun();
			}
		}
	}
	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_PORTAL_LAVABOSS)
		|| (a->getCollisionBitmask() == Model::BITMASK_PORTAL_LAVABOSS && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_PORTAL_LAVABOSS)
		{
			portals.at(a->getGroup())->returntoLavaCastleScene();
		}
		else
		{
			portals.at(b->getGroup())->returntoLavaCastleScene();
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
	// enemy3 attack player
	if ((a->getCollisionBitmask() == Model::BITMASK_BLUEBOSS_ATTACK && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_BLUEBOSS_ATTACK))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_BLUEBOSS_ATTACK)
		{
			player->gotHit(blueBoss->getSlash()->getDamge());
		}
		if (b->getCollisionBitmask() == Model::BITMASK_BLUEBOSS_ATTACK)
		{
			player->gotHit(blueBoss->getSlash()->getDamge());
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

	return false;
}


void IceCastleScene::enemyMoveToPlayer()
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

	for (int i = 0; i < enemys4.size(); i++) {
		if (!enemys4[i]->getAlive())
		{
			continue;
		}
		enemys4[i]->setAIforEnemy();
	}
	if (blueBoss->getAlive()) {
		blueBoss->setAIforEnemy();
	}
}

void IceCastleScene::addHud()
{
	HUD = new HudLayer(this, player);
}

void IceCastleScene::addSnowParticle()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	snowBackground = CCParticleSystemQuad::create("Resources/Effect/backgroundSnow.plist");
	snowBackground->setAnchorPoint(Vec2(0.5, 0.5));
	//snowBackground->setScale();
	this->addChild(snowBackground);
	snowBackground->setGlobalZOrder(Model::TREE_ORDER + 1);
}

void IceCastleScene::update(float dt)
{
	setViewPointCenter(this->m_player->getPosition());
	player->update(dt);
	enemyMoveToPlayer();
	for (int i = 0; i < Skeletons.size(); i++)
	{
		Skeletons[i]->update(dt);
	}
	for (int i = 0; i < enemys2.size(); i++)
	{
		enemys2[i]->update(dt);
	}
	for (int i = 0; i < enemys4.size(); i++)
	{
		enemys4[i]->update(dt);
	}
	for (int i = 0; i < villagers.size(); i++)
	{
		villagers[i]->update(dt);
	}
	blueBoss->update(dt);
	snowBackground->setPosition(m_player->getPosition()
		+ Vec2(m_player->getContentSize().width, m_player->getContentSize().height));
	if (!blueBoss->getAlive())
	{
		for (int i = 0; i < this->portals.size(); i++)
		{
			portals.at(i)->getSprite()->setVisible(true);
			portals.at(i)->getSprite()->getPhysicsBody()->setEnabled(true);
		}
	}
}
