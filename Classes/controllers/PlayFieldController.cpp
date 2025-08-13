#include "PlayFieldController.h"
#include "views/CardView.h"
#include <utils/Utils.h>


void PlayFieldController::init(const std::vector<CardModel>& playFieldCards)
{
	if (playFieldCards.empty()) return;
	_playFieldCards = playFieldCards;

	PlayFieldController::initCoverRelations();

	_playFieldCardControllers.clear();

	for (const auto cardModel : _playFieldCards)
	{
		auto cardController = std::make_shared<CardController>();
		cardController->init(std::make_shared<CardModel>(cardModel));
		cardController->setClickCallback(
			std::bind(&PlayFieldController::_onCardClickCallback, this, std::placeholders::_1)
		);
		_playFieldCardControllers.push_back(cardController);
	}
}

bool PlayFieldController::initView(cocos2d::Node* parentNode)
{
	_playFieldView = PlayFieldView::create();
	if (!_playFieldView) return false;
	parentNode->addChild(_playFieldView);

	for (auto& cardController : _playFieldCardControllers)
	{
		if (!cardController) return false;
		if (!cardController->initView(_playFieldView)) return false;
	}

	return true;
}

void PlayFieldController::initCoverRelations()
{
	_coverMap.clear();

	for (auto& card1 : _playFieldCards)
	{
		for (auto& card2 : _playFieldCards)
		{
			if (card1.id != card2.id && Utils::isCardCovering(card1, card2))
			{
				_coverMap[card1.id].push_back(card2.id);
			}
		}
	}

	for (auto& card : _playFieldCards)
	{
		card.canSelect = _coverMap[card.id].empty();
	}
}

void PlayFieldController::updateCoverRelations()
{
	PlayFieldController::initCoverRelations();

	for (auto cardController : _playFieldCardControllers)
	{
		cardController->setCanSelect(PlayFieldController::getCardModel(cardController->getCardId()).id);
	}
}

void PlayFieldController::pushController(std::shared_ptr<CardController> cardController)
{
	_playFieldCardControllers.push_back(cardController);
}

void PlayFieldController::pushModel(CardModel& model)
{
	_playFieldCards.push_back(model);
}

PlayFieldView* PlayFieldController::getView()
{
	return _playFieldView;
}

void PlayFieldController::_onCardClickCallback(int cardId)
{
	PlayFieldController::handleCardClick(cardId);
}

void PlayFieldController::handleCardClick(int cardId)
{
	CCLOG("playfieldcontroller handle click");

	_cardClickCallback(cardId);
}

CardModel& PlayFieldController::getCardModel(int cardId)
{
	for (auto& cardModel : _playFieldCards)
	{
		if (cardModel.id == cardId)
		{
			return cardModel;
		}
	}
	return CardModel();
}

std::shared_ptr<CardController> PlayFieldController::getCardController(int cardId)
{
	for (auto cardController : _playFieldCardControllers)
	{
		if (cardController->getCardId() == cardId)
		{
			return cardController;
		}
	}

	return nullptr;
}

void PlayFieldController::replaceTrayWithPlayFieldCard(int cardId)
{
	auto itCardModel = std::remove_if(
		_playFieldCards.begin(),
		_playFieldCards.end(),
		[cardId](const CardModel& cardModel) {
			return cardModel.id == cardId;
		}
	);
	_playFieldCards.erase(itCardModel, _playFieldCards.end());

	auto itCardController = std::remove_if(
		_playFieldCardControllers.begin(),
		_playFieldCardControllers.end(),
		[cardId](const std::shared_ptr<CardController> cardController) {
			return cardController->getCardId() == cardId;
		}
	);
	_playFieldCardControllers.erase(itCardController, _playFieldCardControllers.end());

	PlayFieldController::updateCoverRelations();
}

