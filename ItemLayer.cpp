#include "ItemLayer.h"

USING_NS_CC;

Layer* ItemLayer::createLayer()
{

	// 'layer' is an autorelease object
	auto layer = ItemLayer::create();


	// return the scene
	return layer;
}

// on "init" you need to initialize your instance
bool ItemLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto front = Sprite::create("front.png");
	front->setScaleX(0.2);
	front->setScaleY(0.2);
	front->setPosition(Vec2(
		origin.x + visibleSize.width*0.8, 
		origin.y + visibleSize.height*0.95));
	this->addChild(front, 0);

	auto next = Sprite::create("next.png");
	next->setScaleX(0.2);
	next->setScaleY(0.2);
	next->setPosition(Vec2(
		origin.x + visibleSize.width*0.85,
		origin.y + visibleSize.height*0.95));
	this->addChild(next, 0);

	auto refresh = Sprite::create("refresh.png");
	refresh->setScaleX(0.2);
	refresh->setScaleY(0.2);
	refresh->setPosition(Vec2(
		origin.x + visibleSize.width*0.9,
		origin.y + visibleSize.height*0.95));
	this->addChild(refresh, 0);

	return true;
}
