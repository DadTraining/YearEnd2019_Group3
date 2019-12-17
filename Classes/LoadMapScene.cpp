
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
	addChild(m_tileMap);
	// spawn the character at the SpawnPoint
	SpawnPlayer();
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

void LoadMapScene::update(float dt)
{
	setViewPointCenter(this->m_player->getPosition());
}
