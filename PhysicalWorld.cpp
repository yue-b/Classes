#include <iostream>
#include "ItemLayer.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "FirstMainScene.h"
#include "BallLayer.h"
#include "PhysicalWorld.h"
#include "SuccessScene.h"
#include "FailScene.h"
#include "math.h"
using namespace std;
char num;
Layer* PhysicalWorld::createLayer()
{
	auto layer = PhysicalWorld::create();
	return layer;
}
Scene* PhysicalWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = PhysicalWorld::createLayer();
	scene->addChild(layer);
	return scene;
}
bool PhysicalWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

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


	//定义世界的边界
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width*0.8, visibleSize.height*0.8),
		PhysicsMaterial(1,0,1), 2.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

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

	//关卡1
	if (num == '1'){
		//定义小球放置的平台
		auto platform = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.4, visibleSize.height*0.7), Vec2(visibleSize.width*0.6, visibleSize.height*0.7),
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		auto edgeNode1 = Node::create();
		edgeNode1->setPosition(0, 0);
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
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		auto edgeNode2 = Node::create();
		edgeNode2->setPosition(0, 0);
		edgeNode2->setPhysicsBody(bowl);
		this->addChild(edgeNode2);

		//画小球起始位置的平台
		Vec2 point1[2];
		point1[0] = Vec2(visibleSize.width*0.4, visibleSize.height*0.7);
		point1[1] = Vec2(visibleSize.width*0.6, visibleSize.height*0.7);
		drawNode->drawSegment(point1[0], point1[1], 4, Color4F(0.44, 0.5, 0.56, 1));//ground
		//画碗的位置
		//按照二次函数画碗
		DrawNode* drawNode2 = DrawNode::create();
		for (float i = -50.0; i <= 50; i++){
			float t = i / 50.0;
			Vec2 tmp = Vec2(visibleSize.width*0.1*t + visibleSize.width*0.5, visibleSize.width*0.1*t*t + visibleSize.height*0.35);
			drawNode2->drawDot(tmp, 4, Color4F::GRAY);
		}
		this->addChild(drawNode2, 1);
		//{小球起始点坐标x = visibleSize.width*0.5+ origin.x;y = visibleSize.height*0.7+this->ball->getContentSize().height/2 + 4 + origin.y}
		this->ball = Sprite::create("ball1.png");
		auto ball_body = PhysicsBody::createCircle(ball->getContentSize().width / 2);
		ball->setPhysicsBody(ball_body);
		ball->setPosition(Vec2(
			visibleSize.width*0.5,
			visibleSize.height*0.7 + this->ball->getContentSize().height / 2 + 2));
		ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
		this->addChild(ball);

	}
	else if (num == '2'){
		//关卡2
		//定义放置小球的平台
		auto platform = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.11, visibleSize.height*0.8), Vec2(visibleSize.width*0.21, visibleSize.height*0.8),
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		auto edgeNode1 = Node::create();
		edgeNode1->setPosition(0, 0);
		edgeNode1->setPhysicsBody(platform);
		this->addChild(edgeNode1);
		//画小球起始位置的平台
		Vec2 point1[2];
		point1[0] = Vec2(visibleSize.width*0.11, visibleSize.height*0.8);
		point1[1] = Vec2(visibleSize.width*0.21, visibleSize.height*0.8);
		drawNode->drawSegment(point1[0], point1[1], 4, Color4F(0.44, 0.5, 0.56, 1));//ground


		this->ball = Sprite::create("ball1.png");
		auto ball_body = PhysicsBody::createCircle(ball->getContentSize().width / 2);
		ball->setPhysicsBody(ball_body);
		ball->setPosition(Vec2(
			visibleSize.width*0.16,
			visibleSize.height*0.8 + this->ball->getContentSize().height / 2 + 2));
		ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
		this->addChild(ball);

		//障碍物1
		auto obstacle_1 = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.3, visibleSize.height*0.85), Vec2(visibleSize.width*0.3, visibleSize.height*0.55),
			PHYSICSBODY_MATERIAL_DEFAULT, 8);
		auto edgeNode2 = Node::create();
		edgeNode2->setPosition(0, 0);
		edgeNode2->setPhysicsBody(obstacle_1);
		this->addChild(edgeNode2);
		drawNode->drawSegment(Vec2(visibleSize.width*0.3, visibleSize.height*0.85), Vec2(visibleSize.width*0.3, visibleSize.height*0.55), 8, Color4F(1, 1, 1, 1));

		//障碍物2
		auto obstacle_2 = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.5, visibleSize.height*0.6), Vec2(visibleSize.width*0.5, visibleSize.height*0.3),
			PHYSICSBODY_MATERIAL_DEFAULT, 8);
		auto edgeNode3 = Node::create();
		edgeNode3->setPosition(0, 0);
		edgeNode3->setPhysicsBody(obstacle_2);
		this->addChild(edgeNode3);
		drawNode->drawSegment(Vec2(visibleSize.width*0.5, visibleSize.height*0.6), Vec2(visibleSize.width*0.5, visibleSize.height*0.3), 8, Color4F(1, 1, 1, 1));

		//画碗的位置
		//按照二次函数画碗
		DrawNode* drawNode2 = DrawNode::create();
		for (float i = -50.0; i <= 50; i++){
			float t = i / 50.0;
			Vec2 tmp = Vec2(visibleSize.width*0.1*t + visibleSize.width*0.79, -1 * visibleSize.width*0.1*t*t + visibleSize.height*0.4);
			drawNode2->drawDot(tmp, 4, Color4F::GRAY);
		}
		this->addChild(drawNode2, 1);
		Point* points = new Point[101];
		int count = 0;
		for (float i = -50.0; i <= 50; i++){
			float t = i / 50.0;
			Point tmp = Point(visibleSize.width*0.1*t + visibleSize.width*0.79, -1 * visibleSize.width*0.1*t*t + visibleSize.height*0.4);
			points[count] = tmp;
			count++;
		}
		auto bowl = PhysicsBody::createEdgeChain(points, count,
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		auto edgeNode4 = Node::create();
		edgeNode4->setPosition(0, 0);
		edgeNode4->setPhysicsBody(bowl);
		this->addChild(edgeNode4);

		auto fire = Sprite::create("fire5.png");
		fire->setScale(visibleSize.width*0.8 / fire->getContentSize().width);
		fire->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.115));
		this->addChild(fire);
	}
	else if (num == '3'){
		//关卡三
		//定义小球放置的平台

		auto platform = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.11, visibleSize.height*0.75), Vec2(visibleSize.width*0.31, visibleSize.height*0.75),
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		platform->setCategoryBitmask(0x01);
		platform->setCollisionBitmask(0x03);
		auto edgeNode1 = Node::create();
		edgeNode1->setPosition(0, 0);
		edgeNode1->setPhysicsBody(platform);
		this->addChild(edgeNode1);
		//定义碗
		Point* points = new Point[101];
		int count = 0;
		for (float i = -50.0; i <= 50; i++){
			float t = i / 50.0;
			Point tmp = Point(visibleSize.width*0.1*t + visibleSize.width*0.79, visibleSize.width*0.1*t*t + visibleSize.height*0.11);
			points[count] = tmp;
			count++;
		}
		auto bowl = PhysicsBody::createEdgeChain(points, count,
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		bowl->setCategoryBitmask(0x01);
		bowl->setCollisionBitmask(0x03);
		auto edgeNode2 = Node::create();
		edgeNode2->setPosition(0, 0);
		edgeNode2->setPhysicsBody(bowl);
		this->addChild(edgeNode2);
		//画小球起始位置的平台
		Vec2 point1[2];
		point1[0] = Vec2(visibleSize.width*0.11, visibleSize.height*0.75 );
		point1[1] = Vec2(visibleSize.width*0.31, visibleSize.height*0.75 );
		drawNode->drawSegment(point1[0], point1[1], 4, Color4F(0.44, 0.5, 0.56, 1));//ground
		//画碗的位置
		//按照二次函数画碗
		DrawNode* drawNode2 = DrawNode::create();
		for (float i = -50.0; i <= 50; i++){
			float t = i / 50.0;
			Vec2 tmp = Vec2(visibleSize.width*0.1*t + visibleSize.width*0.79, visibleSize.width*0.1*t*t + visibleSize.height*0.11);
			drawNode2->drawDot(tmp, 4, Color4F::GRAY);
		}
		this->addChild(drawNode2, 1);
		//{小球起始点坐标x = visibleSize.width*0.5+ origin.x;y = visibleSize.height*0.7+this->ball->getContentSize().height/2 + 4 + origin.y}
		this->ball = Sprite::create("ball1.png");
		auto ball_body = PhysicsBody::createCircle(ball->getContentSize().width / 2);
		//ball_scale = 2.5;
		//ball->setScale(ball_scale);
		ball_body->setCategoryBitmask(0x02);
		ball_body->setCollisionBitmask(0X01);
		ball->setPhysicsBody(ball_body);
		ball->setPosition(Vec2(
			visibleSize.width*0.21,
			visibleSize.height*0.75 + this->ball->getContentSize().height / 2 + 25));
		ball_scale = 2.5;
		ball->setScale(ball_scale);
		ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
		this->addChild(ball);
		float length;
		length = (visibleSize.width*0.2 - ball->getContentSize().width) / 2 * 0.9;
		auto barrier1 = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.69, visibleSize.width*0.1 + visibleSize.height*0.11), Vec2(visibleSize.width*0.69 + length, visibleSize.width*0.1 + visibleSize.height*0.11),
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		barrier1->setCategoryBitmask(0x01);
		barrier1->setCollisionBitmask(0x03);
		auto edgeba1 = Node::create();
		edgeba1->setPosition(0, 0);
		edgeba1->setPhysicsBody(barrier1);
		this->addChild(edgeba1);
		Vec2 pointba1[2];
		pointba1[0] = Vec2(visibleSize.width*0.69, visibleSize.width*0.1 + visibleSize.height*0.11);
		pointba1[1] = Vec2(visibleSize.width*0.69 + length, visibleSize.width*0.1 + visibleSize.height*0.11);
		drawNode->drawSegment(pointba1[0], pointba1[1], 4, Color4F(1, 1, 1, 1));
		auto barrier2 = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.89 - length, visibleSize.width*0.1 + visibleSize.height*0.11), Vec2(visibleSize.width*0.89 + length, visibleSize.width*0.1 + visibleSize.height*0.11),
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		barrier2->setCategoryBitmask(0x01);
		barrier2->setCollisionBitmask(0x03);
		auto edgeba2 = Node::create();
		edgeba2->setPosition(0, 0);
		edgeba2->setPhysicsBody(barrier2);
		this->addChild(edgeba2);
		Vec2 pointba2[2];
		pointba2[0] = Vec2(visibleSize.width*0.89 - length, visibleSize.width*0.1 + visibleSize.height*0.11);
		pointba2[1] = Vec2(visibleSize.width*0.89, visibleSize.width*0.1 + visibleSize.height*0.11);
		drawNode->drawSegment(pointba2[0], pointba2[1], 4, Color4F(1, 1, 1, 1));
		obstacle1 = DrawNode::create();
		obstacle1->drawDot(Vec2(visibleSize.width*0.3, visibleSize.height*0.5), 10, Color4F::RED);
		this->addChild(obstacle1);
		obstacle2 = DrawNode::create();
		obstacle2->drawDot(Vec2(visibleSize.width*0.6, visibleSize.height*0.2), 10, Color4F::RED);
		this->addChild(obstacle2);
		obstacle3 = DrawNode::create();
		obstacle3->drawDot(Vec2(visibleSize.width*0.7, visibleSize.height*0.8), 10, Color4F::RED);
		this->addChild(obstacle3);
		auto barrier3 = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.5, visibleSize.height*0.2), Vec2(visibleSize.width*0.5, visibleSize.height*0.6),
			PHYSICSBODY_MATERIAL_DEFAULT, 8);
		barrier3->setCategoryBitmask(0x01);
		barrier3->setCollisionBitmask(0x03);
		auto edgeba3 = Node::create();
		edgeba3->setPosition(0, 0);
		edgeba3->setPhysicsBody(barrier3);
		this->addChild(edgeba3);
		Vec2 point3[2];
		point3[0] = Vec2(visibleSize.width*0.5, visibleSize.height*0.2);
		point3[1] = Vec2(visibleSize.width*0.5, visibleSize.height*0.6);
		drawNode->drawSegment(point3[0], point3[1], 8, Color4F(1, 1, 1, 1));
	}
 else{
	 //关卡4
	 auto platform = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.11, visibleSize.height*0.75), Vec2(visibleSize.width*0.31, visibleSize.height*0.75),
		 PHYSICSBODY_MATERIAL_DEFAULT, 8);
	 platform->setCategoryBitmask(0x01);
	 platform->setCollisionBitmask(0x03);
	 auto edgeNode1 = Node::create();
	 edgeNode1->setPosition(0, 0);
	 edgeNode1->setPhysicsBody(platform);
	 this->addChild(edgeNode1);
	 //定义碗
	 Point* points = new Point[101];
	 int count = 0;
	 for (float i = -50.0; i <= 50; i++){
		 float t = i / 50.0;
		 Point tmp = Point(visibleSize.width*0.1*t + visibleSize.width*0.79, visibleSize.width*0.1*t*t + visibleSize.height*0.11);
		 points[count] = tmp;
		 count++;
	 }
	 auto bowl = PhysicsBody::createEdgeChain(points, count,
		 PHYSICSBODY_MATERIAL_DEFAULT, 4);
	 bowl->setCategoryBitmask(0x01);
	 bowl->setCollisionBitmask(0x03);
	 auto edgeNode2 = Node::create();
	 edgeNode2->setPosition(0, 0);
	 edgeNode2->setPhysicsBody(bowl);
	 this->addChild(edgeNode2);
	 //画小球起始位置的平台
	 Vec2 point1[2];
	 point1[0] = Vec2(visibleSize.width*0.11, visibleSize.height*0.75);
	 point1[1] = Vec2(visibleSize.width*0.31, visibleSize.height*0.75);
	 drawNode->drawSegment(point1[0], point1[1], 4, Color4F(0.44, 0.5, 0.56, 1));//ground
	 //画碗的位置
	 //按照二次函数画碗
	 DrawNode* drawNode2 = DrawNode::create();
	 for (float i = -50.0; i <= 50; i++){
		 float t = i / 50.0;
		 Vec2 tmp = Vec2(visibleSize.width*0.1*t + visibleSize.width*0.79, visibleSize.width*0.1*t*t + visibleSize.height*0.11);
		 drawNode2->drawDot(tmp, 4, Color4F::GRAY);
	 }
	 this->addChild(drawNode2, 1);
	 //{小球起始点坐标x = visibleSize.width*0.5+ origin.x;y = visibleSize.height*0.7+this->ball->getContentSize().height/2 + 4 + origin.y}
	 this->ball = Sprite::create("ball1.png");
	 auto ball_body = PhysicsBody::createCircle(ball->getContentSize().width / 2);
	 ball_body->setCategoryBitmask(0x02);
	 ball_body->setCollisionBitmask(0X01);
	 ball->setPhysicsBody(ball_body);
	 ball->setPosition(Vec2(
		 visibleSize.width*0.21,
		 visibleSize.height*0.75 + this->ball->getContentSize().height / 2 + 2));
	 ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
	 this->addChild(ball);

	 auto barrier1 = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.50, visibleSize.height*0.40), Vec2(visibleSize.width*0.50, visibleSize.height*0.60),
		 PHYSICSBODY_MATERIAL_DEFAULT, 8);

	 barrier1->setCategoryBitmask(0x01);
	 barrier1->setCollisionBitmask(0x03);
	 auto edgeba1 = Node::create();
	 edgeba1->setPosition(0, 0);
	 edgeba1->setPhysicsBody(barrier1);
	 this->addChild(edgeba1);
	 Vec2 pointB1[2];
	 pointB1[0] = Vec2(visibleSize.width*0.50, visibleSize.height*0.40);
	 pointB1[1] = Vec2(visibleSize.width*0.50, visibleSize.height*0.60);
	 drawNode->drawSegment(pointB1[0], pointB1[1], 8, Color4F(1, 1, 1, 1));


	 DrawNode* fall1 = DrawNode::create();
	 fall1->drawDot(Vec2(visibleSize.width*0.73, visibleSize.height*0.7), 10, Color4F::RED);
	 Node* fallNode1 = (Node*)fall1;
	 auto fall1_body = PhysicsBody::createCircle(10, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(visibleSize.width*0.73, visibleSize.height*0.7));
	 fall1_body->setCategoryBitmask(0x01);
	 fall1_body->setCollisionBitmask(0x03);
	 fallNode1->setPhysicsBody(fall1_body);
	 this->addChild(fallNode1);

	 DrawNode* fall2 = DrawNode::create();
	 fall2->drawDot(Vec2(visibleSize.width*0.75, visibleSize.height*0.71), 10, Color4F::RED);
	 Node* fallNode2 = (Node*)fall2;
	 auto fall2_body = PhysicsBody::createCircle(10, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(visibleSize.width*0.75, visibleSize.height*0.71));
	 fall2_body->setCategoryBitmask(0x01);
	 fall2_body->setCollisionBitmask(0x03);
	 fallNode2->setPhysicsBody(fall2_body);
	 this->addChild(fallNode2);

	 DrawNode* fall3 = DrawNode::create();
	 fall3->drawDot(Vec2(visibleSize.width*0.77, visibleSize.height*0.7), 10, Color4F::RED);
	 Node* fallNode3 = (Node*)fall3;
	 auto fall3_body = PhysicsBody::createCircle(10, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(visibleSize.width*0.77, visibleSize.height*0.7));
	 fall3_body->setCategoryBitmask(0x01);
	 fall3_body->setCollisionBitmask(0x03);
	 fallNode3->setPhysicsBody(fall3_body);
	 this->addChild(fallNode3);

	 DrawNode* fall4 = DrawNode::create();
	 fall4->drawDot(Vec2(visibleSize.width*0.79, visibleSize.height*0.72), 10, Color4F::RED);
	 Node* fallNode4 = (Node*)fall4;
	 auto fall4_body = PhysicsBody::createCircle(10, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(visibleSize.width*0.79, visibleSize.height*0.72));
	 fall4_body->setCategoryBitmask(0x01);
	 fall4_body->setCollisionBitmask(0x03);
	 fallNode4->setPhysicsBody(fall4_body);
	 this->addChild(fallNode4);

	 DrawNode* fall5 = DrawNode::create();
	 fall5->drawDot(Vec2(visibleSize.width*0.82, visibleSize.height*0.72), 10, Color4F::RED);
	 Node* fallNode5 = (Node*)fall5;
	 auto fall5_body = PhysicsBody::createCircle(10, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(visibleSize.width*0.82, visibleSize.height*0.72));
	 fall5_body->setCategoryBitmask(0x01);
	 fall5_body->setCollisionBitmask(0x03);
	 fallNode5->setPhysicsBody(fall5_body);
	 this->addChild(fallNode5);

	 DrawNode* fall6 = DrawNode::create();
	 fall6->drawDot(Vec2(visibleSize.width*0.8, visibleSize.height*0.74), 10, Color4F::RED);
	 Node* fallNode6 = (Node*)fall6;
	 auto fall6_body = PhysicsBody::createCircle(10, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(visibleSize.width*0.8, visibleSize.height*0.74));
	 fall6_body->setCategoryBitmask(0x01);
	 fall6_body->setCollisionBitmask(0x03);
	 fallNode6->setPhysicsBody(fall6_body);
	 this->addChild(fallNode6);

	 DrawNode* fall7 = DrawNode::create();
	 fall7->drawDot(Vec2(visibleSize.width*0.78, visibleSize.height*0.75), 10, Color4F::RED);
	 Node* fallNode7 = (Node*)fall7;
	 auto fall7_body = PhysicsBody::createCircle(10, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(visibleSize.width*0.78, visibleSize.height*0.75));
	 fall7_body->setCategoryBitmask(0x01);
	 fall7_body->setCollisionBitmask(0x03);
	 fallNode7->setPhysicsBody(fall7_body);
	 this->addChild(fallNode7);
 }



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

	auto backToCheckpoint = MenuItemImage::create(
		"menu3.png",
		"menu3.png",
		CC_CALLBACK_1(PhysicalWorld::back, this));
	backToCheckpoint->setScale(scale1);
	backToCheckpoint->setPosition(Vec2(origin.x + visibleSize.width*0.2, origin.y + visibleSize.height*0.95));


	Menu*mu = Menu::create(settingMenuItem, settingMenuItem2, settingMenuItem3,backToCheckpoint, NULL);
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
	//AllocConsole();                                          // 开辟控制台
	//freopen("CONOUT$", "w", stdout);             // 重定向输出
	//cout << "mouse up" << endl;
	//根据createEdgeChain画曲线（但是无法受重力影响）
	if (!this->points.empty()){
		auto world = this->getScene()->getPhysicsWorld();
		Point* tmp = new Point[this->points.size()];
		int len = 0;
		for (list<Point>::iterator i = this->points.begin(); i != (--this->points.end()); i++){
			tmp[len++] = Point(i->x, i->y);
		}
		this->points.clear();
		/*DrawNode* drawNode2 = DrawNode::create();
		for (int j = 0; j < len - 1; j++){
			Vec2 from = Vec2(tmp[j].x, tmp[j].y);
			int m = j + 1;
			Vec2 to = Vec2(tmp[m].x, tmp[m].y);
			drawNode2->drawSegment(from, to, 4, Color4F::BLACK);
		}
		auto line = PhysicsBody::createEdgeChain(tmp, len,
			PHYSICSBODY_MATERIAL_DEFAULT, 4);
		//line->setGravityEnable(true);
		//line->setCollisionBitmask(0x01);
		Node* lineNode = (Node*)drawNode2;
		lineNode->setPosition(0, 0);
		
		lineNode->setPhysicsBody(line);*/
		/*AllocConsole();                                          // 开辟控制台
		freopen("CONOUT$", "w", stdout);             // 重定向输出*/
		//cout << tmp[0].x - tmp[len].x << endl;
		DrawNode* drawNode2 = DrawNode::create();
		drawNode2->drawSegment(Vec2(tmp[0].x, tmp[0].y), Vec2(tmp[len - 1].x, tmp[len - 1].y), 4, Color4F::BLACK);
		//auto line = PhysicsBody::createBox(Size(100, 100), PHYSICSBODY_MATERIAL_DEFAULT);
		Point* tmp2 = new Point[5];
		if (tmp[0].x == tmp[len - 1].x){
			tmp[0].x += 10;
		}
		if (tmp[0].x > tmp[len - 1].x){
			Point a = tmp[0];
			tmp[0] = tmp[len - 1];
			tmp[len - 1] = a;
		}
		tmp2[3] = Point(tmp[0].x, tmp[0].y);
		tmp2[2] = Point(tmp[len - 1].x, tmp[len - 1].y);
		tmp2[1] = Point(tmp[len - 1].x, tmp[len - 1].y + 2);
		tmp2[0] = Point(tmp[0].x, tmp[0].y + 2);

		
		//auto line = PhysicsBody::createBox(Size(100,100));
		auto line = PhysicsBody::createPolygon(tmp2, 4, PhysicsMaterial(1,0,1));
		line->setGravityEnable(false);
		//drawNode2->drawSegment(Vec2(tmp[0].x, tmp[0].y), Vec2(tmp[len-2].x, tmp[len-2].y), 4,Color4F::BLACK);
		//auto line = PhysicsBody::createBox(Size(tmp[0].x-tmp[len-2].x,4),PHYSICSBODY_MATERIAL_DEFAULT);
		Node* lineNode = (Node*)drawNode2;
		//lineNode->setPosition(0, 0);
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

bool isInBowlBottom(Point point){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//cout << point.x << "," << point.y << endl;
	//cout << "x:"<<visibleSize.width*0.5 - visibleSize.width*0.1*0.2 << "," << visibleSize.width*0.5 + visibleSize.width*0.1*0.2 << endl;
	//cout << "y:" << pow((point.x - visibleSize.width*0.5) / (visibleSize.width*0.1), 2)*visibleSize.width + visibleSize.height*0.35 << "," << (pow(0.2, 2)* visibleSize.width + visibleSize.height*0.35)<< endl;
	//关卡1碗底位置
	if (num == '1'){
		if (point.x > visibleSize.width*0.5 - visibleSize.width*0.1*0.2
			&&point.x < visibleSize.width*0.5 + visibleSize.width*0.1*0.2){
			float y = pow((point.x - visibleSize.width*0.5) / (visibleSize.width*0.1), 2)*visibleSize.width + visibleSize.height*0.35;
			if (point.y - 16>y&&point.y + 16 < (pow(0.2, 2)* visibleSize.width + visibleSize.height*0.35))
				return true;
		}
	}
	else if (num == '2'){
		//关卡2碗底位置
		if (point.x > visibleSize.width*0.79 - visibleSize.width*0.1*0.2
			&&point.x < visibleSize.width*0.79 + visibleSize.width*0.1*0.2){
			float y = -1 * pow((point.x - visibleSize.width*0.79) / (visibleSize.width*0.1), 2)*visibleSize.width + visibleSize.height*0.4;
			if (point.y + 16<y&&point.y - 16 > (-1 * pow(0.2, 2)* visibleSize.width + visibleSize.height*0.4))
				return true;
		}
	}
	else{
		//关卡3碗底位置	//关卡4碗底位置
		if (point.x > visibleSize.width*0.79 - visibleSize.width*0.1*0.2
			&&point.x < visibleSize.width*0.79 + visibleSize.width*0.1*0.2){
			float y = pow((point.x - visibleSize.width*0.79) / (visibleSize.width*0.1), 2)*visibleSize.width + visibleSize.height*0.11;
			if (point.y - 16>y&&point.y + 16 < (pow(0.2, 2)* visibleSize.width + visibleSize.height*0.11))
				return true;
		}
	}
	
	return false;
}
void PhysicalWorld::back(CCObject* pSender)
{
	//本场景出栈
	CCDirector::sharedDirector()->popScene();
}
void PhysicalWorld::update(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Point start = Point(visibleSize.width*0.5 - 20, visibleSize.height*0.35 - 20);
	Rect rect = Rect(start.x, start.y,40, 40);
	//bool isSuccess = rect.containsPoint(this->ball->getPosition());
	if (num == '2'){
		Point ball_point = this->ball->getPosition();
		if (ball_point.y <= visibleSize.height*0.135){
			auto failScene = FailScene::scene();
			CCDirector::sharedDirector()->pushScene(failScene);
		}
	}
	if (num == '3'){
		//关卡三
		Point ball = this->ball->getPosition();
		//cout << "ball:" << ball.x << ',' << ball.y << endl; 

		Point ob1 = Vec2(visibleSize.width*0.3, visibleSize.height*0.5);
		Point ob2 = Vec2(visibleSize.width*0.6, visibleSize.height*0.2);
		Point ob3 = Vec2(visibleSize.width*0.7, visibleSize.height*0.8);
		float dist1 = ball.getDistance(ob1);
		float dist2 = ball.getDistance(ob2);
		float dist3 = ball.getDistance(ob3);

		//cout <<"dist1:"<< dist1 << endl;
		float temp = this->ball->getContentSize().width / 2;
		//cout << "temp" << temp << endl;
		if ((dist1 <= temp* ball_scale + 10) && flag1 == 0){
			//cout << ball_scale << endl;
			flag1 = 1;
			this->removeChild(obstacle1);
			ball_scale = ball_scale - 0.5;
			this->ball->setScale(ball_scale);
		}
		else if ((dist2 <= temp* ball_scale + 10) && flag2 == 0)
		{
			flag2 = 1;
			this->removeChild(obstacle2);
			ball_scale = ball_scale - 0.5;
			this->ball->setScale(ball_scale);

		}
		else if ((dist3 <= temp* ball_scale + 10) && flag3 == 0)
		{
			flag3 = 1;
			this->removeChild(obstacle3);
			ball_scale = ball_scale - 0.5;
			this->ball->setScale(ball_scale);

		}
	}
	bool flag = isInBowlBottom(this->ball->getPosition());
	auto successScene = SuccessScene::scene();
	if (flag){
		freshCallback(this);
		CCDirector::sharedDirector()->pushScene(successScene);
	}
}

void  PhysicalWorld::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags){
	/*AllocConsole();                                          // 开辟控制台
	freopen("CONOUT$", "w", stdout);             // 重定向输出
	cout << "draw" << endl;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("background2.jpg");
	//sprite->setPosition(Vec2(
	//	visibleSize.width / 2 + origin.x,
	//	visibleSize.height / 2 + origin.y));
	//float t1 = visibleSize.width / (sprite->getContentSize()).width;
	//float t2 = visibleSize.height / (sprite->getContentSize()).height;
	//float m = MAX(t1, t2);
	//sprite->setScaleX(visibleSize.width / (sprite->getContentSize()).width);
	//sprite->setScaleY(visibleSize.height / (sprite->getContentSize()).height);
	//sprite->setZOrder(999);
	Mat4 matrix = Mat4();
	matrix.scale(
		visibleSize.width / sprite->getContentSize().width, 
		visibleSize.height / sprite->getContentSize().height, 1.);
	sprite->draw(renderer, matrix, flags);
	sprite->setZOrder(-1);
	//this->addChild(sprite);

	auto array = PointArray::create(10);
	ccDrawColor4B(255,255,255,255);
	glLineWidth(20);
	ccDrawLine(Vec2(100, 100), Vec2(900, 100));
	ccDrawLine(Vec2(100, 100), Vec2(100, 600));
	array->addControlPoint(Vec2(100, 100));
	array->addControlPoint(Vec2(10, 10));
	array->addControlPoint(Vec2(200, 200));
	array->addControlPoint(Vec2(400, 400));
	array->addControlPoint(Vec2(500, 500));
	ccDrawCardinalSpline(array, 0, 100);

		//ccDrawLine(Vec2(100, 100), Vec2(900, 100));
		//ccDrawLine(Vec2(100, 100), Vec2(100, 600));
		//array->addControlPoint(Vec2(100, 100));
	//if (!this->points.empty()){
		//auto array = PointArray::create(this->points.size());
		//PointArray
		//ccDrawCardinalSpline(this->points, 0, 100);
	//}
	cout << "draw end" << endl;*/
}


