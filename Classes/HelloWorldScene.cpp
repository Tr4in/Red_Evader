#include "HelloWorldScene.h"

using namespace std;

USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    /*
#if COCOS2D_DEBUG
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif*/

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();	// Resturns the whole visibleArea
    origin = Director::getInstance()->getVisibleOrigin();	// Returns the origin
    speed = -350;

    /***************** Label **************************/
    life = 5;
    lifeStr << life;
    lifeBar = Label::createWithTTF("Life: " + lifeStr.str(),"fonts/Marker Felt.ttf", 29);
    lifeBar->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height * 0.95));
    this->addChild(lifeBar, 1);

    points = 0;
    pointStr << points;
    pointsBar = Label::createWithTTF("Points: " + pointStr.str(),"fonts/Marker Felt.ttf", 29);
    pointsBar->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.95));
    this->addChild(pointsBar, 1);

    comboPoint = 0;
    comboBar = Label::createWithTTF("", "fonts/Marker Felt.ttf", 39);
    comboBar->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.2));
    this->addChild(comboBar, 1);

	sumAdded = Label::createWithTTF(sumStr.str(), "fonts/Marker Felt.ttf", 29);
	sumAdded->setPosition(Vec2(visibleSize.width * 0.82, visibleSize.height * 0.80));
	this->addChild(sumAdded, 1);

    /***************** Sprites ************************/

    playerBlue = Sprite::create("PlayerBlue.png");
    playerBlue->setPosition(visibleSize.width * 0.3, visibleSize.height * 0.5);
    setPolygonPhysicsBody(playerBlue);
    playerBlue->setTag(10);
    this->addChild(playerBlue, 1);
    /*************************************************/


    initTouch();	// Init touch events
    initPhysics();	// Init the physics
    initAudio();	// Init audio

    schedule(CC_SCHEDULE_SELECTOR(HelloWorld::spawnEnemy),  0.5f);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
    
}

void HelloWorld::pauseGame(Ref* pSender)
{
	//Pop up the Pause-scene
	Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, Pause::createScene()));
}

void HelloWorld::spawnEnemy(float dt)
{
	float randomNumber = CCRANDOM_0_1() * 2.5f;

	if(randomNumber >= 1.25f)
		spawnRedEnemy();


	else if(randomNumber >= 0.05f && randomNumber < 1.25f)
		spawnBlueEnemy();


	else if(randomNumber < 0.05f)
		spawnLife();

}

float HelloWorld::calculateTime()
{
	return visibleSize.width / (-static_cast<float>(speed));
}

void HelloWorld::spawnLife()
{
	float xPos = origin.x + visibleSize.width;
	float yPos = (origin.y + CCRANDOM_0_1() * visibleSize.height);

	auto lifeSprite = Sprite::create("life.png");
	lifeSprite->setPosition(xPos, yPos);
	lifeSprite->setTag(3);

	setPhysicsBody(lifeSprite);

	auto moveTo = MoveTo::create(1.0f, Vec2(origin.x, yPos));
	auto killSprite = CallFuncN::create(CC_CALLBACK_1(HelloWorld::killSprite,
			   	   	  this, true));
	auto action = Sequence::create(moveTo,
								   killSprite, nullptr);

	lifeSprite->runAction(action);

	this->addChild(lifeSprite, 1);
}

void HelloWorld::spawnRedEnemy()
{
	float xPos = origin.x + visibleSize.width;
	float yPos = (origin.y + CCRANDOM_0_1() * visibleSize.height);

	enemyRed = nullptr;
	enemyRed = Sprite::create("enemy_red.png");
	enemyRed->setPosition(xPos, yPos);
	enemyRed->setTag(2);
	setPhysicsBody(enemyRed);

	auto moveTo = MoveTo::create(calculateTime(), Vec2(origin.x, yPos));
	auto killSprite = CallFuncN::create(CC_CALLBACK_1(HelloWorld::killSprite,
			   	   	  this, true));
	auto action = Sequence::create(moveTo,
								   killSprite, nullptr);

	enemyRed->runAction(action);
	this->addChild(enemyRed, 1);
}

