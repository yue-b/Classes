#include <iostream>
#include "ItemLayer.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "FirstMainScene.h"
#include "BallLayer.h"
#include "PhysicalWorld.h"
#include "SuccessScene.h"
using namespace std;
Layer* PhysicalWorld::createLayer()
{
	auto layer = PhysicalWorld::create();
	return layer;
}
bool PhysicalWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//AllocConsole();                                          // 开辟控制台
	//freopen("CONOUT$", "w", stdout);             // 重定向输出

	//定义世界的边界
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width*0.8, visibleSize.height*0.8),
		PHYSICSBODY_MATERIAL_DEFAULT, 2.0f);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x03);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	//定义小球放置的平台
	auto platform = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.4, visibleSize.height*0.7), Vec2(visibleSize.width*0.6, visibleSize.height*0.7), 
		PHYSICSBODY_MATERIAL_DEFAULT,8);
	platform->setCategoryBitmask(0x01);
	platform->setCollisionBitmask(0x03);
	auto edgeNode1 = Node::create();
	edgeNode1->setPosition(0,0);
	edgeNode1->setPhysicsBody(platform);
	this->addChild(edgeNode1);
	//定义碗
	Point* points = new Point[101];
	int count = 0;
	for (float i = -50.0; i <= 50; i++){
		float t = i / 50.0;
		Point tmp = Point(visibleSize.width*0.1*t + visibleSize.width*0.5, visibleSize.width*0.1*t*t + visibleSize.height*0.35);
		points[count] = tmp;
		count++;
	}
	auto bowl = PhysicsBody::createEdgeChain(points, count, 
		PHYSICSBODY_MATERIAL_DEFAULT,4);
	bowl->setCategoryBitmask(0x01);
	bowl->setCollisionBitmask(0x03);
	auto edgeNode2 = Node::create();
	edgeNode2->setPosition(0, 0);
	edgeNode2->setPhysicsBody(bowl);
	this->addChild(edgeNode2);

	// 1.//创建一个精灵
	auto MainNode = Node::create();
	MainNode->setTag(5);
	MainNode->setPosition(visibleSize.width*0.2, visibleSize.height*0.5);
	this->addChild(MainNode);

	//创建鼠标监听
	listener = EventListenerMouse::create();
	//分发MouseMove事件

	listener->onMouseMove = CC_CALLBACK_1(PhysicalWorld::mousemove, this);
	listener->onMouseDown = CC_CALLBACK_1(PhysicalWorld::mousedown, this);
	listener->onMouseUp = CC_CALLBACK_1(PhysicalWorld::mouseup, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, MainNode);

	
	// 3. add your codes below...
	//{小球起始点坐标x = visibleSize.width*0.5+ origin.x;y = visibleSize.height*0.7+this->ball->getContentSize().height/2 + 4 + origin.y}
	this->ball = Sprite::create("ball1.png");
	auto ball_body = PhysicsBody::createCircle(ball->getContentSize().width / 2);
	ball_body->setCategoryBitmask(0x02);
	ball_body->setCollisionBitmask(0X01);
	ball->setPhysicsBody(ball_body);
	ball->setPosition(Vec2(
		visibleSize.width*0.5,
		visibleSize.height*0.7 + this->ball->getContentSize().height / 2 + 4));
	ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
	this->addChild(ball);

	this->ball_listener = EventListenerMouse::create();
	//分发MouseMove事件
	//ball_listener->onMouseDown = CC_CALLBACK_1(PhysicalWorld::balldown, this);
	ball_listener->onMouseUp = CC_CALLBACK_1(PhysicalWorld::ballup, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ball_listener, ball);

	//
	MenuItemImage *settingMenuItem = MenuItemImage::create(
		"front.png",
		"frontSelected.png",
		CC_CALLBACK_1(PhysicalWorld::frontCallback, this));
	auto front = Sprite::create("front.png");
	float scale = (visibleSize.width*visibleSize.height) / (100 * front->getContentSize().width* front->getContentSize().height);
	settingMenuItem->setScaleX(scale);
	settingMenuItem->setScaleY(scale);
	settingMenuItem->setPosition(Vec2(
		origin.x + visibleSize.width*0.7,
		origin.y + visibleSize.height*0.95));
	//this->addChild(front, 0);

	MenuItemImage *settingMenuItem2 = MenuItemImage::create(
		"next.png",
		"nextSelected.png",
		CC_CALLBACK_1(PhysicalWorld::nextCallback, this));
	auto next = Sprite::create("next.png");
	settingMenuItem2->setScaleX(scale);
	settingMenuItem2->setScaleY(scale);
	settingMenuItem2->setPosition(Vec2(
		origin.x + visibleSize.width*0.85,
		origin.y + visibleSize.height*0.95));
	//this->addChild(next, 0);


	MenuItemImage *settingMenuItem3 = MenuItemImage::create(
		"refresh3.png",
		"refreshSelected.png",
		CC_CALLBACK_1(PhysicalWorld::freshCallback, this));
	auto refresh = Sprite::create("refresh3.png");
	float scale1 = (visibleSize.width*visibleSize.height) / (100 * refresh->getContentSize().width* refresh->getContentSize().height);
	settingMenuItem3->setScaleX(scale1);
	settingMenuItem3->setScaleY(scale1);
	settingMenuItem3->setPosition(Vec2(
		origin.x + visibleSize.width*0.05,
		origin.y + visibleSize.height*0.95));
	Menu*mu = Menu::create(settingMenuItem, settingMenuItem2, settingMenuItem3, NULL);
	mu->setPosition(Point::ZERO);
	this->addChild(mu, 0);

	scheduleUpdate();
	return true;
}

