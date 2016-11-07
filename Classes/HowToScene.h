#ifndef __HOWTO_SCENE_H__
#define __HOWTO_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "HelloWorldScene.h"
#include <iostream>
#include <sstream>

using namespace std;

class HowTo : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuReturn(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HowTo);

    void openMenu(cocos2d::Ref* pSender);
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif // __HOWTO_SCENE_H__
