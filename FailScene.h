#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class FailScene :public CCLayer{
public:
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(FailScene);
	void back(cocos2d::Ref* pSender);//���س���
	void showMessage(std::string msg);
};