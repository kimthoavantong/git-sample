/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "gameover.h"


USING_NS_CC;



Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vec2(0, 0)); // chim k chiu tac dong trong luc

	auto layer = HelloWorld::create();
	layer->physics(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("nhac/ANE.mp3");


	auto edegbody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 0); //duong vien = 3, full man hinh
	edegbody->setCollisionBitmask(2);  //chim roi xuong va cham *1
	edegbody->setContactTestBitmask(true); //*1
	auto node = Node::create();
	node->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(edegbody);// tao moi truong vat ly
	addChild(node);

	auto backrou = Sprite::create("1234.jpg");
	backrou->setScale(1);
	backrou->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(backrou);

	birth = Sprite::create("chim30.png");
	birth->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto brithphysic = PhysicsBody::createBox(birth->getContentSize());
	brithphysic->setContactTestBitmask(true); //bat va cham
	brithphysic->setCollisionBitmask(4);
	birth->setPhysicsBody(brithphysic);
	addChild(birth);

	//auto chim = Sprite::create("chim30.png");
	//chim->setPosition(Vec2(visibleSize.width/20, visibleSize.height / 2));
	//chim->setScale(1);
	//auto bodychim = PhysicsBody::createBox(chim->getContentSize());
	//chim->setPhysicsBody(bodychim);

	//addChild(chim);

	auto touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(HelloWorld::click, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
	// tao label tinh diem
	__String *diem1 = __String::createWithFormat("%i", diem);
	label = Label::createWithTTF(diem1->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.1);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.8));
	label->setColor(Color3B::RED);
	addChild(label);

	auto contactlis = EventListenerPhysicsContact::create();
	contactlis->onContactBegin = CC_CALLBACK_1(HelloWorld::vacham, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactlis, this);

	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::taoongnuoc), 0.005*visibleSize.width);	 // goi ham tao ong nuoc de chay


    return true;
}
void HelloWorld::taoongnuoc(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto cottren = Sprite::create("cot22.png");
	auto cotduoi = Sprite::create("cot11.png");

	//set physics
	auto topphysic = PhysicsBody::createBox(cottren->getContentSize());

	//thuoc tinh bat va cham
	topphysic->setCollisionBitmask(2); // dat ten
	topphysic->setContactTestBitmask(true); // k co k phat hien va cham
	cottren->setPhysicsBody(topphysic);

	auto butomphysic = PhysicsBody::createBox(cotduoi->getContentSize());
	butomphysic->setCollisionBitmask(2);
	butomphysic->setContactTestBitmask(true);
	cotduoi->setPhysicsBody(butomphysic);

	topphysic->setDynamic(false); // k chiu trong luc
	butomphysic->setDynamic(false);



	// lay ti le
	auto random = CCRANDOM_0_1();
	if (random < 0.35)
	{
		random = 0.35;
	}
	else
	{
		if (random>65)
		{
			random = 65;
		}
	}

	// toa do y	 2 cot voi chieu cao random moi cot
	auto cottren1 = visibleSize.height*random + cottren->getContentSize().height / 2;
	cottren->setPosition(Vec2(visibleSize.width + cottren->getContentSize().width, cottren1)); // cot ngoai man hinh

	cotduoi->setPosition(Vec2(cottren->getPositionX(), cottren1 - (Sprite::create("chim30.png")->getContentSize().height * 5) - cottren->getContentSize().height));

	addChild(cottren);
	addChild(cotduoi);

	auto dichuyen1 = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	auto dichuyen2 = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	cottren->runAction(dichuyen1);
	cotduoi->runAction(dichuyen2);

	auto pointNode = Node::create();
	pointNode->setPosition(Vec2(cottren->getPositionX(), cottren->getPositionY() - cottren->getContentSize().height / 2 - (Sprite::create("chim30.png")->getContentSize().height * 5) / 2));
	auto nodephysic = PhysicsBody::createBox(Size(1, (Sprite::create("chim30.png")->getContentSize().height * 5))); // chieu cao node
	nodephysic->setCollisionBitmask(3);
	nodephysic->setContactTestBitmask(true);
	pointNode->setPhysicsBody(nodephysic);

	nodephysic->setDynamic(false);

	auto dichuyen3 = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	pointNode->runAction(dichuyen3);




	addChild(pointNode);
}
void HelloWorld::update(float fl)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// chim roi xuong
	if (isfalling == true)
	{
		birth->setPositionX(visibleSize.width / 2);
		birth->setPositionY(birth->getPositionY() - visibleSize.height*0.005);
	}
	else // chim bay len
	{
		birth->setPositionX(visibleSize.width / 2);
		birth->setPositionY(birth->getPositionY() + visibleSize.height*0.0075);
	}

}
// click chim
bool HelloWorld::click(cocos2d::Touch *touch1, cocos2d::Event *event1)
{
	isfalling = false;
	this->scheduleOnce(schedule_selector(HelloWorld::stopfly), 0.3); //sau 0.25s chim roi xuong
	return true;
}
void HelloWorld::stopfly(float fl1) {
	isfalling = true;
}
bool HelloWorld::vacham(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	 //hien diem

	if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 3 || a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 4)
	{
		diem = diem + 1;
		__String *diem1 = __String::createWithFormat("%i", diem);
		label->setString(diem1->getCString());
	}
	//else //game over
	//{
	//	if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 2 || a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 4)
	//	{
	//		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects(); //stop tat ca nhac
	//		auto gameover1 = gameover::createScene();
	//		Director::getInstance()->replaceScene(gameover1);
	//	}
	//}
	return true;
}



