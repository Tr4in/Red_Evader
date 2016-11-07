#include "GameOverScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    int scorePoints = UserDefault::getInstance()->getIntegerForKey("score", 0);
    std::stringstream scorePointStr;
    scorePointStr << scorePoints;

    auto score = Label::createWithTTF("Your Score: " + scorePointStr.str(), "fonts/Marker Felt.ttf", 29);
    score->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.95);
    this->addChild(score, 1);

    auto playAgain = MenuItemImage::create("menu/play_again.png",
    									   "menu/play_again.png",
    									   CC_CALLBACK_1(GameOver::playGame, this));
    playAgain->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.75f);


    auto playAgainMenu = Menu::create(playAgain, nullptr);
    playAgainMenu->setPosition(Vec2());
    this->addChild(playAgainMenu, 1);

    auto menuItem = MenuItemImage::create("menu/menu.png", "menu/menu.png", CC_CALLBACK_1(GameOver::openMenu, this));
    menuItem->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));

    auto gotoMenu = Menu::create(menuItem, nullptr);
    gotoMenu->setPosition(Vec2::ZERO);
    this->addChild(gotoMenu, 1);


    return true;
}

void GameOver::menuReturn(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void GameOver::playGame(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void GameOver::closeGame(Ref* pSender)
{
	Director::getInstance()->end();
}

void GameOver::openMenu(Ref*pSender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}
