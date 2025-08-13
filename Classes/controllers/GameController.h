#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "GamePlayScene.h"
#include "views/GameView.h"
#include "models/GameModel.h"

#include <functional>
#include <services/GameModelFromLevelGenerator.h>
#include "PlayFieldController.h"
#include "StackController.h"
#include <managers/UndoManager.h>

/// <summary>
/// 游戏总控制器，负责控制 GameView 和 PlayFieldController 、StackController
/// </summary>
class GameController
{
public:
	/// <summary>
	/// 初始化：绑定事件
	/// </summary>
	void init();
	/// <summary>
	/// 初始化 GameView
	/// </summary>
	/// <param name="layer"></param>
	/// <returns></returns>
	bool initView(GamePlayScene* layer);
	/// <summary>
	/// 开始游戏，每次选择关卡后调用
	/// </summary>
	/// <param name="levelId">关卡 id</param>
	/// <returns></returns>
	bool startGame(int levelId);
	/// <summary>
	/// 处理 PlayField 区域的卡牌点击事件
	/// </summary>
	/// <param name="cardId">需要处理的卡牌 id</param>
	void handlePlayFieldCardClick(int cardId);
	/// <summary>
	/// 处理 Stack 区域的卡牌点击事件
	/// </summary>
	/// <param name="cardId">需要处理的卡牌 id</param>
	void handleStackCardClick(int cardId);
	/// <summary>
	/// 处理回退按键点击事件
	/// </summary>
	void handleUndoButtonClick();
	/// <summary>
	/// 处理回退操作
	/// </summary>
	/// <param name="step"></param>
	void handleUndo(const UndoStep& step);
	/// <summary>
	/// 禁用所有输入
	/// </summary>
	void disableAllInputs();
	/// <summary>
	/// 等待一段事件恢复所有输入
	/// </summary>
	/// <param name="delay">等待时间</param>
	void enableAllInputs(float delayTime);


private:
	/// <summary>
	/// 游戏场景
	/// </summary>
	GamePlayScene* _gamePlayLayer;
	GameView* _gameView;
	std::unique_ptr<GameModel> _gameModel;

	std::unique_ptr<StackController> _stackController;
	std::unique_ptr<PlayFieldController> _playFieldController;
	std::unique_ptr<UndoManager> _undoManager;

	std::shared_ptr<CardController> getPlayFieldCardController(int cardId);
	std::shared_ptr<CardController> getStackCardController(int cardId);

	cocos2d::Node* getParentView(FromZoneType zone);
	void changeParentView(cocos2d::Node* newParent, cocos2d::Node* originalParent, cocos2d::Node* self);
};

#endif