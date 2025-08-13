#include "PlayFieldView.h"
#include "configs/ConstValueConfig.h"

USING_NS_CC;

bool PlayFieldView::init()
{
	if (!Node::init()) return false;

	this->setContentSize(Size(1080, 1500));
	this->setAnchorPoint(Vec2(0, 0));
	this->setPosition(0, 580);

	_backgroundCardTable = cocos2d::DrawNode::create();

	Rect rect(kSpace, 0, 1080 - kSpace * 2, 1500 - kSpace);
	Color3B color(170, 121, 66);
	_backgroundCardTable->drawSolidRect(rect.origin, rect.origin + Vec2(rect.size), Color4F(color));
	this->addChild(_backgroundCardTable, -1);

	return true;
}
