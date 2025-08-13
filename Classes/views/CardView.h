#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__

#include "cocos2d.h"
#include "models/CardModel.h"

/// <summary>
/// CardView 由 CardController 持有并处理，负责卡牌视图相关内容
/// </summary>
class CardView : public cocos2d::Node
{
public:

	CREATE_FUNC(CardView);

	/// <summary>
	/// 对 CardView 进行简单初始化：绑定事件等
	/// </summary>
	/// <returns>是否初始化成功</returns>
	virtual bool init() override;
	/// <summary>
	/// 根据 CardModel 对视图进行初始化
	/// </summary>
	/// <param name="cardModel">卡牌数据</param>
	/// <returns>是否初始化成功</returns>
	bool initViewWithModel(const std::shared_ptr<CardModel>& cardModel);
	/// <summary>
	/// 将 CardView 移动到指定位置
	/// </summary>
	/// <param name="position">位置坐标</param>
	void moveToPos(cocos2d::Vec2 position);

	using ClickCallback = std::function<void()>;
	/// <summary>
	/// 外部调用事件绑定接口
	/// </summary>
	/// <param name="callback">无参无返回</param>
	void setClickCallback(const ClickCallback callback) { _clickCallback = callback; }

private:
	/// <summary>
	/// 卡牌背景
	/// </summary>
	cocos2d::Sprite* _background;
	/// <summary>
	/// 卡牌中心数字
	/// </summary>
	cocos2d::Sprite* _mainNumber;
	/// <summary>
	/// 卡牌左上角数字
	/// </summary>
	cocos2d::Sprite* _topLeftNumber;
	/// <summary>
	/// 卡牌右上角数字
	/// </summary>
	cocos2d::Sprite* _topRightSuit;

	cocos2d::EventListenerTouchOneByOne* _touchListener;
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* evnet);

	ClickCallback _clickCallback;

	/// <summary>
	/// 点击是否位于卡牌区域
	/// </summary>
	bool _isTouchInArea;

	std::shared_ptr<CardModel> _cardModel;
};






#endif