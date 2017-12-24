#ifndef __PHYSICAL_WORLD_H__
#define __PHYSICAL_WORLD_H__


#include "cocos2d.h"
USING_NS_CC;

class PhysicalWorld : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	CREATE_FUNC(PhysicalWorld);

	void addNewSpriteAtPosition(Vec2 p);
};
#endif // __PHYSICAL_WORLD_H__