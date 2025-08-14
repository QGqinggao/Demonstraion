#include "GameController.h"
#include "configs/LevelConfigLoader.h"
#include "services/GameModelFromLevelGenerator.h"
#include "views/GameView.h"
#include "PlayFieldController.h"
#include "StackController.h"

USING_NS_CC;


void GameController::init()
{
	
	_playFieldController = std::make_unique<PlayFieldController>();
	_stackController = std::make_unique<StackController>();
	_undoManager = std::make_unique<UndoManager>();

	_playFieldController->setClickCallback(
		std::bind(&GameController::handlePlayFieldCardClick, this, std::placeholders::_1)
	);
	_stackController->setCardClickCallback(
		std::bind(&GameController::handleStackCardClick, this, std::placeholders::_1)
	);
	_stackController->setButtonClickCallback(
		std::bind(&GameController::handleUndoButtonClick, this)
	);
	_undoManager->setUndoCallback(
		std::bind(&GameController::handleUndo, this, std::placeholders::_1)
	);
}

bool GameController::initView(GamePlayScene* layer)
{
	_gamePlayLayer = layer;

	_gameView = GameView::create();
	if (!_gameView) return false;
	_gamePlayLayer->addChild(_gameView);

	return true;
}

bool GameController::startGame(int levelId)
{
	LevelConfig levelConfig = LevelConfigLoader::loadLevelConfig(levelId);	
	GameModelFromLevelGenerator::getInstance()->generatorGameModel(levelConfig, _gameModel);
	if (!_gameModel) return false;

	_playFieldController->init(_gameModel->playFieldCards);
	_stackController->init(_gameModel->stackCards);

	if (!_playFieldController->initView(_gameView)) return false;
	if (!_stackController->initView(_gameView)) return false;

	_gameView->initView();

	return true;
}

void GameController::handlePlayFieldCardClick(int cardId)
{
	auto cardController = GameController::getPlayFieldCardController(cardId);
	if (!cardController)
	{
		CCLOG("THE PLAY FIELD CARD CONTROLLER IS NULL");
		return;
	}
	
	auto trayCardController = _stackController->getTrayCardController();
	if (fabs(cardController->getNumber() - trayCardController->getNumber()) == 1)
	{

		UndoStep step;
		CardMoveRecord record;

		record.fromPos = trayCardController->getView()->getPosition();
		record.toPos = trayCardController->getView()->getPosition();
		record.cardModel = trayCardController->getModel();
		record.fromZone = Tray;
		record.toZone = None;
		step.moveRecords.push_back(record);

		CardMoveRecord record2;
		record2.fromPos = cardController->getView()->getPosition();
		record2.toPos = trayCardController->getView()->getPosition();
		record2.cardModel = cardController->getModel();		
		record2.fromZone = PlayField;
		record2.toZone = Tray;
		step.moveRecords.push_back(record2);

		if (_undoManager) _undoManager->pushStep(step);

		_playFieldController->replaceTrayWithPlayFieldCard(cardId);
		auto cardView = cardController->getView();

		GameController::changeParentView(_stackController->getView(), _playFieldController->getView(), cardView);
		GameController::disableAllInputs();
		cardView->moveToPos(cocos2d::Vec2(700, 300));
		_stackController->replaceTray(cardController);
		GameController::enableAllInputs(2.0f);
	}

}

void GameController::handleStackCardClick(int cardId)
{
	auto cardController = GameController::getStackCardController(cardId);
	if (!cardController)
	{
		CCLOG("THE STACK CARD CONTROLLER IS NULL");
		return;
	}
	auto trayCardController = _stackController->getTrayCardController();

	UndoStep step;
	CardMoveRecord record;

	record.fromPos = trayCardController->getView()->getPosition();
	record.toPos = trayCardController->getView()->getPosition();

	record.cardModel = trayCardController->getModel();
	record.fromZone = Tray;
	record.toZone = None;
	step.moveRecords.push_back(record);

	CardMoveRecord record2;
	record2.fromPos = cardController->getView()->getPosition();
	record2.toPos = trayCardController->getView()->getPosition();
	record2.cardModel = cardController->getModel();
	record2.fromZone = Stack;
	record2.toZone = Tray;
	step.moveRecords.push_back(record2);

	if (_undoManager) _undoManager->pushStep(step);
	_stackController->replaceTrayWithStack(cardId);
	auto cardView = cardController->getView();
	GameController::disableAllInputs();
	cardView->moveToPos(cocos2d::Vec2(700, 300));
	_stackController->replaceTray(cardController);
	GameController::enableAllInputs(2.0f);
}

void GameController::handleUndoButtonClick()
{
	_undoManager->undoLastStep();
}

void GameController::handleUndo(const UndoStep& step)
{
	std::shared_ptr<CardController> trayCardController;
	std::shared_ptr<CardController> cardController = _stackController->getTrayCardController();
	for (auto& record : step.moveRecords)
	{	

		if (record.toZone == None)			
		{
			CardModel model = record.cardModel;
			model.position = record.toPos;
			trayCardController = std::make_shared<CardController>();
			trayCardController->init(std::make_shared<CardModel>(model));
			trayCardController->initView(GameController::getParentView(record.fromZone));	
			_stackController->setTrayCardController(trayCardController);
		}
		else
		{
			if (record.fromZone == PlayField)
			{
				_playFieldController->pushController(cardController);
				_playFieldController->pushModel(cardController->getModel());
				_playFieldController->registerCardClickCallback(trayCardController);
			}
			else
			{
				_stackController->pushController(cardController);
				_stackController->pushModel(cardController->getModel());
			}
			auto cardView = cardController->getView();
			GameController::changeParentView(GameController::getParentView(record.fromZone), GameController::getParentView(record.toZone), cardView);
			GameController::disableAllInputs();
			cardView->moveToPos(record.fromPos);
			GameController::enableAllInputs(2.0f);
		}
	} 

	_playFieldController->updateCoverRelations();
	_stackController->updateCoverRelations();

}

std::shared_ptr<CardController> GameController::getPlayFieldCardController(int cardId)
{
	return _playFieldController->getCardController(cardId);
}

std::shared_ptr<CardController> GameController::getStackCardController(int cardId)
{
	return _stackController->getCardController(cardId);
}

cocos2d::Node* GameController::getParentView(FromZoneType zone)
{
	if (zone == PlayField)
		return _playFieldController->getView();
	else if (zone == Stack)
		return _stackController->getView();
	else
		return _stackController->getView();
}

void GameController::changeParentView(cocos2d::Node* newParent, cocos2d::Node* originalParent, cocos2d::Node* self)
{
	Vec2 worldPos = originalParent->convertToWorldSpace(self->getPosition());
	self->retain();
	originalParent->removeChild(self, false);
	Vec2 localPos = newParent->convertToNodeSpace(worldPos);
	self->setPosition(localPos);
	newParent->addChild(self);
}

void GameController::disableAllInputs() {
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->pauseEventListenersForTarget(_gameView, true);
}

void GameController::enableAllInputs(float delayTime) {
	auto delay = cocos2d::DelayTime::create(delayTime);
	auto callback = cocos2d::CallFunc::create([=]() {
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->resumeEventListenersForTarget(_gameView, true);
		});

	_gameView->runAction(cocos2d::Sequence::create(delay, callback, nullptr));
}