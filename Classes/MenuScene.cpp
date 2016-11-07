#include "MenuScene.h"
#include "ScoreScene.h"
#include "SimpleAudioEngine.h"
#include "HowToScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto logoSprite = Sprite::create("logo/technopakiLogo.png");
    logoSprite->setPosition(Vec2(origin.x, visibleSize.height * 0.2f));
    logoSprite->setAnchorPoint(Vec2(0,0));
    logoSprite->setScale(0.4f);
    this->addChild(logoSprite);

    auto playItem = MenuItemImage::create("menu/play.png", "menu/play.png",CC_CALLBACK_1(MenuScene::playGame, this));
    playItem->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.9));

    auto playMenu = Menu::create(playItem, nullptr);
    playMenu->setPosition(Vec2::ZERO);
    this->addChild(playMenu, 1);

    auto howToItem = MenuItemImage::create("menu/info.png", "menu/info.png", CC_CALLBACK_1(MenuScene::openHowTo ,this));
    howToItem->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.6));

    auto howToMenu = Menu::create(howToItem, nullptr);
    howToMenu->setPosition(Vec2::ZERO);
    this->addChild(howToMenu, 1);

    auto closeItem = MenuItemImage::create("menu/close.png", "menu/close.png", CC_CALLBACK_1(MenuScene::closeGame, this));
    closeItem->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.3));

    auto closeMenu = Menu::create(closeItem, nullptr);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 1);

    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
    
    
}

void MenuScene::openHowTo(Ref* pSender)
{
	Director::getInstance()->pushScene(HowTo::createScene());
}

void MenuScene::pauseGame(Ref* pSender)
{
	//Pop up the Pause-scene
	Director::getInstance()->pushScene(Pause::createScene());
}

void MenuScene::playGame(Ref* pasender)
{
	Director::getInstance()->pushScene(HelloWorld::createScene());
}

void MenuScene::closeGame(Ref* pSender)
{
	Director::getInstance()->end();
}
