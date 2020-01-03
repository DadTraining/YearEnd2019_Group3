#pragma once
#include "LoadMapScene.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
#include "Update.h"
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
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, 0));
	this->getPhysicsWorld()->setSubsteps(5);
	addMap();
	SpawnPlayer();
	addHud();
	createPhysics();
	addListener();
	scheduleUpdate();
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
	// ---
	auto objects = m_objectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);

		auto properties = object.asValueMap();
		int posX = properties.at("x").asFloat() * m_SCALE;
		int posY = properties.at("y").asFloat() * m_SCALE;
		int type = object.asValueMap().at("type").asInt();
		// Case the player is the main character
		if (type == Model::MAIN_CHARACTER_TYPE)
		{
			player = new Player(this);
			Update::GetInstance()->setPlayer(player);
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			m_player = player->getSprite();
			m_player->setPosition(Vec2(posX, posY));
			m_player->setScale(m_SCALE / 2);
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
 	}
}

void LoadMapScene::setViewPointCenter(Vec2 position)
{
	this->getDefaultCamera()->setPosition(position);
}

Vec2 LoadMapScene::tileCoordForPosition(Vec2 position)
{
	int x = position.x / (m_tileMap->getTileSize().width * m_SCALE);
	int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height * m_SCALE) - position.y)
		/ (m_tileMap->getTileSize().height * m_SCALE);
	return Vec2(x, y);
}

// indicate collsion between player and object

void LoadMapScene::addMap()
{
	m_tileMap = TMXTiledMap::create("Resources/Map/TileMap2.tmx");
	m_tileMap->setScale(m_SCALE);
	auto physicsBody = PhysicsBody::createEdgeBox(m_tileMap->getContentSize());
	m_tileMap->setPhysicsBody(physicsBody);
	m_meta = m_tileMap->layerNamed("Meta");
	m_objectGroup = m_tileMap->getObjectGroup("Objects");
	m_meta->setVisible(false);
	auto tree = m_tileMap->layerNamed("TreeTop");
	tree->setGlobalZOrder(Model::TREE_ORDER);
	addChild(m_tileMap, -1);

}

void LoadMapScene::createPhysics()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// world
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize + Size(0, 200),
		PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(Model::BITMASK_WORLD);

	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

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
		player->increaseVillager(1);
		
		HUD->addVilagerPoint();
		if (a->getCollisionBitmask() == Model::BITMASK_VILLAGER)
		{
			villagers.at(a->getGroup())->Die();
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_VILLAGER)
		{
			villagers.at(b->getGroup())->Die();
		}
	}
	// player attack enemy
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY && b->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK)
		|| (a->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK && b->getCollisionBitmask() == Model::BITMASK_ENEMY))
	{
		HUD->addVilagerPoint();
		if (a->getCollisionBitmask() == Model::BITMASK_ENEMY)
		{
			Skeletons.at(a->getGroup())->gotHit();
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_ENEMY)
		{
			Skeletons.at(b->getGroup())->gotHit();
		}
	}
	// Skeleton attack player
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY1_ATTACK && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ENEMY1_ATTACK))
	{
		HUD->addVilagerPoint();
		player->gotHit();
	}
	return false;
}

void LoadMapScene::addHud()
{
	HUD = new HudLayer(this, player, m_tileMap);
	HUD->setMap(m_tileMap);
}

