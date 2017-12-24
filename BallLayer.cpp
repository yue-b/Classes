#include "BallLayer.h"
#include <iostream>
#include "math.h"
using namespace std;

USING_NS_CC;

//摩擦等阻力
float Loss(float factor,float speed){
	float tmp = (1.0 - factor) * speed;
	if (fabsf(tmp) < 1)
		return 0;
	return tmp;
}

Layer* BallLayer::createLayer()
{

	// 'layer' is an autorelease object
	auto layer = BallLayer::create();

	// return the scene
	return layer;
}

// on "init" you need to initialize your instance
bool BallLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//AllocConsole();                                          // 开辟控制台
	//freopen("CONOUT$", "w", stdout);             // 重定向输出
	//cout << "in" << endl;
	/////////////////////////////
	// 3. add your codes below...
	this->ball = Sprite::create("ball1.png");
	this->ball->setPosition(Vec2(
		visibleSize.width*0.5,
		visibleSize.height*0.7 + this->ball->getContentSize().height / 2 + 4));
	//{小球起始点坐标x = visibleSize.width*0.5+ origin.x;y = visibleSize.height*0.7+this->ball->getContentSize().height/2 + 4 + origin.y}

	setSpeed(10, -2);
	setAcceleration(0, -9.8 / 60);//重力加速度
	this->addChild(this->ball, 2);

	this->scheduleUpdate();
	return true;
}
void BallLayer::move(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float factor = 0.2;//碰撞损失
	speedX = Loss(0.003,speedX );
	double x = this->ball->getPositionX();//小球当前圆心位置

	double A = visibleSize.width*0.1 + this->ball->getContentSize().width / 2;
	float B = visibleSize.width*0.4 - this->ball->getContentSize().width / 2;
	float O = visibleSize.width*0.5;
	float C = visibleSize.width*0.6 + this->ball->getContentSize().width / 2;
	float D = visibleSize.width*0.9 - this->ball->getContentSize().width / 2;
	//触碰到平台反弹
	if ((float)(this->ball->getPositionY())<(float)(visibleSize.height*0.7 + this->ball->getContentSize().height / 2 + 4)
		&& (float)(this->ball->getPositionY())>(float)(visibleSize.height*0.7 - this->ball->getContentSize().height / 2 - 4)){

		if (x < A){
			speedX = fabsf(speedX);
			speedX = speedX * (1 - factor);
		}
		if (x > B && x<O){
			speedX = -fabsf(speedX);
			speedX = speedX * (1 - factor);
		}
		if (x > O && x < C){
			speedX = fabsf(speedX);
			speedX = speedX * (1 - factor);
		}
		if (x > D){
			speedX = -fabsf(speedX);
			speedX = speedX * (1 - factor);
		}
	}
	else{
		//cout << "0" << endl;
		if ((float)(this->ball->getPositionY()) <= (float)(visibleSize.width*0.1*0.5*0.5 + visibleSize.height*0.35)
			&& (float)(this->ball->getPositionY()) >= (float)(visibleSize.height*0.35)){
			float t1 = -sqrtf((this->ball->getPositionY() - visibleSize.height*0.35) / (visibleSize.width*0.1));
			float t2 = sqrtf((this->ball->getPositionY() - visibleSize.height*0.35) / (visibleSize.width*0.1));
			float O1 = visibleSize.width*0.1*t1 + visibleSize.width*0.5;
			float l1 = O1 - 2 - this->ball->getContentSize().width / 2;
			float r1 = O1 + 2 + this->ball->getContentSize().width / 2;
			float O2 = visibleSize.width*0.1*t2 + visibleSize.width*0.5;
			float l2 = O2 - 2 - this->ball->getContentSize().width / 2;
			float r2 = O2 + 2 + this->ball->getContentSize().width / 2;
			if (x < A){
				speedX = fabsf(speedX);
				speedX = speedX * (1 - factor);
			}
			if (x > l1 && x < O1){
				speedX = -fabsf(speedX);
				speedX = speedX * (1 - factor);
			}
			if (x > O1 && x < r1){
				speedX = fabsf(speedX);
				speedX = speedX * (1 - factor);

			}
			if (x > l2 && x < O2){
				speedX = -fabsf(speedX);
				speedX = speedX * (1 - factor);
			}
			if (x > O2 && x < r2){
				speedX = fabsf(speedX);
				speedX = speedX * (1 - factor);
			}
			if (x > D){
				speedX = -fabsf(speedX);
				speedX = speedX * (1 - factor);
			}
		}
		else{
			if (x > D){
				speedX = -fabsf(speedX);
				speedX = speedX * (1 - factor);
			}
			if (x < A){
				speedX = fabsf(speedX);
				speedX = speedX * (1 - factor);
			}
		}
	}

	float up = visibleSize.height*0.9 - this->ball->getContentSize().height / 2;
	float level_1 = visibleSize.height*0.7 + this->ball->getContentSize().height / 2 + 4;
	float level_2 = visibleSize.height*0.7;
	float level_3 = visibleSize.height*0.7 - this->ball->getContentSize().height / 2 - 4;
	float down = visibleSize.height*0.1 + this->ball->getContentSize().height / 2;
	float y = this->ball->getPositionY();
	setAcceleration(0, -9.8 / 60);//重力加速度
	//cout << (float)(visibleSize.width*0.1 * 1 + visibleSize.width*0.5) << "," << (float)(visibleSize.width*0.1 * (-1.0) + visibleSize.width*0.5) << endl;
	//cout << "B:" << B << " C:" << C << endl;
	if (x >= B && x <= C){
		if (x <= (float)(visibleSize.width*0.1 * 0.5 + visibleSize.width*0.5)
			&& x >= (float)(visibleSize.width*0.1 * (-0.5) + visibleSize.width*0.5)){
			float O1 = powf((this->ball->getPositionX() - visibleSize.width*0.5) / (visibleSize.width*0.1), 2)*visibleSize.width*0.1 + visibleSize.height*0.35;
			float d1 = O1 - 2 - this->ball->getContentSize().height / 2;
			float u1 = O1 + 2 + this->ball->getContentSize().height / 2;
			if (y < down){
				speedY = fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y > d1 && y < O1){
				speedY = -fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y > O1 && y < u1){
				speedY = fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y > level_2 && y < level_1){
				speedY = fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y < level_2 && y > level_3){
				speedY = -fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y > up){
				speedY = -fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			
			if (y <= level_1 && y> level_2 && fabsf(speedY) < 2.0){
				speedY = 0;
				setAcceleration(0, 0);
			}
			if (y <= u1 && y > O1 && fabsf(speedY) < 2.0){
				speedY = 0;
				setAcceleration(0, 0);
			}
			if (y <= down&&fabsf(speedY) < 2.0){
				speedY = 0;
				setAcceleration(0, 0);
			}
		}
		else{
			if (y > up){
				speedY = -fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y > level_2 && y < level_1){
				speedY = fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y < level_2 && y > level_3){
				speedY = -fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y < down){
				speedY = fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y <= level_1 && y> level_2 && fabsf(speedY) < 2.0){
				speedY = 0;
				setAcceleration(0, 0);
			}
			if (y <= down&&fabsf(speedY) < 2.0){
				speedY = 0;
				setAcceleration(0, 0);
			}
		}
	}
	else{
			if (y < down){
				speedY = fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y > up){
				speedY = -fabsf(speedY);
				speedY = speedY * (1 - factor);
			}
			if (y <= down&&fabsf(speedY) < 2.0){
				speedY = 0;
				setAcceleration(0, 0);
			}
		}
	//cout << "x:" << x << " speedX:" << speedX << " accelerationX:" << accelerationX << endl;
	//cout << "y:" << y << " speedY:" << speedY << " accelerationY:" << accelerationY << endl;
	this->ball->setPositionX(x + speedX);
	this->ball->setPositionY(y + speedY);
	
	setSpeed(speedX + this->accelerationX, speedY + this->accelerationY);	
}
void BallLayer::setSpeed(float x,float y){
	this->speedX = x;
	this->speedY = y;
}
void BallLayer::setAcceleration(float x, float y){
	this->accelerationX = x;
	this->accelerationY = y;
}
float BallLayer::getSpeedX(){
	return this->speedX;
}
float BallLayer::getSpeedY(){
	return this->speedY;
}
float BallLayer::getAccelerationX(){
	return this->accelerationX;
}
float BallLayer::getAccelerationY(){
	return this->accelerationY;
}
void BallLayer::update(float dt){
	this->move();
}