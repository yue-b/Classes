#ifndef __PHYSICAL_WORLD_H__
#define __PHYSICAL_WORLD_H__


#include "cocos2d.h"

USING_NS_CC;
class PhysicalWorld : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();
	virtual bool init();
	void mousemove(Event* event);
	void mousedown(Event* event);
	void mouseup(Event* event);
	virtual void update(float dt);

	CREATE_FUNC(PhysicalWorld);
private:
	std::list<Point> points;
};
#endif // __PHYSICAL_WORLD_H__