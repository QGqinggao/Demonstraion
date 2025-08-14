#ifndef __PLAY_FIELD_CONTROLLER_H__
#define __PLAY_FIELD_CONTROLLER_H__

#include "cocos2d.h"
#include "models/CardModel.h"
#include <views/PlayFieldView.h>
#include "CardController.h"

/// <summary>
/// PlayField 区域控制器，负责其区域  CardControllers 的管理
/// </summary>
class PlayFieldController
{
public:
	/// <summary>
	/// 根据 PlayFielcCardModel 对 PlayFiledController 进行初始化
	/// </summary>
	/// <param name="playFieldCards"></param>
	void init(const std::vector<CardModel>& playFieldCards);
	/// <summary>
	/// 初始化PlayFieldView 以及其下面的 CardControllers 视图
	/// </summary>
	/// <param name="parentNode"></param>
	/// <returns></returns>
	bool initView(cocos2d::Node* parentNode);
	/// <summary>
	/// 初始化卡牌之间的覆盖关系
	/// </summary>
	void initCoverRelations();
	/// <summary>
	/// 更新卡牌之间的覆盖关系
	/// </summary>
	void updateCoverRelations();
	/// <summary>
	/// 向 PlayFieldControllers 中添加新卡牌
	/// </summary>
	/// <param name="cardController"></param>
	void pushController(std::shared_ptr<CardController> cardController);
	/// <summary>
	/// 向 PlayFieldCardModels 中添加新卡牌
	/// </summary>
	/// <param name="model"></param>
	void pushModel(CardModel& model);
	/// <summary>
	/// 获得 PlayFieldView 接口
	/// </summary>
	/// <returns></returns>
	PlayFieldView* getView();
	/// <summary>
	/// 获得 PlayFiledCardModels 中的 CardModel 通过 cardId
	/// </summary>
	/// <param name="cardId"></param>
	/// <returns></returns>
	CardModel& getCardModel(int cardId);
	/// <summary>
	/// 获得 PlayFiledCardControllers 中的 CardController 通过 cardId
	/// </summary>
	/// <param name="cardId"></param>
	/// <returns></returns>
	std::shared_ptr<CardController> getCardController(int cardId);
	/// <summary>
	/// 处理卡牌点击事件
	/// </summary>
	/// <param name="cardId"></param>
	void handleCardClick(int cardId);

	using ClickCallback = std::function<void(int cardId)>;
	void setClickCallback(const ClickCallback callback) { _cardClickCallback = callback; }

	/// <summary>
	/// 将 PlayField 中的卡牌替换为手牌
	/// </summary>
	/// <param name="cardId"></param>
	void replaceTrayWithPlayFieldCard(int cardId);
	/// <summary>
	/// 注册卡牌点击
	/// </summary>
	/// <param name="cardController"></param>
	void registerCardClickCallback(std::shared_ptr<CardController> cardController);

private:
	std::vector<CardModel> _playFieldCards;
	std::vector<std::shared_ptr<CardController>> _playFieldCardControllers;

	PlayFieldView* _playFieldView;

	std::unordered_map<int, std::vector<int>> _coverMap;

	std::function<void(int cardId)> _cardClickCallback;
	void _onCardClickCallback(int cardId);

};


#endif