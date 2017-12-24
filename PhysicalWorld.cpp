#include "PhysicalWorld.h"
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

	//定义世界的边界
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width*0.8, visibleSize.height*0.8),
		PHYSICSBODY_MATERIAL_DEFAULT, 2.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	//定义小球放置的平台
	auto platform = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.4, visibleSize.height*0.7), Vec2(visibleSize.width*0.6, visibleSize.height*0.7), 
		PHYSICSBODY_MATERIAL_DEFAULT,8);
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
	auto edgeNode2 = Node::create();
	edgeNode2->setPosition(0, 0);
	edgeNode2->setPhysicsBody(bowl);
	this->addChild(edgeNode2);

	setTouchEnabled(true);
	//设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}
bool PhysicalWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 location = touch->getLocation();
	addNewSpriteAtPosition(location);
	return false;
}


void PhysicalWorld::addNewSpriteAtPosition(Vec2 p)
{
	auto sp = Sprite::create("ball.png");
	sp->setTag(1);

	auto body = PhysicsBody::createCircle(sp->getContentSize().width / 2);
	//auto body = PhysicsBody::createBox(sp->getContentSize());					
	sp->setPhysicsBody(body);
	sp->setPosition(p);
	this->addChild(sp);
}