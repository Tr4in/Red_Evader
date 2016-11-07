#include "ScoreScene.h"

USING_NS_CC;

Scene* Score::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Score::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Score::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    int scorePoints = UserDefault::getInstance()->getIntegerForKey("score", 1);
    std::stringstream scorePointStr;
    scorePointStr << scorePoints;

    auto logoSprite = Sprite::create("logo/technopakiLogo.png");
    logoSprite->setPosition(Vec2(origin.x, visibleSize.height * 0.2f));
    logoSprite->setAnchorPoint(Vec2(0,0));
    logoSprite->setScale(0.4f);
    this->addChild(logoSprite);

    auto score = Label::createWithTTF("Your Score: " + scorePointStr.str(), "fonts/Marker Felt.ttf", 29);
    score->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.95);
    this->addChild(score, 1);

    auto playAgain = MenuItemImage::create("menu/play_again.png",
    									   "menu/play_again.png",
    									   CC_CALLBACK_1(Score::playGame, this));
    playAgain->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);


    auto playAgainMenu = Menu::create(playAgain, nullptr);
    playAgainMenu->setPosition(Vec2());
    this->addChild(playAgainMenu, 1);

    auto menuItem = MenuItemImage::create("menu/menu.png", "menu/menu.png", CC_CALLBACK_1(Score::openMenu, this));
    menuItem->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.2));

    auto gotoMenu = Menu::create(menuItem, nullptr);
    gotoMenu->setPosition(Vec2::ZERO);
    this->addChild(gotoMenu, 1);


    return true;
}

void Score::menuReturn(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void Score::playGame(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void Score::closeGame(Ref* pSender)
{
	Director::getInstance()->end();
}

void Score::openMenu(Ref*pSender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}
