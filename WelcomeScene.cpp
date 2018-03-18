#include "WelcomeScene.h"
#include "Checkpoint.h"
#include "math.h"

USING_NS_CC;

Layer* Welcome::createLayer()
{

	// 'layer' is an autorelease object
	auto layer = Welcome::create();

	// return the scene
	return layer;
}

// on "init" you need to initialize your instance
bool Welcome::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//加载背景图片
	auto sprite = Sprite::create("background2.jpg");
	sprite->setPosition(Vec2(
		visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 + origin.y));
	float t1 = visibleSize.width / (sprite->getContentSize()).width;
	float t2 = visibleSize.height / (sprite->getContentSize()).height;
	float m = MAX(t1, t2);
	sprite->setScaleX(visibleSize.width / (sprite->getContentSize()).width);
	sprite->setScaleY(visibleSize.height / (sprite->getContentSize()).height);
	this->addChild(sprite, -1);
	//加载游戏标题
	auto title = Sprite::create("title1.png");
	title->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+150));
	this->addChild(title);
	//加载开始游戏按钮
	auto startItem = MenuItemImage::create(
		"cloud1.png",
		"cloud1.png",
		CC_CALLBACK_1(Welcome::startPlay, this));
	startItem->setScaleX(0.3);
	startItem->setScaleY(0.3);
	startItem->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2));
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 0);
	return true;
}
void Welcome::startPlay(Ref* pSender){
	auto checkpointScene = Checkpoint::scene();
	CCDirector::sharedDirector()->pushScene(checkpointScene);
}