void HelloWorld::spawnBlueEnemy()
{
	float xPos = origin.x + visibleSize.width;
	float yPos = (origin.y + CCRANDOM_0_1() * visibleSize.height);

	enemyBlue = nullptr;
	enemyBlue = Sprite::create("enemy_blue.png");
	enemyBlue->setPosition(xPos, yPos);
	enemyBlue->setTag(1);
	setPhysicsBody(enemyBlue);

	auto moveTo = MoveTo::create(calculateTime(), Vec2(origin.x, yPos));
	auto killSprite = CallFuncN::create(CC_CALLBACK_1(HelloWorld::killSprite,
			   	   	  this, true));

	auto action = Sequence::create(moveTo,
								   killSprite, nullptr);

	enemyBlue->runAction(action);

	this->addChild(enemyBlue, 1);
}
/***************************** Touch ***********************************/
void HelloWorld::initTouch()
{
	auto listener = EventListenerTouchOneByOne::create();		// Init
	listener->onTouchBegan = [] (Touch* touch, Event* event)
		{
			return true;
		};
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::movePlayerByTouch, this);
	listener->onTouchEnded = [=] (Touch* touch, Event* event) {};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::movePlayerBlueIfPossible(float newX,float newY)
{
	float sprHalfHeight = playerBlue->getBoundingBox().size.height / 2;
	float sprHalfWidth = playerBlue->getBoundingBox().size.width / 2;

	if(newY > origin.y - sprHalfHeight && newY < visibleSize.height + sprHalfHeight)
	{
		playerBlue->setPositionY(newY);

		if(newX > origin.y + sprHalfWidth && newX < visibleSize.width)
		{
			playerBlue->setPositionX(newX);
		}
	}

}

void HelloWorld::movePlayerByTouch(Touch* touch, Event* event)
{
	auto touchLocation = touch->getLocation();
	auto lastTouchLocation = touch->getPreviousLocation();

	float lastYPos = lastTouchLocation.y;
	float lastXPos = lastTouchLocation.x;

	float currentYPos = touchLocation.y;
	float currentXPos = touchLocation.x;

	float positionDiffY =  currentYPos - lastYPos;
	float positionDiffX =  currentXPos - lastXPos;

	movePlayerBlueIfPossible(playerBlue->getPositionX() + positionDiffX, playerBlue->getPositionY() + positionDiffY);
}


/******************************* Physics  ************************************/
void HelloWorld::setPhysicsBody(cocos2d::Sprite* sprite)
{
	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
	body->setContactTestBitmask(true);
	body->setDynamic(true);
	sprite->setPhysicsBody(body);
}

void HelloWorld::setPolygonPhysicsBody(Sprite* sprite)
{
	auto body = PhysicsBody::createEdgeBox(sprite->getContentSize());	// Changed
	body->setContactTestBitmask(true);
	body->setDynamic(false);
	body->setVelocity(Vect());
	sprite->setPhysicsBody(body);

}


bool HelloWorld::onCollision(PhysicsContact& contact)
{

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if(nodeA && nodeB)
	{

		if(nodeB->getTag() == 10)
		{
			if(nodeA->getTag() == 1)
			{
				combo(*nodeA);
				dissapearBlueEnemy(*nodeA);
				nodeA->removeFromParentAndCleanup(true);
				incrementSpeed();
				incrementPoints();

			}

			else if(nodeA->getTag() == 2)
			{
				combo(*nodeA);
				dissapearRedEnemy(*nodeA);
				nodeA->removeFromParentAndCleanup(true);
				incrementSpeed();

				if (checkLife() == false) {
					Director::getInstance()->replaceScene(GameOver::createScene());
				}
			}

			else if(nodeA->getTag() == 3)
			{
				dissapearGreenLife(*nodeA);
				nodeA->removeFromParentAndCleanup(true);
				lifeUp();
			}

		}

		else if(nodeA->getTag() == 10)
		{
			if(nodeB->getTag() == 1)
			{
				combo(*nodeB);
				dissapearBlueEnemy(*nodeB);
				nodeB->removeFromParentAndCleanup(true);
				speed -= 10;
				incrementPoints();
				incrementSpeed();
			}

			else if(nodeB->getTag() == 2)
			{
				combo(*nodeB);
				dissapearRedEnemy(*nodeB);
				nodeB->removeFromParentAndCleanup(true);
				speed -= 10;

				if (checkLife() == false){
					Director::getInstance()->replaceScene(Score::createScene());
				}
			}

			else if(nodeB->getTag() == 3)
			{
				dissapearGreenLife(*nodeA);
				nodeB->removeFromParentAndCleanup(true);
				lifeUp();
			}

		}

		return false;
	}

	return true;
}

