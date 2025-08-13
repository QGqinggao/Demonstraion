#include "StackView.h"
#include "utils/Utils.h"
#include "configs/ConstValueConfig.h"

USING_NS_CC;

bool StackView::init()
{
	if (!Node::init()) return false;

	this->setContentSize(Size(1080, 580));
	this->setAnchorPoint(Vec2(0, 0));
	this->setPosition(0, 0);

	_backgroundCardTable = cocos2d::DrawNode::create();

	Rect rect(kSpace, kSpace, 1080 - kSpace * 2, 580 - kSpace);
	Color3B color(148, 33, 146);
	_backgroundCardTable->drawSolidRect(rect.origin, rect.origin + Vec2(rect.size), Color4F(color));
	this->addChild(_backgroundCardTable, -1);

	_undoButton = cocos2d::ui::Button::create();
	_undoButton->setTitleFontName("fonts/simhei");
	_undoButton->setTitleText(Utils::GBKToUTF8("回退"));
	_undoButton->setTitleFontSize(50);
	_undoButton->setTitleColor(Color3B::WHITE);
	_undoButton->setContentSize(Size(100, 60));
	_undoButton->setPosition(Vec2(900, 400));
	_undoButton->addClickEventListener(CC_CALLBACK_1(StackView::_onUndoButtonClick, this));

	this->addChild(_undoButton);

	return true;
}


void StackView::_onUndoButtonClick(cocos2d::Ref* sender)
{
	_buttonClickCallback();
}

