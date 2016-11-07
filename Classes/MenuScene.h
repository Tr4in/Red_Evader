#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "PauseScene.h"
#include "ui/CocosGUI.h"

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // Function to pause the game
    void pauseGame(cocos2d::Ref* pSender);
    // Play game
    void playGame(cocos2d::Ref* pSender);
    // Close game
    void closeGame(cocos2d::Ref* pSender);
    void openHowTo(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif // __MENU_SCENE_H__
