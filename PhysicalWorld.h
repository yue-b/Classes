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
	static cocos2d::Scene* createScene();
	virtual bool init();
	void mousemove(Event* event);
	void mousedown(Event* event);
	void mouseup(Event* event);

	void ballup(Event* event);

	void freshCallback(Ref* pSender);
	void frontCallback(Ref* pSender);
	void nextCallback(Ref* pSender);
	void back(cocos2d::Ref* pSender);//·µ»Ø³¡¾°
	
	//void showMessage(std::string msg);
	void update(float dt);
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

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