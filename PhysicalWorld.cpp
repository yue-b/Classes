#include "PhysicalWorld.h"
#include <iostream>
using namespace std;
Layer* PhysicalWorld::createLayer()
{
	auto layer = PhysicalWorld::create();
	return layer;
}
bool PhysicalWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��������ı߽�
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width*0.8, visibleSize.height*0.8),
		PHYSICSBODY_MATERIAL_DEFAULT, 2.0f);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x03);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	//����С����õ�ƽ̨
	auto platform = PhysicsBody::createEdgeSegment(Vec2(visibleSize.width*0.4, visibleSize.height*0.7), Vec2(visibleSize.width*0.6, visibleSize.height*0.7), 
		PHYSICSBODY_MATERIAL_DEFAULT,8);
	platform->setCategoryBitmask(0x01);
	platform->setCollisionBitmask(0x03);
	auto edgeNode1 = Node::create();
	edgeNode1->setPosition(0,0);
	edgeNode1->setPhysicsBody(platform);
	this->addChild(edgeNode1);
	//������
	Point* points = new Point[101];
	int count = 0;
	for (float i = -50.0; i <= 50; i++){
		float t = i / 50.0;
		Point tmp = Point(visibleSize.width*0.1*t + visibleSize.width*0.5, visibleSize.width*0.1*t*t + visibleSize.height*0.35);
		points[count] = tmp;
		count++;
	}
	auto bowl = PhysicsBody::createEdgeChain(points, count, 
		PHYSICSBODY_MATERIAL_DEFAULT,4);
	bowl->setCategoryBitmask(0x01);
	bowl->setCollisionBitmask(0x03);
	auto edgeNode2 = Node::create();
	edgeNode2->setPosition(0, 0);
	edgeNode2->setPhysicsBody(bowl);
	this->addChild(edgeNode2);
	// 1.//����һ������
	auto m_sprite = Sprite::create("ball.png");
	m_sprite->setPosition(visibleSize.width*0.2, visibleSize.height*0.5);
	this->addChild(m_sprite,1);
	//����������

	auto listener = EventListenerMouse::create();
	//�ַ�MouseMove�¼�

	listener->onMouseMove = CC_CALLBACK_1(PhysicalWorld::mousemove, this);
	listener->onMouseDown = CC_CALLBACK_1(PhysicalWorld::mousedown, this);
	listener->onMouseUp = CC_CALLBACK_1(PhysicalWorld::mouseup, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, m_sprite);
	

	return true;
}

void PhysicalWorld::mousemove(Event* event)
{
	//CCLog("mouse  move!!!!!!!!!!!!!!!!!!!!!!");
	AllocConsole();                                          // ���ٿ���̨
	freopen("CONOUT$", "w", stdout);             // �ض������
	cout << "mouse in" << endl;
	EventMouse* e = (EventMouse*)event;
	if (e->getMouseButton() == 0){
	float x = e->getCursorX();
    float y = e->getCursorY();

	/*auto point = Node::create();
	auto body = PhysicsBody::createCircle(2);
	DrawNode* node = DrawNode::create();
	node->drawDot(Vec2(x,y),5,Color4F::BLUE);
	this->addChild(node);
	point->setPhysicsBody(body);
	point->setPosition(Vec2(x, y));
	this->addChild(point);*/
	this->points.push_back(Point(x, y));
	cout << x << "," << y << endl;
	}

}
void PhysicalWorld::mousedown(Event* event){
	EventMouse* e = (EventMouse*)event;
	float x = e->getCursorX();
	float y = e->getCursorY();
}
void PhysicalWorld::mouseup(Event* event){
	EventMouse* e = (EventMouse*)event;
	float x = e->getCursorX();
	float y = e->getCursorY();
	/*����PhysicsJointDistance���Ӹ���
	auto first = Sprite::create("ball3.png");
	first->setPosition(this->points.begin()->x, this->points.begin()->y);
	auto firstBody = PhysicsBody::createCircle(5); //Բ�θ���
	//firstBody->setCollisionBitmask(0);
	firstBody->setCategoryBitmask(0x02);
	firstBody->setCollisionBitmask(0X03);
	first->setPhysicsBody(firstBody);
	this->addChild(first);
	list<Point>::iterator i = this->points.begin();
	i++;
	for (; i != (this->points.end());i++){
		auto A = Sprite::create("ball3.png");
		A->setPosition(Vec2(i->x, i->y));
		auto bodyA = PhysicsBody::createCircle(5); //Բ�θ���
		//bodyA->setCollisionBitmask(0);
		bodyA->setCategoryBitmask(0x02);
		bodyA->setCollisionBitmask(0X3);
		A->setPhysicsBody(bodyA);
		this->addChild(A);
		auto world = this->getScene()->getPhysicsWorld();
		PhysicsJointDistance* joint = PhysicsJointDistance::construct(firstBody, bodyA,
			Vec2(0, 0), Vec2(0, 3));
		world->addJoint(joint);
		first = A;
		firstBody = bodyA;
	}
	this->points.clear();*/



	/*����DrawPrimitivesh����bug
	DrawPrimitives::setDrawColor4B(255, 255, 255, 255);
	glLineWidth(8);
	Point* tmp = new Point[this->points.size()];
	int len = 0;
	for (list<Point>::iterator i = this->points.begin(); i != (--this->points.end());){
		cout << "lll" << endl;
		tmp[len++] = Point(i->x, i->y);
		Vec2 from = Vec2(i->x, i->y);
		Vec2 to = Vec2((++i)->x, (++i)->y);
		DrawPrimitives::drawLine(from, to);
		auto lineBody = PhysicsBody::createEdgeSegment(from, to);
		auto edgeNode = Node::create();
		edgeNode->setPhysicsBody(lineBody);
		addChild(edgeNode);
	}
	this->points.clear();*/

	//����createEdgeChain�����ߣ������޷�������Ӱ�죩
	auto world = this->getScene()->getPhysicsWorld();
	Point* tmp = new Point[this->points.size()];
	int len = 0;
	for (list<Point>::iterator i = this->points.begin(); i != (--this->points.end()); i++){
	tmp[len++] = Point(i->x, i->y);
	}
	this->points.clear();
	for (int j = 0; j < len-1; j++){
		DrawNode* drawNode2 = DrawNode::create();
		Vec2 from = Vec2(tmp[j].x, tmp[j].y);
		int m = j + 1;
		Vec2 to = Vec2(tmp[m].x, tmp[m].y);
		drawNode2->drawSegment(from, to, 4,Color4F::BLACK);
		this->addChild(drawNode2);
	}
	auto line = PhysicsBody::createEdgeChain(tmp, len,
	PHYSICSBODY_MATERIAL_DEFAULT, 4);
	auto lineNode = Node::create();
	lineNode->setPosition(0, 0);
	lineNode->setPhysicsBody(line);

	this->addChild(lineNode);
}
void PhysicalWorld::update(float dt){

}
