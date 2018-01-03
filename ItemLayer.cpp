#include "ItemLayer.h"
#include <iostream>
using namespace std;
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


	
	DrawNode* drawNode = DrawNode::create();
	this->addChild(drawNode, 1);
	//画四周边框
	Vec2 point2[4];
	point2[0] = Vec2(visibleSize.width*0.1, visibleSize.height*0.1);
	point2[1] = Vec2(visibleSize.width*0.1, visibleSize.height*0.9);
	point2[2] = Vec2(visibleSize.width*0.9, visibleSize.height*0.9);
	point2[3] = Vec2(visibleSize.width*0.9, visibleSize.height*0.1);
	drawNode->drawSegment(point2[0], point2[1], 2, Color4F(0, 0, 0, 1));//left
	drawNode->drawSegment(point2[1], point2[2], 2, Color4F(0, 0, 0, 1));//ceiling
	drawNode->drawSegment(point2[2], point2[3], 2, Color4F(0, 0, 0, 1));//right
	drawNode->drawSegment(point2[3], point2[0], 2, Color4F(0, 0, 0, 1));//ground
	//画小球起始位置的平台
	Vec2 point1[2];
	point1[0] = Vec2(visibleSize.width*0.4, visibleSize.height*0.7);
	point1[1] = Vec2(visibleSize.width*0.6, visibleSize.height*0.7);
	drawNode->drawSegment(point1[0], point1[1], 8, Color4F(1, 1, 1, 1));//ground
	//画碗的位置
	//按照二次函数画碗
	DrawNode* drawNode2 = DrawNode::create();
	for (float i = -50.0; i <= 50; i++){
		float t = i / 50.0;
		Vec2 tmp = Vec2(visibleSize.width*0.1*t + visibleSize.width*0.5, visibleSize.width*0.1*t*t + visibleSize.height*0.35);
		drawNode2->drawDot(tmp, 4, Color4F::GRAY);
	}
	this->addChild(drawNode2, 1);
	return true; 
}
