#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

class Welcome : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();
	void startPlay(Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Welcome);
};

#endif // __WELCOME_SCENE_H__
