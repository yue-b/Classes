#ifndef __BALL_LAYER_H__
#define __BALL_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;
class BallLayer : public cocos2d::Layer
{
private:
	Point from_point;
	Point to_point;
	cocos2d::Sprite* ball;
public:
	static cocos2d::Layer* createLayer();
	virtual bool init();
	void mousedown(Event* event);
	void mouseup(Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(BallLayer);
};

#endif // __BALL_LAYER_H__