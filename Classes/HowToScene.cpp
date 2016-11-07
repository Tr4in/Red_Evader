#include "HowToScene.h"

USING_NS_CC;

Scene* HowTo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HowTo::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HowTo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto playerSprite = Sprite::create("PlayerBlue.png");
    playerSprite->setPosition(visibleSize.width * 0.15f, visibleSize.height * 0.95f);
    playerSprite->setScale(0.75f);
    this->addChild(playerSprite, 1);

    auto descriptionPlayer = Label::createWithTTF("That's the player! You can move him around \n by touching the visible Area!", "fonts/Marker Felt.ttf", 15);
    descriptionPlayer->setPosition(Vec2(visibleSize.width * 0.20f, visibleSize.height * 0.9f));
    descriptionPlayer->setAnchorPoint(Vec2(0,0));
    this->addChild(descriptionPlayer, 1);

    auto enemy = Sprite::create("enemy_red.png");
    enemy->setPosition(visibleSize.width * 0.15, visibleSize.height * 0.7f);
    enemy->setScale(0.75f);
    this->addChild(enemy, 1);

    auto descriptionEnemy = Label::createWithTTF("Don't let be hit by that one!", "fonts/Marker Felt.ttf", 15);
    descriptionEnemy->setPosition(Vec2(visibleSize.width * 0.20f, visibleSize.height * 0.65f));
    descriptionEnemy->setAnchorPoint(Vec2(0,0));
    this->addChild(descriptionEnemy, 1);

    auto friend_enemy = Sprite::create("enemy_blue.png");
    friend_enemy->setPosition(visibleSize.width * 0.15f, visibleSize.height * 0.45f);
    friend_enemy->setScale(0.75f);
    this->addChild(friend_enemy, 1);

    auto descriptionFriend = Label::createWithTTF("Your friend! Collect him and gain points!", "fonts/Marker Felt.ttf", 15);
    descriptionFriend->setPosition(Vec2(visibleSize.width * 0.20f, visibleSize.height * 0.40f));
    descriptionFriend->setAnchorPoint(Vec2(0,0));
    this->addChild(descriptionFriend, 1);

    auto life = Sprite::create("life.png");
    life->setPosition(visibleSize.width * 0.15f, visibleSize.height * 0.20f);
    life->setScale(0.75f);
    this->addChild(life, 1);

    auto descriptionLife = Label::createWithTTF("Life increases by one!", "fonts/Marker Felt.ttf", 15);
    descriptionLife->setPosition(Vec2(visibleSize.width * 0.20f, visibleSize.height * 0.15f));
    descriptionLife->setAnchorPoint(Vec2(0,0));
    this->addChild(descriptionLife, 1);

    auto menuItem = MenuItemImage::create("menu/menu.png", "menu/menu.png", CC_CALLBACK_1(HowTo::menuReturn, this));
    menuItem->setPosition(Vec2(visibleSize.width * 0.9, visibleSize.height * 0.2));

    auto gotoMenu = Menu::create(menuItem, nullptr);
    gotoMenu->setPosition(Vec2::ZERO);
    this->addChild(gotoMenu, 1);


    return true;
}

void HowTo::menuReturn(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}
