#ifndef __CHECKPOINT_SCENE_H__
#define __CHECKPOINT_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class Checkpoint : public CCLayer
{
public:
	static CCScene* scene();
	virtual bool init();
	void play(Ref* pSender,char num);

	// implement the "static create()" method manually
	CREATE_FUNC(Checkpoint);
};

#endif // __CHECKPOINT_SCENE_H__
