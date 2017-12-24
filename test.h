#ifndef __TEST_H__
#define __TEST_H__


#include "cocos2d.h"
USING_NS_CC;

class test : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();



	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	CREATE_FUNC(test);

	void addNewSpriteAtPosition(Vec2 p);
};
#endif // __TEST_H__