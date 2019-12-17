
#ifndef __LOADMAP_SCENE_H__
#define __LOADMAP_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class LoadMapScene : public cocos2d::Scene
{
private:
	TMXTiledMap* m_tileMap;
	Sprite* m_player;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(LoadMapScene);

	// Extra methods for adding the map
	// --------------------------------
	void SpawnPlayer();
	void setViewPointCenter(Vec2 position);
	// --------------------------------
	void update(float dt);
};

#endif // __LOADMAP_SCENE_H__
