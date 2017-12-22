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

	//圆点
	DrawNode* drawNode = DrawNode::create();
	this->addChild(drawNode, 1);
	drawNode->drawDot(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200), 10, Color4F::BLACK);
	//多边形
	Vec2 point2[4];
	point2[0] = Vec2(80, 50);
	point2[1] = Vec2(80, 680);
	point2[2] = Vec2(1000, 680);
	point2[3] = Vec2(1000, 50);
	drawNode->drawPolygon(point2, 4, Color4F(1, 0, 0, 0), 2, Color4F(0, 1, 0, 1));//1000透明

	Vec2 point1[4];
	point1[0] = Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 + 180);
	point1[1] = Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 + 190);
	point1[2] = Vec2(visibleSize.width / 2 + 80, visibleSize.height / 2 + 190);
	point1[3] = Vec2(visibleSize.width / 2 + 80, visibleSize.height / 2 + 180);
	drawNode->drawPolygon(point1, 4, Color4F(0, 1, 0, 1), 1, Color4F(0, 1, 0, 1));


	return true;
}
