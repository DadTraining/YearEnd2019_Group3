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
			SpriteFrameCache::getInstance()->removeSpriteFrames();
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
			physicBody->setContactTestBitmask(true);
			addChild(villagerSprite);
		}
		else if (type == Model::MAIN_MONSTER_TYPE)
		{
			auto boss = new MiniBoss01(this);
			boss->setPosSpawn(Vec2(posX, posY));
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
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	//int x = MAX(position.x, visibleSize.width / 2);
	//int y = MAX(position.y, visibleSize.height / 2);

	//auto borderX = m_tileMap->getMapSize().width * this->m_tileMap->getTileSize().width * m_SCALE;
	//auto borderY = m_tileMap->getMapSize().width * this->m_tileMap->getTileSize().height * m_SCALE;
	//x = MIN(x, borderX - visibleSize.width / 2);
	//y = MIN(y, borderY - visibleSize.height / 2);

	//auto actualPosition = Vec2(x, y);
	//auto centerOfView = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//auto viewPoint = Vec2(centerOfView.x - actualPosition.x, centerOfView.y - actualPosition.y);
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
		HUD->addVilagerPoint();
	}
	// player attack enemy
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY && b->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK)
		|| (a->getCollisionBitmask() == Model::BITMASK_NORMAL_ATTACK && b->getCollisionBitmask() == Model::BITMASK_ENEMY))
	{
		HUD->addVilagerPoint();
	}
	// Skeleton attack player
	if ((a->getCollisionBitmask() == Model::BITMASK_ENEMY1_ATTACK && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ENEMY1_ATTACK))
	{
		HUD->addVilagerPoint();
		m_player->stopAllActions();
		auto animation = player->getHitAnimate();
		animation->setTag(TAG_ANIMATE_HIT);
		m_player->runAction(animation);
	}
	return false;
}

void LoadMapScene::addHud()
{
	HUD = new HudLayer(this, player, m_tileMap);
	HUD->setMap(m_tileMap);
}
void LoadMapScene::checkConditionsToMiniBoss01Move()
{
	for (int i = 0; i < Skeletons.size(); i++) {
		auto rpIdleAnimate = RepeatForever::create(Skeletons[i]->getIdleAnimate());
		rpIdleAnimate->setTag(TAG_ANIMATE_IDLE1);
		auto rpAttackAnimate = RepeatForever::create(Skeletons[i]->getAttackAnimate());
		rpAttackAnimate->setTag(TAG_ANIMATE_ATTACK);
		auto rpRunAnimate = RepeatForever::create(Skeletons[i]->getRunAnimate());
		rpRunAnimate->setTag(TAG_ANIMATE_RUN);
		auto range = std::sqrt(pow((Skeletons[i]->getSprite()->getPosition().x - player->getSprite()->getPosition().x), 2) + pow((Skeletons[i]->getSprite()->getPosition().y - player->getSprite()->getPosition().y), 2));
		if (range < 300) {
			auto vectorMove = Vec2(player->getSprite()->getPosition().x - Skeletons[i]->getSprite()->getPosition().x, player->getSprite()->getPosition().y - Skeletons[i]->getSprite()->getPosition().y);
			Skeletons[i]->getSprite()->getPhysicsBody()->setVelocity(vectorMove*SPEED_MB01);
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
			if ((player->getSprite()->getPosition().y < (Skeletons[i]->getSprite()->getPosition().y + 50)) && player->getSprite()->getPosition().y >(Skeletons[i]->getSprite()->getPosition().y - 50)&&std::sqrt(pow(player->getSprite()->getPosition().x -Skeletons[i]->getSprite()->getPosition().x, 2))<100) {
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
			auto vectorMove = Vec2(Skeletons[i]->getPosSpawn().x - Skeletons[i]->getSprite()->getPosition().x, Skeletons[i]->getPosSpawn().y - Skeletons[i]->getSprite()->getPosition().y);
			Skeletons[i]->getSprite()->getPhysicsBody()->setVelocity(vectorMove*SPEED_MB01);
			if (Skeletons[i]->getPosSpawn().x > Skeletons[i]->getSprite()->getPosition().x) {
				Skeletons[i]->getSprite()->setFlipX(0);
			}
			if (Skeletons[i]->getPosSpawn().x < Skeletons[i]->getSprite()->getPosition().x) {
				Skeletons[i]->getSprite()->setFlipX(180);
			}
			if (Skeletons[i]->getPosSpawn().x== Skeletons[i]->getSprite()->getPosition().x &&Skeletons[i]->getPosSpawn().y == Skeletons[i]->getSprite()->getPosition().y) {
				if (Skeletons[i]->getSprite()->getNumberOfRunningActionsByTag(TAG_ANIMATE_RUN) > 0) {
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
	checkConditionsToMiniBoss01Move();
}


