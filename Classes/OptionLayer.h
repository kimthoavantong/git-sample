#pragma once
#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "MessageScene.h"
using namespace cocos2d::ui;
USING_NS_CC;
class OptionLayer : public Layer
{
public:
	
	bool init();
	CREATE_FUNC(OptionLayer);
	void close(Ref* sender = nullptr);
	void ShowOptionScene();
	static void CheckCancel();
private:
	cocos2d::Menu * menu;
	cocos2d::Sprite *settingbackground;
	//
	cocos2d::ui::CheckBox * checkboxMusic;
	cocos2d::ui::CheckBox * checkboxXMusic;
	cocos2d::ui::CheckBox * checkboxSound;
	cocos2d::ui::CheckBox * checkboxXSound;
	cocos2d::MenuItemSprite *musicItem;
	cocos2d::MenuItemSprite *soundItem;
	//
	MessageScene *messageScene;
};


