
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
	// Init the tile map to the gameplay
	// Adding the tile map to the child
	m_tileMap = TMXTiledMap::create("Resources/Map/TileMap.tmx");
	m_tileMap->setScale(1.5f);
	auto background = Sprite::create("Resources/test.png");
	background->setPosition(500, 500);
	background->setScale(2.0f);
	this->setScale(2.0f);
	addChild(background);
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
	m_player = Sprite::create("Resources/sprites/Player.png");
	m_player->setPosition(x, y);
	addChild(m_player);
}

void LoadMapScene::setViewPointCenter(Vec2 position)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);

	x = MIN(x, (m_tileMap->getMapSize().width * this->m_tileMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (m_tileMap->getMapSize().height * this->m_tileMap->getTileSize().height) - visibleSize.height / 2);

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
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveUp);
		repeatForever->setTag(1);
		event->getCurrentTarget()->runAction(repeatForever);
		break;
	}
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveUp->reverse());
		repeatForever->setTag(2);
		event->getCurrentTarget()->runAction(repeatForever);
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveRight);
		repeatForever->setTag(3);
		event->getCurrentTarget()->runAction(repeatForever);
		break;
	}
	case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		auto repeatForever = RepeatForever::create(moveRight->reverse());
		repeatForever->setTag(4);
		event->getCurrentTarget()->runAction(repeatForever);
		break;
	}
	default:
		break;
	}
}
// When the key is released
void LoadMapScene::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		event->getCurrentTarget()->stopActionByTag(1);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		event->getCurrentTarget()->stopActionByTag(2);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		event->getCurrentTarget()->stopActionByTag(3);
		break;
	case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		event->getCurrentTarget()->stopActionByTag(4);
		break;
	default:
		break;
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
}
