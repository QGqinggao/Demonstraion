#ifndef __CARD_CONTROLLER_H__
#define __CARD_CONTROLLER_H__

#include "models/CardModel.h"
#include "views/CardView.h"

/// <summary>
/// 单个卡牌控制器，由 PlayFieldController 和 StackController 分别持有
/// </summary>
class CardController
{
public:
	/// <summary>
	/// 根据 CardModel 进行初始化
	/// </summary>
	/// <param name="cardModel"></param>
	void init(std::shared_ptr<CardModel> cardModel);
	/// <summary>
	/// 初始化视图
	/// </summary>
	/// <param name="parent">父节点</param>
	/// <returns></returns>
	bool initView(cocos2d::Node* parent);

	/// <summary>
	/// 获得持有的 CardModel 的 Id
	/// </summary>
	/// <returns></returns>
	int getCardId();
	/// <summary>
	/// 获得卡牌实际数字
	/// </summary>
	/// <returns></returns>
	int getNumber();
	/// <summary>
	/// 获得 CardView 接口
	/// </summary>
	/// <returns></returns>
	CardView* getView();
	/// <summary>
	/// 获得 CardModel 接口
	/// </summary>
	/// <returns></returns>
	CardModel getModel();
	/// <summary>
	/// 设置卡牌是否可以被选择
	/// </summary>
	/// <param name="canSelect"></param>
	void setCanSelect(bool canSelect);
	/// <summary>
	/// 处理卡牌点击事件
	/// </summary>
	void handleCardClick();

	using ClickCallback = std::function<void(int cardId)>;
	/// <summary>
	/// 外部调用点击事件接口
	/// </summary>
	/// <param name="callback"></param>
	void setClickCallback(const ClickCallback callback) { _cardClickCallback = callback; }

private:

	std::shared_ptr<CardModel> _cardModel;
	CardView* _cardView;
	/// <summary>
	/// 注册卡牌视图点击事件
	/// </summary>
	void registerCardViewCallback();

	std::function<void(int cardId)> _cardClickCallback;
};




#endif