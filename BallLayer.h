#ifndef __BALL_LAYER_H__
#define __BALL_LAYER_H__

#include "cocos2d.h"

class BallLayer : public cocos2d::Layer
{
private:
	float speedX;
	float speedY;
	float accelerationX;
	float accelerationY;
public:
	cocos2d::Sprite* ball;
	static cocos2d::Layer* createLayer();
	virtual bool init();
	virtual void update(float dt);

	void setSpeed(float x, float y);
	void setAcceleration(float x, float y);
	float getSpeedX();
	float getSpeedY();
	float getAccelerationX();
	float getAccelerationY();

	void move();

	// implement the "static create()" method manually
	CREATE_FUNC(BallLayer);
};

#endif // __BALL_LAYER_H__