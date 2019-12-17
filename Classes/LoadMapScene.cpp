
#include "LoadMapScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* LoadMapScene::createScene()
{
    return LoadMapScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadMapScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}


void LoadMapScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
