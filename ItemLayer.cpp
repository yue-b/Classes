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


	auto front = Sprite::create("front.png");
	float scale = (visibleSize.width*visibleSize.height) / (100 * front->getContentSize().width* front->getContentSize().height);
	front->setScaleX(scale);
	front->setScaleY(scale);
	front->setPosition(Vec2(
		origin.x + visibleSize.width*0.7, 
		origin.y + visibleSize.height*0.95));
	this->addChild(front, 0);

	auto next = Sprite::create("next.png");
	next->setScaleX(scale);
	next->setScaleY(scale);
	next->setPosition(Vec2(
		origin.x + visibleSize.width*0.85,
		origin.y + visibleSize.height*0.95));
	this->addChild(next, 0);

	auto refresh = Sprite::create("refresh3.png");
	float scale1 = (visibleSize.width*visibleSize.height) / (100 * refresh->getContentSize().width* refresh->getContentSize().height);
	//AllocConsole();                                          // ���ٿ���̨
	//freopen("CONOUT$", "w", stdout);             // �ض������
	//cout <<scale1 << endl;
	refresh->setScaleX(scale1);
	refresh->setScaleY(scale1);
	refresh->setPosition(Vec2(
		origin.x + visibleSize.width*0.05,
		origin.y + visibleSize.height*0.95));
	this->addChild(refresh, 0);

	//Բ��
	DrawNode* drawNode = DrawNode::create();
	this->addChild(drawNode, 1);
	drawNode->drawDot(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200), 10, Color4F::BLACK);
	//�����ܱ߿�
	Vec2 point2[4];
	point2[0] = Vec2(visibleSize.width*0.1, visibleSize.height*0.1);
	point2[1] = Vec2(visibleSize.width*0.1, visibleSize.height*0.9);
	point2[2] = Vec2(visibleSize.width*0.9, visibleSize.height*0.9);
	point2[3] = Vec2(visibleSize.width*0.9, visibleSize.height*0.1);
	drawNode->drawSegment(point2[0], point2[1], 2, Color4F(0, 0, 0, 1));//left
	drawNode->drawSegment(point2[1], point2[2], 2, Color4F(0, 0, 0, 1));//ceiling
	drawNode->drawSegment(point2[2], point2[3], 2, Color4F(0, 0, 0, 1));//right
	drawNode->drawSegment(point2[3], point2[0], 2, Color4F(0, 0, 0, 1));//ground
	//��С����ʼλ�õ�ƽ̨
	Vec2 point1[2];
	point1[0] = Vec2(visibleSize.width*0.4, visibleSize.height*0.7);
	point1[1] = Vec2(visibleSize.width*0.6, visibleSize.height*0.7);
	drawNode->drawSegment(point1[0], point1[1], 8, Color4F(1, 1, 1, 1));//ground
	//�����λ��
	Vec2 from1 = Vec2(visibleSize.width*0.4, visibleSize.height*0.5);
	Vec2 to1 = Vec2(visibleSize.width*0.6, visibleSize.height*0.5);
	Vec2 control = Vec2(visibleSize.width*0.5, visibleSize.height*0.2);
	drawNode->drawQuadraticBezier(from1, control, to1, 1000, Color4F::WHITE);
	return true; 
}
