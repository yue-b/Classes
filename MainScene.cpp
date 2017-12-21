#include "cocos2d.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Scene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}