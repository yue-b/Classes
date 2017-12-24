#include "test.h"
#define RED_BIT_MASK    0x2
Scene* test::createScene()
{
	auto scene = Scene::createWithPhysics();								
		//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

		auto layer = test::create();

	scene->addChild(layer);

	return scene;
}
bool test::init()
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
	edgeNode->setColor(Color3B(0, 0, 0));
	edgeNode->getPhysicsBody()->setContactTestBitmask(RED_BIT_MASK);
	
	this->addChild(edgeNode); 										


	setTouchEnabled(true);											
	//设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);						


	return true;
}
bool test::onTouchBegan(Touch* touch, Event* event)					
{
	Vec2 location = touch->getLocation();
	addNewSpriteAtPosition(location);
	return false;
}


void test::addNewSpriteAtPosition(Vec2 p) 							
{
	auto sp = Sprite::create("ball.png");									
	sp->setTag(1);													

	auto body = PhysicsBody::createCircle(sp->getContentSize().width / 2);			
	//auto body = PhysicsBody::createBox(sp->getContentSize());					
	sp->setPhysicsBody(body);										
	sp->setPosition(p);
	this->addChild(sp);
}