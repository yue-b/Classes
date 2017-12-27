#include "BallLayer.h"
#include <iostream>
#include "math.h"
using namespace std;

USING_NS_CC;

Layer* BallLayer::createLayer()
{

	// 'layer' is an autorelease object
	auto layer = BallLayer::create();

	// return the scene
	return layer;
}

// on "init" you need to initialize your instance
bool BallLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//AllocConsole();                                          // 开辟控制台
	//freopen("CONOUT$", "w", stdout);             // 重定向输出
	//cout << "in" << endl;
	/////////////////////////////
	// 3. add your codes below...
	//{小球起始点坐标x = visibleSize.width*0.5+ origin.x;y = visibleSize.height*0.7+this->ball->getContentSize().height/2 + 4 + origin.y}
	this->ball = Sprite::create("ball1.png");
	ball->setTag(1);
	auto body = PhysicsBody::createCircle(ball->getContentSize().width / 2);
	body->setCategoryBitmask(0x02);
	body->setCollisionBitmask(0X01);
	ball->setPhysicsBody(body);
	ball->setPosition(Vec2(
		visibleSize.width*0.5,
		visibleSize.height*0.7 + this->ball->getContentSize().height / 2 + 4));
	ball->getPhysicsBody()->setVelocity(Vec2(50, 0));
	this->addChild(ball);

	return true;
}