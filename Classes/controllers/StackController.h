#ifndef __STACK_CONTROLLER_H__
#define __STACK_CONTROLLER_H__

#include "cocos2d.h"
#include "models/CardModel.h"
#include "views/StackView.h"
#include "controllers/CardController.h"

/// <summary>
/// Stack 区域控制器，负责其区域  CardControllers 的管理
/// </summary>
class StackController
{
public:
	/// <summary>
	/// 根据 StackCardModel 对 PlayFiledController 进行初始化
	/// </summary>
	/// <param name="stackCards"></param>
	void init(const std::vector<CardModel>& stackCards);
	/// <summary>
	/// 初始化StackView 以及其下面的 CardControllers 视图
	/// </summary>
	/// <param name="parentLayer"></param>
	/// <returns></returns>
	bool initView(cocos2d::Node* parentLayer);
	/// <summary>
	/// 初始化卡牌之间的覆盖关系
	/// </summary>
	void initCoverRelations();
	/// <summary>
	/// 初始化手牌控制器
	/// </summary>
	void initTrayCardController();
	/// <summary>
	/// 更新卡牌之间的覆盖关系
	/// </summary>
	void updateCoverRelations();
	/// <summary>
	/// 向 StackControllers 中添加新卡牌
	/// </summary>
	/// <param name="cardController"></param>
	void pushController(std::shared_ptr<CardController> cardController);
	/// <summary>
	/// 向 StackCardModels 中添加新卡牌
	/// </summary>
	/// <param name="model"></param>
	void pushModel(CardModel& model);
	/// <summary>
	/// 设置手牌控制器
	/// </summary>
	/// <param name="newTrayCardController"></param>
	void setTrayCardController(std::shared_ptr<CardController> newTrayCardController);
	/// <summary>
	/// 获得 StackView 接口
	/// </summary>
	/// <returns></returns>
	cocos2d::Node* getView();
	/// <summary>
	/// 处理卡牌点击事件
	/// </summary>
	/// <param name="cardId"></param>
	void handleCardClick(int cardId);

	using CardClickCallback = std::function<void(int cardId)>;
	void setCardClickCallback(const CardClickCallback callback) { _cardClickCallback = callback; }

	using ButtonClickCallback = std::function<void()>;
	void setButtonClickCallback(const ButtonClickCallback buttonClickCallback) { _buttonClickCallback = buttonClickCallback; }
	/// <summary>
	/// 获得 StackModels 中的 CardModel 通过 cardId
	/// </summary>
	/// <param name="cardId"></param>
	/// <returns></returns>
	CardModel& getCardModel(int cardId);
	/// <summary>
	/// 获得 StackCardControllers 中的 CardController 通过 cardId
	/// </summary>
	/// <param name="cardId"></param>
	/// <returns></returns>
	std::shared_ptr<CardController> getCardController(int cardId);
	/// <summary>
	/// 获得手牌控制器
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<CardController> getTrayCardController();
	/// <summary>
	/// 将 Stack 中的卡牌替换为手牌
	/// </summary>
	/// <param name="cardId"></param>
	void replaceTrayWithStack(int cardId);
	/// <summary>
	/// 替换手牌
	/// </summary>
	/// <param name="newTrayCardController"></param>
	void replaceTray(std::shared_ptr<CardController> newTrayCardController);

private:
	std::vector<CardModel> _stackCards;
	std::vector<std::shared_ptr<CardController>> _stackCardControllers;

	StackView* _stackView;

	std::shared_ptr<CardController> _trayCardController;

	std::unordered_map<int, std::vector<int>> _coverMap;

	void _onCardClickCallback(int cardId);
	void _onButtonClickCallback(cocos2d::Ref* sender);

	std::function<void(int cardId)> _cardClickCallback;
	std::function<void()> _buttonClickCallback;

};



#endif