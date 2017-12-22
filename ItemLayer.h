#ifndef __ITEM_LAYER_H__
#define __ITEM_LAYER_H__

#include "cocos2d.h"

class ItemLayer : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();


	// implement the "static create()" method manually
	CREATE_FUNC(ItemLayer);
};

#endif // __ITEM_LAYER_H__