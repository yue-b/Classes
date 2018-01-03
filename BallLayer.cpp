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
	auto body = PhysicsBody::createCircle(ball->getContentSize().width / 2);
	body->setCategoryBitmask(0x02);
	body->setCollisionBitmask(0X01);
	ball->setPhysicsBody(body);
	ball->setPosition(Vec2(
		visibleSize.width*0.5,
		visibleSize.height*0.7 + this->ball->getContentSize().height / 2 + 4));
	ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
	this->addChild(ball);

	auto ball_listener = EventListenerMouse::create();
	//分发MouseMove事件
	ball_listener->onMouseDown = CC_CALLBACK_1(BallLayer::mousedown, this);
	ball_listener->onMouseUp = CC_CALLBACK_1(BallLayer::mouseup, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ball_listener, ball);
	//listener->setEnabled(false);
	return true;
}

void BallLayer::mousedown(Event* event){
	/* 获取事件所绑定的 target */
	auto target = event->getCurrentTarget();
	Size ball = target->getContentSize();
	Vec2 ball_location = target->getPosition();
	Rect rect = Rect(ball_location.x-ball.width/2, ball_location.y-ball.height/2, ball.width, ball.height);
	EventMouse* e = (EventMouse*)event;
	float x = e->getCursorX();
	float y = e->getCursorY();
	cout << "x:" << x << " y:" << y << endl;
	bool isClicked = rect.containsPoint(Point(e->getCursorX(), e->getCursorY()));
	cout << rect.getMinX() <<","<< rect.getMaxX() << endl;
	cout << "x:" << x << " y:" << y << endl;
	cout << "isClicked:"<<isClicked << endl;
	if (isClicked){
		//Node* tmp = Director::getInstance()->getRunningScene()->getChildByTag(5);
		//this->removeChildByTag(5, true);
		//Director::getInstance()->getRunningScene()->getEventDispatcher()->pauseEventListenersForTarget(tmp);
		from_point = Point(ball_location.x, ball_location.y);

	}
}
void BallLayer::mouseup(Event* event){
	EventMouse* e = (EventMouse*)event;
	float x = e->getCursorX();
	float y = e->getCursorY();
	to_point = Point(x, y);
	DrawNode* draw = DrawNode::create();
	draw->drawSegment(from_point, to_point, 6, Color4F::ORANGE);
	this->addChild(draw);
}