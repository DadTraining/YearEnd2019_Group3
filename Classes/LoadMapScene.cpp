#pragma once
#include "LoadMapScene.h"
#include "SimpleAudioEngine.h"
#include "Model.h"
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
	addMap();
	SpawnPlayer();
	addHud();
	createPhysics();
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	//player = new Player(this);
	//m_player = player->getSprite();
	//// Get the object group named Objects
	//auto objectGroup = m_tileMap->objectGroupNamed("Objects");
	//if (objectGroup == NULL)
	//{
	//	return;
	//}
	// //get the x y of the spawnPoint
	//auto spawnPoint = objectGroup->objectNamed("SpawnPoint");
	//float x = spawnPoint.at("x").asFloat() * m_SCALE;
	//float y = spawnPoint.at("y").asFloat() * m_SCALE;
	//// create the player and add the x y to the player
	//m_player->setPosition(x, y);
	//m_player->setScale(m_SCALE / 2);
	// //add the physicsBody
	//addChild(m_player);

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
			m_player = player->getSprite();
			m_player->setPosition(Vec2(posX, posY));
			m_player->setScale(m_SCALE / 2);
			addChild(m_player);
		}
		else if (type == Model::MAIN_VILLAGER_TYPE)
		{
			auto villagerSprite = Sprite::create("Resources/sprites/Village/Idle/idle-1.png");
			villagerSprite->setPosition(Vec2(posX, posY));
			villagers.push_back(villagerSprite);
			auto physicBody = PhysicsBody::createBox(villagerSprite->getContentSize());
			villagerSprite->setPhysicsBody(physicBody);
			physicBody->setDynamic(false);
			physicBody->setCollisionBitmask(Model::BITMASK_VILLAGER);
			addChild(villagerSprite);
		}
	}
}

void LoadMapScene::setViewPointCenter(Vec2 position)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);

	auto borderX = m_tileMap->getMapSize().width * this->m_tileMap->getTileSize().width * m_SCALE;
	auto borderY = m_tileMap->getMapSize().width * this->m_tileMap->getTileSize().height * m_SCALE;
	x = MIN(x, borderX - visibleSize.width / 2);
	y = MIN(y, borderY - visibleSize.height / 2);

	auto actualPosition = Vec2(x, y);
	auto centerOfView = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	auto viewPoint = Vec2(centerOfView.x - actualPosition.x, centerOfView.y - actualPosition.y);
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
void LoadMapScene::isCollision(Vec2 position)
{
	auto tileCoord = this->tileCoordForPosition(position);
	int tileGid = this->m_meta->tileGIDAt(tileCoord);
	if (tileGid)
	{
		auto properties = m_tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty())
		{
			auto collision = properties["Collidable"].asString();
			if (collision.empty() || (collision.compare("true") == 0))
			{
				if (stuck == false)
				{
					stuck = true;
					m_player->getPhysicsBody()->setVelocity(Vec2(0, 0));
					return;
				}
			}
		}
	}
	stuck = false;
}

void LoadMapScene::isCollectable(Vec2 position)
{
	auto tileCoord = this->tileCoordForPosition(position);
	auto tileGid = this->m_meta->tileGIDAt(tileCoord);
	if (tileGid)
	{
		auto properties = m_tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty())
		{
			auto collect = properties["Collectable"].asString();
			if ((collect.compare("true") == 0))
			{
				m_meta->removeTileAt(tileCoord);
				m_villagerLayer->removeTileAt(tileCoord);
				_numCollected++;
			}
		}
	}
}

void LoadMapScene::addMap()
{
	m_tileMap = TMXTiledMap::create("Resources/Map/TileMap2.tmx");
	m_tileMap->setScale(m_SCALE);
	auto physicsBody = PhysicsBody::createEdgeBox(m_tileMap->getContentSize());
	m_tileMap->setPhysicsBody(physicsBody);
	m_meta = m_tileMap->layerNamed("Meta");
	m_objectGroup = m_tileMap->getObjectGroup("Objects");
	m_meta->setVisible(false);
	m_villagerLayer = m_tileMap->layerNamed("Villagers");
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
				physics->setContactTestBitmask(true);
				physics->setDynamic(false);
				physics->setMass(100);
				tileSet->setPhysicsBody(physics);
			}
		}
	}
}

void LoadMapScene::addListener()
{
	/*auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(LoadMapScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);*/
}

bool LoadMapScene::onContactBegin(cocos2d::PhysicsContact & contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();
	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_VILLAGER)
		|| (a->getCollisionBitmask() == Model::BITMASK_VILLAGER && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		HUD->addVilagerPoint();
	}
	return false;
}

void LoadMapScene::addHud()
{
	HUD = new HudLayer(this, player, m_tileMap);
	HUD->setMap(m_tileMap);
}

void LoadMapScene::update(float dt)
{
	setViewPointCenter(this->m_player->getPosition());
	//isCollision(this->m_player->getPosition());
	isCollectable(this->m_player->getPosition());
}


