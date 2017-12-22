#ifndef __FIRSTMAIN_SCENE_H__
#define __FIRSTMAIN_SCENE_H__

#include "cocos2d.h"

class FirstMain : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(FirstMain);
};

#endif // __FIRSTMAIN_SCENE_H__
