#include "GameView.h"

USING_NS_CC;

bool GameView::init()		
{
	if (!Node::init()) return false;

	this->setContentSize(Director::getInstance()->getVisibleSize());
	this->setAnchorPoint(Vec2(0, 0));
	this->setPosition(0, 0);

	return true;
}

void GameView::initView()
{
	_backgroundCardTable = cocos2d::DrawNode::create();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Rect rect(0, 0, visibleSize.width, visibleSize.height);
	Color3B color(128, 128, 128);
	_backgroundCardTable->drawSolidRect(rect.origin, rect.origin + Vec2(rect.size), Color4F(color));
	this->addChild(_backgroundCardTable, -1);
}