void LoadMapScene::mb1MoveToPlayer()
{
	for (int i = 0; i < Skeletons.size(); i++) {
		auto rpIdleAnimate = RepeatForever::create(Skeletons[i]->getIdleAnimate());
		rpIdleAnimate->setTag(TAG_ANIMATE_IDLE1);
		auto rpAttackAnimate = Skeletons[i]->getAttackAnimate();
		rpAttackAnimate->setTag(TAG_ANIMATE_ATTACK);
		auto rpRunAnimate = RepeatForever::create(Skeletons[i]->getRunAnimate());
		rpRunAnimate->setTag(TAG_ANIMATE_RUN);
		auto range = std::sqrt(pow((Skeletons[i]->getSprite()->getPosition().x - player->getSprite()->getPosition().x), 2) + pow((Skeletons[i]->getSprite()->getPosition().y - player->getSprite()->getPosition().y), 2));
		auto vectorMoveToSpawnPoint = Vec2(Skeletons[i]->getPosSpawn().x - Skeletons[i]->getSprite()->getPosition().x, Skeletons[i]->getPosSpawn().y - Skeletons[i]->getSprite()->getPosition().y);
		auto vectorMoveToPlayer = Vec2(player->getSprite()->getPosition().x - Skeletons[i]->getSprite()->getPosition().x, player->getSprite()->getPosition().y - Skeletons[i]->getSprite()->getPosition().y);
		if (range < VISION_OF_MB) {
			if (player->getHP() > 0) {
					Skeletons[i]->getSprite()->getPhysicsBody()->setVelocity(vectorMoveToPlayer*SPEED_MB01);
					if (player->getSprite()->getPosition().x < Skeletons[i]->getSprite()->getPosition().x) {
						Skeletons[i]->getSprite()->setFlipX(180);
					}
					if (player->getSprite()->getPosition().x > Skeletons[i]->getSprite()->getPosition().x) {
						Skeletons[i]->getSprite()->setFlipX(0);
					}
					if (Skeletons[i]->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) > 0) {
						Skeletons[i]->getSprite()->stopAllActionsByTag(TAG_ANIMATE_IDLE1);
						Skeletons[i]->getSprite()->runAction(rpRunAnimate);
					}
					if ((player->getSprite()->getPosition().y < (Skeletons[i]->getSprite()->getPosition().y + 50)) &&
						player->getSprite()->getPosition().y > (Skeletons[i]->getSprite()->getPosition().y - 50) &&
						std::sqrt(pow(player->getSprite()->getPosition().x - Skeletons[i]->getSprite()->getPosition().x, 2)) < RANGE_OF_MB) {
						if (Skeletons[i]->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0) {
							Skeletons[i]->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
							Skeletons[i]->getSprite()->runAction(rpAttackAnimate);
						}
					}
					else {
						if (Skeletons[i]->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) > 0) {
							Skeletons[i]->getSprite()->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
							Skeletons[i]->getSprite()->runAction(rpRunAnimate);
						}
					}
			}
			else {
				if (Skeletons[i]->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_ATTACK) > 0) {
					Skeletons[i]->getSprite()->stopAllActionsByTag(TAG_ANIMATE_ATTACK);
					Skeletons[i]->getSprite()->runAction(rpRunAnimate);
				}
				Skeletons[i]->getSprite()->getPhysicsBody()->setVelocity(vectorMoveToSpawnPoint*SPEED_MB01);
				if ((Skeletons[i]->getSprite()->getPosition() < Skeletons[i]->getPosSpawn() && Skeletons[i]->getSprite()->getPosition() > Skeletons[i]->getPosSpawn() - Vec2(5, 5)) ||
					Skeletons[i]->getSprite()->getPosition() > Skeletons[i]->getPosSpawn() && Skeletons[i]->getSprite()->getPosition() < Skeletons[i]->getPosSpawn() + Vec2(5, 5)) {
					Skeletons[i]->getSprite()->setPosition(Skeletons[i]->getPosSpawn());
				}
				if (Skeletons[i]->getPosSpawn().x > Skeletons[i]->getSprite()->getPosition().x) {
					Skeletons[i]->getSprite()->setFlipX(0);
				}
				if (Skeletons[i]->getPosSpawn().x < Skeletons[i]->getSprite()->getPosition().x) {
					Skeletons[i]->getSprite()->setFlipX(180);
				}
				if (Skeletons[i]->getPosSpawn().x == Skeletons[i]->getSprite()->getPosition().x) {
					if (Skeletons[i]->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) == 0) {
						Skeletons[i]->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
						Skeletons[i]->getSprite()->runAction(rpIdleAnimate);
					}
				}
			}
		}
		else {
			Skeletons[i]->getSprite()->getPhysicsBody()->setVelocity(vectorMoveToSpawnPoint*SPEED_MB01);
			if ((Skeletons[i]->getSprite()->getPosition() < Skeletons[i]->getPosSpawn()&& Skeletons[i]->getSprite()->getPosition() > Skeletons[i]->getPosSpawn()-Vec2(5, 5))||
				Skeletons[i]->getSprite()->getPosition() > Skeletons[i]->getPosSpawn() && Skeletons[i]->getSprite()->getPosition() < Skeletons[i]->getPosSpawn() + Vec2(5, 5)) {
				Skeletons[i]->getSprite()->setPosition(Skeletons[i]->getPosSpawn());
			}
			if (Skeletons[i]->getPosSpawn().x > Skeletons[i]->getSprite()->getPosition().x) {
				Skeletons[i]->getSprite()->setFlipX(0);
			}
			if (Skeletons[i]->getPosSpawn().x < Skeletons[i]->getSprite()->getPosition().x) {
				Skeletons[i]->getSprite()->setFlipX(180);
			}
			if (Skeletons[i]->getPosSpawn().x==Skeletons[i]->getSprite()->getPosition().x) {
				if (Skeletons[i]->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_IDLE1) == 0) {
					Skeletons[i]->getSprite()->stopAllActionsByTag(TAG_ANIMATE_RUN);
					Skeletons[i]->getSprite()->runAction(rpIdleAnimate);
				}
				
			}
		}
		
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
	mb1MoveToPlayer();
	for (int i = 0; i < villagers.size(); i++)
	{
		villagers[i]->update(dt);
	}
}


