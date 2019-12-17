#include "GameStart.h"

USING_NS_CC;

Scene* GameStart::createScene()
{
    return GameStart::create();
}

bool GameStart::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto label = Label::createWithTTF("Play", "fonts/8BIT WONDER.ttf", 48);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer

        this->addChild(label, 1)
    return true;
}
