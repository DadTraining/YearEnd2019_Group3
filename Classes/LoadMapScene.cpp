
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
	//auto rFIdle = RepeatForever::create(player->getAnimateIdle());
	//rFIdle->setTag(0);
	//m_player->runAction(rFIdle);
	// Init the tile map to the gameplay
	// Adding the tile map to the child
	m_tileMap = TMXTiledMap::create("Resources/Map/TileMap2.tmx");
	m_tileMap->setScale(m_SCALE);
	//auto background = Sprite::create("Resources/test.png");
	//background->setPosition(500, 500);
	//background->setScale(m_SCALE * 2);
	//addChild(background);
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
	float x = spawnPoint.at("x").asFloat();
	float y = spawnPoint.at("y").asFloat();
	// create the player and add the x y to the player
	//m_player = Sprite::create("Resources/sprites/Player.png");
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

// Key for the character to moving
// When the key is pressed

void LoadMapScene::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	auto moveUp = MoveBy::create(0.1f, Vec2(0, 30));
	auto moveRight = MoveBy::create(0.1f, Vec2(30, 0));
	auto runAnimate = player->getAnimateRun();
	auto repeatForeverActionRun = RepeatForever::create(runAnimate);

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveUp);
		repeatForever->setTag(1);
		event->getCurrentTarget()->runAction(repeatForever);
		//
		repeatForeverActionRun->setTag(11);
		event->getCurrentTarget()->runAction(repeatForeverActionRun);
		event->getCurrentTarget()->stopAllActionsByTag(99);

		event->getCurrentTarget()->stopAllActionsByTag(12);
		event->getCurrentTarget()->stopAllActionsByTag(13);
		event->getCurrentTarget()->stopAllActionsByTag(14);

		//
		break;
	}
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveUp->reverse());
		repeatForever->setTag(2);
		//
		repeatForeverActionRun->setTag(12);
		event->getCurrentTarget()->runAction(repeatForever);
		event->getCurrentTarget()->runAction(repeatForeverActionRun);
		event->getCurrentTarget()->stopAllActionsByTag(99);

		event->getCurrentTarget()->stopAllActionsByTag(11);
		event->getCurrentTarget()->stopAllActionsByTag(13);
		event->getCurrentTarget()->stopAllActionsByTag(14);
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		repeatForeverActionRun->setTag(13);
		auto repeatForever = RepeatForever::create(moveRight);
		repeatForever->setTag(3);
		event->getCurrentTarget()->setRotationY(0.0f);
		event->getCurrentTarget()->runAction(repeatForever);
		event->getCurrentTarget()->runAction(repeatForeverActionRun);
		event->getCurrentTarget()->stopAllActionsByTag(99);
		//
		event->getCurrentTarget()->stopAllActionsByTag(12);
		event->getCurrentTarget()->stopAllActionsByTag(11);
		event->getCurrentTarget()->stopAllActionsByTag(14);
		break;
	}
	case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		repeatForeverActionRun->setTag(14);
		auto repeatForever = RepeatForever::create(moveRight->reverse());
		repeatForever->setTag(4);
		event->getCurrentTarget()->setRotationY(180.0f);
		event->getCurrentTarget()->runAction(repeatForever);
		event->getCurrentTarget()->runAction(repeatForeverActionRun);
		event->getCurrentTarget()->stopAllActionsByTag(99);
		//
		event->getCurrentTarget()->stopAllActionsByTag(12);
		event->getCurrentTarget()->stopAllActionsByTag(11);
		event->getCurrentTarget()->stopAllActionsByTag(13);
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
		event->getCurrentTarget()->stopAllActionsByTag(11);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		event->getCurrentTarget()->stopAllActionsByTag(2);
		event->getCurrentTarget()->stopAllActionsByTag(12);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		event->getCurrentTarget()->stopAllActionsByTag(3);
		event->getCurrentTarget()->stopAllActionsByTag(13);
		break;
	case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		event->getCurrentTarget()->stopAllActionsByTag(4);
		event->getCurrentTarget()->stopAllActionsByTag(14);
		break;
	default:
		break;
	}
	event->getCurrentTarget()->runAction(repeatForeverIdle);
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
}
