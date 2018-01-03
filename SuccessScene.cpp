#include "SuccessScene.h"
#include "ItemLayer.h"
#include "FirstMainScene.h"

USING_NS_CC;

CCScene* SuccessScene::scene()
{
	CCScene *scene = CCScene::create();
	SuccessScene* successScene = SuccessScene::create();
	scene->addChild(successScene);
	return scene;
}

bool SuccessScene::init()
{
	//获取屏幕的尺寸、位置信息等    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto firstLayer = FirstMain::createLayer();
	auto itemLayer = ItemLayer::createLayer();
	this->addChild(firstLayer, 0);
	this->addChild(itemLayer, 1);

	auto backItem = MenuItemImage::create(
		"refresh3.png",
		"refreshSelected.png",
		CC_CALLBACK_1(SuccessScene::back, this));
	backItem->setScale(0.5);
	backItem->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height/ 2-backItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	showMessage("Success");
	return true;
}


void SuccessScene::back(CCObject* pSender)
{
	//本场景出栈
	CCDirector::sharedDirector()->popScene();
}
void SuccessScene::showMessage(std::string msg){
	//获取屏幕的尺寸、位置信息等    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCLabelTTF* _label = CCLabelTTF::create(msg.c_str(), "", 40);
	_label->setPosition(visibleSize.width / 2, visibleSize.height/2+50);
	//_label->runAction(CCSequence::create(CCDelayTime::create(5), CCFadeOut::create(1), CCRemoveSelf::create(true), NULL));
	this->addChild(_label);
}
