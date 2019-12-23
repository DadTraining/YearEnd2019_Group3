	
#include "LoadMapScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* LoadMapScene::createScene()
{
    return LoadMapScene::create();
}

bool LoadMapScene::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	player = new Player(this);
	m_player = player->getSprite();
	// Init the tile map to the gameplay
	// Adding the tile map to the child
	m_tileMap = TMXTiledMap::create("Resources/Map/TileMap2.tmx");
	m_tileMap->setScale(m_SCALE);
	// Get the Meta layer for indicate collision and eaten
	m_meta = m_tileMap->layerNamed("Meta");
	m_meta->setVisible(false);
	// Get the m_villagerLayer  in the Map
	m_villagerLayer = m_tileMap->layerNamed("Villagers");
	addChild(m_tileMap, -1);
	// spawn the character at the SpawnPoint
	SpawnPlayer();
	// Set the keyboard to the character
	// Create the joystick
	CreateJoystick(this);
	createHud();
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
	// Get the object group named Objects
	auto objectGroup = m_tileMap->objectGroupNamed("Objects");
	if (objectGroup == NULL)
	{
		return;
	}
	// get the x y of the spawnPoint
	auto spawnPoint = objectGroup->objectNamed("SpawnPoint");
	float x = spawnPoint.at("x").asFloat() * m_SCALE;
	float y = spawnPoint.at("y").asFloat() * m_SCALE;
	// create the player and add the x y to the player
	m_player->setPosition(x, y);
	m_player->setScale(m_SCALE / 2);
	// add the physicsBody
	physicsBody = PhysicsBody::createBox(m_player->getContentSize());
	physicsBody->setDynamic(false);
	m_player->setPhysicsBody(physicsBody);
	addChild(m_player);
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
	this->setPosition(viewPoint);
	_hudLayer->setPosition(Vec2(x - visibleSize.width / 2, y - visibleSize.height / 2));
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
					//for (int i = 1; i < 5; i++)
					//{
					//	if (m_player->getActionByTag(i) != NULL)
					//	{
					//		auto moveUp = MoveBy::create(0.1f, Vec2(0, 10));
					//		auto moveRight = MoveBy::create(0.1f, Vec2(10, 0));
					//		switch (i)
					//		{
					//			// case when player move Up
					//		case 1:
					//		{
					//			m_player->stopActionByTag(i);
					//			m_player->runAction(moveUp->clone()->reverse());
					//			break;
					//		}
					//		// case when player move Down, we have to move it up
					//		case 2:
					//		{
					//			m_player->stopActionByTag(i);
					//			m_player->runAction(moveUp->clone());
					//			break;
					//		}
					//		// case when player move Right, we have to move it to left
					//		case 3:
					//		{
					//			m_player->stopActionByTag(i);
					//			m_player->runAction(moveRight->clone()->reverse());
					//			break;
					//		}
					//		// case when player move Left, we have to move it to right
					//		case 4:
					//		{
					//			m_player->stopActionByTag(i);
					//			m_player->runAction(moveRight->clone());
					//			break;
					//		}
					//		};
					//	}
					//}
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

void LoadMapScene::CreateJoystick(Scene * scene)
{
	auto thumb = Sprite::create("Resources/sprites/JoyStick/thumb.png");
	auto joystick = Sprite::create("Resources/sprites/JoyStick/joystick.png");
	Rect joystickBaseDimensions = Rect(0, 0, 40.f, 40.0f);
	Point joystickBasePosition;
	joystickBasePosition = Vec2(thumb->getBoundingBox().size.width / 2 + joystick->getBoundingBox().size.width / 2
		, thumb->getBoundingBox().size.height / 2 + joystick->getBoundingBox().size.height / 2);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite(thumb);
	joystickBase->setThumbSprite(joystick);
	joystickBase->getThumbSprite()->setScale(0.5f);
	joystick->setScale(0.5f);
	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);
	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);

	leftJoystick = joystickBase->getJoystick();
	//this->addChild(joystickBase, 4);
	//joystickBase->setCameraMask(2);

	activeRunRange = thumb->getBoundingBox().size.height / 2;
}

void LoadMapScene::UpdateJoystick(float dt)
{
	Point pos = leftJoystick->getStickPosition();
	float radius = std::sqrt(pos.x*pos.x + pos.y*pos.y);
	auto rpAnimateIdle = RepeatForever::create(player->getAnimateIdle());
	rpAnimateIdle->setTag(1);
	auto rpAnimateRun = RepeatForever::create(player->getAnimateRun());
	rpAnimateRun->setTag(2);
	if (radius > 0)
	{
		float degree = std::atan2f(pos.y, pos.x) * 180 / 3.141593;
		if (degree>-90 && degree<90) {
			m_player->setFlipX(false);
		}
		else {
			m_player->setFlipX(true);
		}
		m_player->stopAllActionsByTag(1);
		m_player->runAction(rpAnimateRun);
		physicsBody->setVelocity(pos*SPEED);
	}
	else
	{
		m_player->stopAllActionsByTag(2);
		m_player->runAction(rpAnimateIdle);
		physicsBody->setVelocity(Vec2(0, 0));
	}
}

void LoadMapScene::createHud()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// Init the layer of hud
	_hudLayer = Layer::create();
	// create a label to increase the score
	_hudLayer->addChild(joystickBase);
	_hudScore = Label::create(std::to_string(this->_numCollected), "fonts/arial.ttf", 24);
	int margin = 20;
	_hudScore->setPosition(Vec2(visibleSize.width - (_hudScore->getContentSize().width / 2) - margin,
		_hudScore->getContentSize().height / 2 + margin));
	_hudLayer->addChild(_hudScore);
	addChild(_hudLayer, 10);
}

void LoadMapScene::updateHud(float dt)
{
	_hudScore->setString(std::to_string(this->_numCollected));
}

void LoadMapScene::update(float dt)
{
	setViewPointCenter(this->m_player->getPosition());
	UpdateJoystick(dt);
	updateHud(dt);
	isCollision(this->m_player->getPosition());
	isCollectable(this->m_player->getPosition());
}
