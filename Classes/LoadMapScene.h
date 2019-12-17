
#ifndef __LOADMAP_SCENE_H__
#define __LOADMAP_SCENE_H__
#define m_SCALE 2.0f
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
	// Extra methods to make the character moving around
	// --------------------------------
	void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void setKeyBoard();
	// --------------------------------
	void update(float dt);
};

#endif // __LOADMAP_SCENE_H__
