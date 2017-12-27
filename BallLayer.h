#ifndef __BALL_LAYER_H__
#define __BALL_LAYER_H__

#include "cocos2d.h"

class BallLayer : public cocos2d::Layer
{

public:
	cocos2d::Sprite* ball;
	static cocos2d::Layer* createLayer();
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(BallLayer);
};

#endif // __BALL_LAYER_H__