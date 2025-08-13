#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include <functional>

USING_NS_CC;
/// <summary>
/// 游戏总视图，由 GameController 持有
/// </summary>
class GameView : public Node
{
public:

	CREATE_FUNC(GameView);

	virtual bool init() override;

	/// <summary>
	/// 对视图进行初始化
	/// </summary>
	void initView();

	using CardClickCallback = std::function<void()>;
	/// <summary>
	/// 外部卡牌点击事件接口
	/// </summary>
	/// <param name="callback">无参无返回</param>
	void setCardClickCallback(CardClickCallback callback)
	{
		_cardClickCallback = callback;
	}



private:

	CardClickCallback _cardClickCallback;
	/// <summary>
	/// 简单背景画面
	/// </summary>
	cocos2d::DrawNode* _backgroundCardTable;
};



#endif