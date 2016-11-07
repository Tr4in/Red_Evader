#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PauseScene.h"
#include "ui/CocosGUI.h"
#include "physics/CCPhysicsBody.h"
#include "physics/CCPhysicsShape.h"
#include "SimpleAudioEngine.h"
#include "ScoreScene.h"
#include "GameOverScene.h"
#include <iostream>
#include <sstream>

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // Function to pause the game
    void pauseGame(cocos2d::Ref* pSender);

    /*************** TouchEvents *******************/
    void initTouch();
    void movePlayerByTouch(cocos2d::Touch* touch, cocos2d::Event* event);
    void movePlayerBlueIfPossible(float newX, float newY);
    /*********************************************/

    /*************** Physics ***********************/
    void initPhysics();
    bool onCollision(cocos2d::PhysicsContact& contact);
    void setPhysicsBody(cocos2d::Sprite* sprite);
    void setPolygonPhysicsBody(cocos2d::Sprite* sprite);
    /***********************************************/

    /**************** Music ************************/
    void initAudio();
    /***********************************************/

    void spawnRedEnemy();
    void spawnBlueEnemy();
    void spawnEnemy(float dt);
    void spawnLife();
    void dissapearRedEnemy(const cocos2d::Node& node);
    void dissapearBlueEnemy(const cocos2d::Node& node);
    void dissapearGreenLife(const cocos2d::Node& node);

    bool checkLife();
    bool checkIfTenRedPoints();
    void incrementPoints();
    void incrementSpeed();
    float calculateTime();
    void killSprite(cocos2d::Node* sender, bool cleanup);

    void combo(const Node& node);
    /***************** Effects ********************/
    void lifeUp();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    /******** Player ***********/
    cocos2d::Sprite* playerBlue;
    cocos2d::Sprite* playerRed;
    /**************************/

    cocos2d::Sprite* enemyRed;
    cocos2d::Sprite* enemyBlue;

    /********** Speed ***********/
    int speed;
    unsigned int points;
    unsigned int life;
    unsigned int redPoints;
    unsigned int comboPoint;

    cocos2d::Label* lifeBar;
    cocos2d::Label*	pointsBar;
    cocos2d::Label*	redPointsBar;
    cocos2d::Label* comboBar;
    cocos2d::Label* sumAdded;

    std::stringstream lifeStr;
    std::stringstream pointStr;
    std::stringstream redPointsStr;
    std::stringstream comboPointStr;
	std::stringstream sumStr;
};

#endif // __HELLOWORLD_SCENE_H__
