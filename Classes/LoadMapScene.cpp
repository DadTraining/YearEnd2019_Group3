
#include "LoadMapScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* LoadMapScene::createScene()
{
    return LoadMapScene::create();
}

bool LoadMapScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	player = new Player(this);
	m_player = player->getSprite();
	auto rFIdle = RepeatForever::create(player->getAnimateIdle());
	rFIdle->setTag(99);
	m_player->runAction(rFIdle);
	// Init the tile map to the gameplay
	// Adding the tile map to the child
	m_tileMap = TMXTiledMap::create("Resources/Map/TileMap2.tmx");
	m_tileMap->setScale(m_SCALE);
	// Get the Meta layer for indicate collision and eaten
	m_meta = m_tileMap->layerNamed("Meta");
	m_meta->setVisible(false);

	addChild(m_tileMap, -1);
	// spawn the character at the SpawnPoint
	SpawnPlayer();
	// Set the keyboard to the character
	setKeyBoard();
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
}
// indicate collsion between player and object
Vec2 LoadMapScene::tileCoordForPosition(Vec2 position)
{
	int x = position.x / (m_tileMap->getTileSize().width * m_SCALE);
	int y = ((m_tileMap->getMapSize().height * m_tileMap->getTileSize().height * m_SCALE) - position.y)
		/ (m_tileMap->getTileSize().height * m_SCALE);
	return Vec2(x, y);
}

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
					for (int i = 1; i < 5; i++)
					{
						if (m_player->getActionByTag(i) != NULL)
						{
							auto moveUp = MoveBy::create(0.1f, Vec2(0, 10));
							auto moveRight = MoveBy::create(0.1f, Vec2(10, 0));
							switch (i)
							{
								// case when player move Up
							case 1:
							{
								m_player->stopActionByTag(i);
								m_player->runAction(moveUp->clone()->reverse());
								break;
							}
							// case when player move Down, we have to move it up
							case 2:
							{
								m_player->stopActionByTag(i);
								m_player->runAction(moveUp->clone());
								break;
							}
							// case when player move Right, we have to move it to left
							case 3:
							{
								m_player->stopActionByTag(i);
								m_player->runAction(moveRight->clone()->reverse());
								break;
							}
							// case when player move Left, we have to move it to right
							case 4:
							{
								m_player->stopActionByTag(i);
								m_player->runAction(moveRight->clone());
								break;
							}
							};
						}
					}
					return;
				}
			}
		}
	}
	stuck = false;
}

// Key for the character to moving
// When the key is pressed
void LoadMapScene::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	auto moveUp = MoveBy::create(0.1f, Vec2(0, 30));
	auto moveRight = MoveBy::create(0.1f, Vec2(30, 0));
	auto runAnimate = player->getAnimateRun();
	auto repeatForeverActionRun = RepeatForever::create(runAnimate);
	repeatForeverActionRun->setTag(11);
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveUp);
		repeatForever->setTag(1);
		event->getCurrentTarget()->runAction(repeatForever);
		//
		event->getCurrentTarget()->stopAllActionsByTag(99);
		event->getCurrentTarget()->stopAllActionsByTag(11);
		event->getCurrentTarget()->runAction(repeatForeverActionRun);
		this->player->m_numberOfKeyPress++;
		//
		break;
	}
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveUp->reverse());
		repeatForever->setTag(2);
		//
		event->getCurrentTarget()->runAction(repeatForever);
		event->getCurrentTarget()->stopAllActionsByTag(99);
		// --------------------------------------------
		event->getCurrentTarget()->stopAllActionsByTag(11);
		event->getCurrentTarget()->runAction(repeatForeverActionRun);
		this->player->m_numberOfKeyPress++;

		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveRight);
		repeatForever->setTag(3);
		event->getCurrentTarget()->setRotationY(0.0f);
		event->getCurrentTarget()->runAction(repeatForever);
		event->getCurrentTarget()->stopAllActionsByTag(99);
		//
		event->getCurrentTarget()->stopAllActionsByTag(11);
		event->getCurrentTarget()->runAction(repeatForeverActionRun);
		this->player->m_numberOfKeyPress++;

		break;
	}
	case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveRight->reverse());
		repeatForever->setTag(4);
		event->getCurrentTarget()->setRotationY(180.0f);
		event->getCurrentTarget()->runAction(repeatForever);
		event->getCurrentTarget()->stopAllActionsByTag(99);
		//
		event->getCurrentTarget()->stopAllActionsByTag(11);
		event->getCurrentTarget()->runAction(repeatForeverActionRun);
		this->player->m_numberOfKeyPress++;
		break;
	}
	default:
		break;
	}
}
// When the key is released
void LoadMapScene::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	auto idleAnimate = player->getAnimateIdle();
	auto repeatForeverIdle = RepeatForever::create(idleAnimate);
	repeatForeverIdle->setTag(99);
 	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		event->getCurrentTarget()->stopAllActionsByTag(1);
		this->player->m_numberOfKeyPress--;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		event->getCurrentTarget()->stopAllActionsByTag(2);
		this->player->m_numberOfKeyPress--;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		event->getCurrentTarget()->stopAllActionsByTag(3);
		this->player->m_numberOfKeyPress--;
		break;
	case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		event->getCurrentTarget()->stopAllActionsByTag(4);
		this->player->m_numberOfKeyPress--;
		break;
	default:
		break;
	}
	// If the player is not pressed by key moving then player will stop moving action
	if (player->m_numberOfKeyPress == 0) {
		this->m_player->stopAllActionsByTag(11);
		event->getCurrentTarget()->runAction(repeatForeverIdle);
	}
}
// Set all the keyboard code to the player
void LoadMapScene::setKeyBoard()
{
	auto listenerKeyBoard = EventListenerKeyboard::create();
	listenerKeyBoard->onKeyPressed = CC_CALLBACK_2(LoadMapScene::onKeyPressed, this);
	listenerKeyBoard->onKeyReleased = CC_CALLBACK_2(LoadMapScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyBoard, m_player);
}

void LoadMapScene::update(float dt)
{
	setViewPointCenter(this->m_player->getPosition());
	isCollision(this->m_player->getPosition());
}