void PhysicalWorld::mousemove(Event* event)
{
	//cout << "mouse in" << endl;
	EventMouse* e = (EventMouse*)event;
	if (e->getMouseButton() == 0){
	float x = e->getCursorX();
    float y = e->getCursorY();

	/*auto point = Node::create();
	auto body = PhysicsBody::createCircle(2);
	DrawNode* node = DrawNode::create();
	node->drawDot(Vec2(x,y),5,Color4F::BLUE);
	this->addChild(node);
	point->setPhysicsBody(body);
	point->setPosition(Vec2(x, y));
	this->addChild(point);*/
	this->points.push_back(Point(x, y));
	//cout << x << "," << y << endl;
	}

}
void PhysicalWorld::mousedown(Event* event){
	EventMouse* e = (EventMouse*)event;
	float x = e->getCursorX();
	float y = e->getCursorY();
	Size ball = this->ball->getContentSize();
	Vec2 ball_location = this->ball->getPosition();
	//cout << "ball_location:"<<ball_location.x << ball_location.y << endl;
	Rect rect = Rect(ball_location.x - ball.width / 2, ball_location.y - ball.height / 2, ball.width, ball.height);
	bool isClicked = rect.containsPoint(Point(e->getCursorX(), e->getCursorY()));
	if (isClicked){
		//cout << "click ball" << endl;
		from_point = Point(ball_location.x, ball_location.y);
		this->listener->setEnabled(false);
	}
	else{
		//cout << "not ball" << endl;
		this->ball_listener->setEnabled(false);
	}
}
void PhysicalWorld::mouseup(Event* event){
	EventMouse* e = (EventMouse*)event;
	float x = e->getCursorX();
	float y = e->getCursorY();
	//根据createEdgeChain画曲线（但是无法受重力影响）
	if (!this->points.empty()){
		auto world = this->getScene()->getPhysicsWorld();
		Point* tmp = new Point[this->points.size()];
		int len = 0;
		for (list<Point>::iterator i = this->points.begin(); i != (--this->points.end()); i++){
			tmp[len++] = Point(i->x, i->y);
		}
		this->points.clear();
		DrawNode* drawNode2 = DrawNode::create();
		for (int j = 0; j < len - 1; j++){
			Vec2 from = Vec2(tmp[j].x, tmp[j].y);
			int m = j + 1;
			Vec2 to = Vec2(tmp[m].x, tmp[m].y);
			drawNode2->drawSegment(from, to, 4, Color4F::BLACK);
		}
		auto line = PhysicsBody::createEdgeChain(tmp, len,
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		Node* lineNode = (Node*)drawNode2;
		lineNode->setPosition(0, 0);
		lineNode->setPhysicsBody(line);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		if (y <= visibleSize.height*0.9){
			front.pushBack(lineNode);
			this->addChild(lineNode);
		}

	}
	this->ball_listener->setEnabled(true);

	//cout << "ball_listener true" << endl;
}
void PhysicalWorld::ballup(Event* event){
	EventMouse* e = (EventMouse*)event;
	float x = e->getCursorX();
	float y = e->getCursorY();
	to_point = Point(x, y);
	/*DrawNode* draw = DrawNode::create();
	draw->drawSegment(from_point, to_point, 6, Color4F::ORANGE);
	this->addChild(draw);*/
	this->ball->getPhysicsBody()->setVelocity(Vec2(to_point.x - from_point.x, to_point.y - from_point.y));
	this->listener->setEnabled(true);
}
//刷新事件
void PhysicalWorld::freshCallback(Ref* pSender)
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto firstLayer = FirstMain::createLayer();
	auto itemLayer = ItemLayer::createLayer();
	//auto ballLayer = BallLayer::createLayer();
	auto physicalWorld = PhysicalWorld::createLayer();
	scene->addChild(firstLayer, 0);
	scene->addChild(itemLayer, 1);
	//scene->addChild(ballLayer, 2);
	scene->addChild(physicalWorld, 2);
	CCDirector::sharedDirector()->replaceScene(scene);

}
//前一步事件
void PhysicalWorld::frontCallback(Ref* pSender)
{
	//cout << "frontCallback" << endl;
	if (!front.empty()) {
		Node* node = front.back();
		nextforward.pushBack(node);
		this->removeChild(node);
		front.popBack();
	}

}
//后一步事件
void PhysicalWorld::nextCallback(Ref* pSender)
{
	//cout << "nextCallback" << endl;
	if (!nextforward.empty()) {
		//cout << nextforward.size() << endl;
		Node* node = nextforward.back();
		this->addChild(node);
		front.pushBack(node);
		nextforward.popBack();
	}
}

void PhysicalWorld::update(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Point start = Point(visibleSize.width*0.5 - 20, visibleSize.height*0.35 - 20);
	Rect rect = Rect(start.x, start.y,40, 40);
	bool isSuccess = rect.containsPoint(this->ball->getPosition());
	auto successScene = SuccessScene::scene();
	
	if (isSuccess){
		freshCallback(this);
		CCDirector::sharedDirector()->pushScene(successScene);
	}
}

