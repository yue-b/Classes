#include "FailScene.h"
#include "PhysicalWorld.h"

USING_NS_CC;

CCScene* FailScene::scene()
{
	CCScene *scene = CCScene::create();
	FailScene* failScene = FailScene::create();
	scene->addChild(failScene);
	return scene;
}

bool FailScene::init()
{
	//获取屏幕的尺寸、位置信息等    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*auto firstLayer = FirstMain::createLayer();
	auto itemLayer = ItemLayer::createLayer();
	this->addChild(firstLayer, 0);
	this->addChild(itemLayer, 1);*/
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

	/*auto backItem = MenuItemImage::create(
	"refresh3.png",
	"refreshSelected.png",
	CC_CALLBACK_1(SuccessScene::back, this));
	backItem->setScale(0.5);
	backItem->setPosition(Vec2(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height/ 2-backItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);*/

	auto fail = Sprite::create("fail.png");
	fail->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
	this->addChild(fail);


	auto backToScene = MenuItemImage::create(
		"refresh3.png",
		"refresh3.png",
		CC_CALLBACK_1(FailScene::back, this));
	backToScene->setScale(0.5);
	backToScene->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));

	// create menu, it's an autorelease object
	auto menu = Menu::create(backToScene, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	return true;
}


void FailScene::back(CCObject* pSender)
{
	//本场景出栈
	CCDirector::sharedDirector()->popScene();
	CCDirector::sharedDirector()->popScene();
	auto tmp = PhysicalWorld::createScene();
	CCDirector::sharedDirector()->pushScene(tmp);
}
