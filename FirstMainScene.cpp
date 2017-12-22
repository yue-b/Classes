#include "FirstMainScene.h"
#include "math.h"

USING_NS_CC;

Layer* FirstMain::createLayer()
{

	// 'layer' is an autorelease object
	auto layer = FirstMain::create();

	// return the scene
	return layer;
}

// on "init" you need to initialize your instance
bool FirstMain::init()
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
	//auto layer = Layer::create("background.jpg");
	auto sprite = Sprite::create("background2.jpg");
	sprite->setPosition(Vec2(
		visibleSize.width / 2 + origin.x, 
		visibleSize.height / 2 + origin.y));
	float t1 = visibleSize.width / (sprite->getContentSize()).width;
	float t2 = visibleSize.height / (sprite->getContentSize()).height;
	float m = MAX(t1, t2);
	//sprite->setScaleX(m);
	//sprite->setScaleY(m);
	sprite->setScaleX(visibleSize.width / (sprite->getContentSize()).width);
	sprite->setScaleY(visibleSize.height / (sprite->getContentSize()).height);



	this->addChild(sprite, 0);

	return true;
}



