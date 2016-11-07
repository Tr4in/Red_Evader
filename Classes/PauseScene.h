#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"

class Pause : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Pause);

    void resumeGame(cocos2d::Ref* pSender);
};

#endif // __PAUSE_SCENE_H__
