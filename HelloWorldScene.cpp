#include "HelloWorldScene.h"
#include <iostream>
using namespace std;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	//获取事件分发器

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	//创建自定义事件监听器

	//监听器名字  : "custom_event"

	//事件响应函数: HelloWorld::onCustomEvent

	auto customListener = EventListenerCustom::create("custom_event", CC_CALLBACK_1(HelloWorld::onCustomEvent, this));

	//添加自定义事件监听器，优先权为1

	dispatcher->addEventListenerWithFixedPriority(customListener, 1);


	//手动分发监听器的事件，通过dispatchEvent发布名称为custom_event的消息。

	EventCustom event = EventCustom("custom_event");

	event.setUserData((void*)123); // 绑定消息传递的数据，可以为任意类型void。

	dispatcher->dispatchEvent(&event);



    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
//消息事件回调函数

void HelloWorld::onCustomEvent(EventCustom* event)

{
	AllocConsole();                                          // 开辟控制台
	freopen("CONOUT$", "w", stdout);             // 重定向输出
	// 获取消息传递的数据

	int* data = (int*)event->getUserData();

	cout<<"onCustomEvent data"<<data<<endl;

}
