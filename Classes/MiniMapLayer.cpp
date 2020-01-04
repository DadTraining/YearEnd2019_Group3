# include "MiniMapLayer.h"
# define SCALE_MINIMAP 0.1f
cocos2d::Layer * MiniMapLayer::createLayer()
{
	return MiniMapLayer::create();
}

bool MiniMapLayer::init()
{
	if (!LayerColor::initWithColor(cocos2d::Color4B(0, 0, 0, 0)))
	{
		return false;
	}
	addMinimap();
	setMiniPlayer();
}


void MiniMapLayer::addMinimap()
{
	this->miniMap = TMXTiledMap::create("Resources/Map/TileMap2.tmx");
	this->addChild(miniMap);
	miniMap->setScale(SCALE_MINIMAP);
	miniMap->setAnchorPoint(Vec2(0, 0));
	// Set the Position for the map
	this->setPositionMiniMap();
}

void MiniMapLayer::setPositionMiniMap()
{
	auto minimapSize = this->miniMap->getContentSize() * SCALE_MINIMAP;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto height = visibleSize.height - minimapSize.height;
	auto width = visibleSize.width - minimapSize.width;
	miniMap->setPosition(width, height);
}

void MiniMapLayer::updateMiniPlayerPosition()
{
	auto playerCurrentPosition = this->currentPlayer->getSprite()->getPosition() * SCALE_MINIMAP / m_SCALE;
	auto miniMapPos = this->miniMap->getPosition();
	this->miniPlayer->setPosition(miniMapPos + playerCurrentPosition);
}

void MiniMapLayer::setMiniPlayer()
{
	this->currentPlayer = Update::GetInstance()->getPlayer();
	this->miniPlayer = Sprite::create("Resources/Map/HeroIcon.png");
	this->miniPlayer->setScale(SCALE_MINIMAP / 2);
	this->miniPlayer->setAnchorPoint(Vec2(0, 0));
	this->miniPlayer->setAnchorPoint(Vec2(0.5, 0.5));
	this->miniPlayer->setPosition(this->miniMap->getPosition());
	this->addChild(miniPlayer);
}

void MiniMapLayer::update(float dt)
{
	updateMiniPlayerPosition();
}
