#include <iostream>
#include "Checkpoint.h"
#include "PhysicalWorld.h"
#include "SuccessScene.h"
#include "math.h"
extern char num;

USING_NS_CC;

CCScene* Checkpoint::scene()
{
	CCScene *scene = CCScene::create();
	Checkpoint* CheckpointScene = Checkpoint::create();
	scene->addChild(CheckpointScene);
	return scene;
}

// on "init" you need to initialize your instance
bool Checkpoint::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	//¼ÓÔØ±³¾°Í¼Æ¬
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

	//¼ÓÔØ¹Ø¿¨°´Å¥
	auto checkpoint2 = MenuItemImage::create(
		"checkpoint2.png",
		"checkpoint2.png",
		CC_CALLBACK_1(Checkpoint::play, this, '2'));
	checkpoint2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));

	auto checkpoint1 = MenuItemImage::create(
		"checkpoint1.png",
		"checkpoint1.png",
		CC_CALLBACK_1(Checkpoint::play, this, '1'));
	checkpoint1->setPosition(Vec2(checkpoint2->getPositionX()-150, checkpoint2->getPositionY()));

	auto checkpoint3 = MenuItemImage::create(
		"checkpoint3.png",
		"checkpoint3.png",
		CC_CALLBACK_1(Checkpoint::play, this, '3'));
	checkpoint3->setPosition(Vec2(checkpoint2->getPositionX() + 150, checkpoint2->getPositionY()));

	auto checkpoint4 = MenuItemImage::create(
		"checkpoint4.png",
		"checkpoint4.png",
		CC_CALLBACK_1(Checkpoint::play, this, '4'));
	checkpoint4->setPosition(Vec2(checkpoint2->getPositionX() - 150, checkpoint2->getPositionY()-150));

	auto checkpoint5 = MenuItemImage::create(
		"checkpoint_pending.png",
		"checkpoint_pending.png");
	checkpoint5->setPosition(Vec2(checkpoint2->getPositionX(), checkpoint2->getPositionY() - 150));

	auto checkpoint6 = MenuItemImage::create(
		"checkpoint_pending.png",
		"checkpoint_pending.png");
	checkpoint6->setPosition(Vec2(checkpoint2->getPositionX()+150, checkpoint2->getPositionY() - 150));

	auto menu = Menu::create(checkpoint1, NULL);
	menu->addChild(checkpoint2);
	menu->addChild(checkpoint3);
	menu->addChild(checkpoint4);
	menu->addChild(checkpoint5);
	menu->addChild(checkpoint6);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 0);
	

	return true;
}
void Checkpoint::play(Ref* pSender, char n){
	num = n;
	auto checkpoint_1 = PhysicalWorld::createScene();
	CCDirector::sharedDirector()->pushScene(checkpoint_1);
}



