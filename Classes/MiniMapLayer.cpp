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
	return true;
}


void MiniMapLayer::addMinimap() // Done
{
	this->miniMap = TMXTiledMap::create("Resources/Map/TileMap2.tmx");
	this->addChild(miniMap);
	miniMap->setScale(SCALE_MINIMAP);
	miniMap->setAnchorPoint(Vec2(0, 0));
	// Set the Position for the map
	this->setPositionMiniMap();
	setMiniPlayer();
	setVisibleObject();

}

void MiniMapLayer::setPositionMiniMap() // Done
{
	auto minimapSize = this->miniMap->getContentSize() * SCALE_MINIMAP;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto height = visibleSize.height - minimapSize.height;
	auto width = visibleSize.width - minimapSize.width;
	miniMap->setPosition(width, height);
}

void MiniMapLayer::updateMiniPlayerPosition()
{
	auto playerCurrentPosition = this->currentPlayer->getSprite()->getPosition() * SCALE_MINIMAP / m_SCALE_32x32;
	auto miniMapPos = this->miniMap->getPosition();
	this->miniPlayer->setPosition(miniMapPos + playerCurrentPosition);
}

void MiniMapLayer::setMiniPlayer() // done
{
	this->currentPlayer = Update::GetInstance()->getPlayer();
	this->miniPlayer = Sprite::create("Resources/Map/HeroIcon.png");
	this->miniPlayer->setScale(SCALE_MINIMAP / 2);
	this->miniPlayer->setAnchorPoint(Vec2(0, 0));
	this->miniPlayer->setAnchorPoint(Vec2(0.5, 0));
	this->miniPlayer->setPosition(this->miniMap->getPosition());
	this->addChild(miniPlayer);
}

void MiniMapLayer::setVisibleObject() // Done
{
	miniMap->getLayer("TreeTop")->setVisible(false);
	miniMap->getLayer("TreeBottom")->setVisible(false);
	miniMap->getLayer("Grass")->setVisible(false);
	miniMap->getLayer("StatueTop")->setVisible(false);
	miniMap->getLayer("StatueBottom")->setVisible(false);
	miniMap->getLayer("Water Object")->setVisible(false);
	miniMap->getLayer("Meta")->setVisible(false);
}

void MiniMapLayer::update(float dt)
{
	updateMiniPlayerPosition();
}