void HelloWorld::combo(const Node& node)
{
	auto fadeIn = FadeIn::create(1.0f);

	switch(node.getTag())
	{
	// Blue one
	case 1:
		comboPointStr.str("");
		comboPointStr << ++comboPoint << " Hits";
		comboBar->setTextColor(Color4B::GREEN);
		comboBar->setString(comboPointStr.str());
		comboBar->runAction(fadeIn);
		sumAdded->runAction(FadeOut::create(2.0f));
		break;

	// Red one
	case 2:
		auto fadeOut = FadeOut::create(1.0f);
		comboPointStr.str("");
		comboPointStr << "Combo Break!";
		comboBar->setTextColor(Color4B::RED);
		comboBar->setString(comboPointStr.str());
		comboBar->runAction(fadeOut);
		comboPoint = 0;
		break;
	}
}

void HelloWorld::incrementSpeed()
{
	if(speed < 550)
		speed += -5.5;
}

void HelloWorld::initPhysics()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onCollision, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

// Audio Definition soll ausgebaut werden
/************************ Audio **********************************************/
void HelloWorld::initAudio()
{
	/*SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3", true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);*/
}


/***************************** Design *****************************************/

void HelloWorld::dissapearRedEnemy(const Node& node)
{
	auto explosion = ParticleExplosion::create();
	explosion->setSpeed(500.0f);
	explosion->setStartColor(Color4F::RED);
	explosion->setEndColor(Color4F::RED);
	explosion->setPosition(node.getPosition());
	this->addChild(explosion);

}

void HelloWorld::dissapearBlueEnemy(const Node& node)
{
	auto explosion = ParticleExplosion::create();
	explosion->setSpeed(500.0f);
	explosion->setStartColor(Color4F::BLUE);
	explosion->setEndColor(Color4F::BLUE);
	explosion->setPosition(node.getPosition());
	this->addChild(explosion);

}

void HelloWorld::dissapearGreenLife(const Node& node)
{
	auto explosion = ParticleExplosion::create();
	explosion->setSpeed(500.0f);
	explosion->setStartColor(Color4F::GREEN);
	explosion->setEndColor(Color4F::GREEN);
	explosion->setPosition(node.getPosition());
	this->addChild(explosion);
}


void HelloWorld::killSprite(Node* sender, bool cleanup)
{
	sender->removeFromParentAndCleanup(cleanup);
}

bool HelloWorld::checkLife()
{
	lifeStr.str("");

	if (life > 0) {
		lifeStr << "Life: " << --life;
		lifeBar->setString(lifeStr.str());
		return true;
	}

	else
		return false;
}

bool HelloWorld::checkIfTenRedPoints()
{
	return ++redPoints % 10 == 0 ? true : false;
}

void HelloWorld::incrementPoints()
{
	auto fadeIn = FadeIn::create(1.0f);
	int sum = 100 * comboPoint;
	sumStr.str("");
	sumStr << sum;

	pointStr.str("");
	pointStr << "Points: " << (points += sum);
	pointsBar->setString(pointStr.str());

	UserDefault::getInstance()->setIntegerForKey("score", points);

	sumAdded->runAction(fadeIn);
	sumAdded->setString("+" + sumStr.str());
	this->addChild(sumAdded, 1);
}

void HelloWorld::lifeUp()
{
	lifeStr.str("");
	lifeStr << "Life: "<< ++life;
	lifeBar->setString(lifeStr.str());

	auto lifeUpSprite = Sprite::create("effects/arrowLifeUp.png");	// Lade Sprite mit dem grünen Pfeil
	lifeUpSprite->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height * 0.95f));	// Setze die Position

	auto moveTo = MoveTo::create(1.0f, Vec2(lifeUpSprite->getPositionX(), visibleSize.height)); // Setze die Position, wo sich der SPrite bewegen soll
	auto killSprite = CallFuncN::create(CC_CALLBACK_1(HelloWorld::killSprite,
			   	   	  this, true));

	auto action = Sequence::create(moveTo,
								   killSprite, NULL);

	lifeUpSprite->runAction(action);

	this->addChild(lifeUpSprite, 1);	// Added des Grünen Pfeil Sprites
}
