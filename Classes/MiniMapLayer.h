#ifndef __MINIMAP_LAYER_H__
#define __MINIMAP_LAYER_H__
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Model.h"

class MiniMapLayer : public cocos2d::LayerColor
{
private:
	cocos2d::TMXTiledMap* miniMap;
public:
	static cocos2d::Layer* createLayer();
	virtual bool init();
	void update(float dt);
	void addMinimap();
	void setPositionMiniMap();
	CREATE_FUNC(MiniMapLayer);

};
#endif // __MINIMAP_LAYER_H__