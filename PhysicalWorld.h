#ifndef __PHYSICAL_WORLD_H__
#define __PHYSICAL_WORLD_H__


#include "cocos2d.h"

USING_NS_CC;
static Vector<Node*>  front;
static Vector<Node*>  nextforward;
class PhysicalWorld : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();
	virtual bool init();
	void mousemove(Event* event);
	void mousedown(Event* event);
	void mouseup(Event* event);

	void ballup(Event* event);

	void freshCallback(Ref* pSender);
	void frontCallback(Ref* pSender);
	void nextCallback(Ref* pSender);


	CREATE_FUNC(PhysicalWorld);
private:
	std::list<Point> points;

	Point from_point;
	Point to_point;
	cocos2d::Sprite* ball;
	EventListenerMouse* listener;
	EventListenerMouse* ball_listener;
};
#endif // __PHYSICAL_WORLD_H__