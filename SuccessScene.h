#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class SuccessScene :public CCLayer{
public:
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(SuccessScene);
	void back(cocos2d::Ref* pSender);//���س���
	void showMessage(std::string msg);
};