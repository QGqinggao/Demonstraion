#include "CardController.h"

void CardController::init(std::shared_ptr<CardModel> cardModel)
{
	_cardModel = cardModel;
}

bool CardController::initView(cocos2d::Node* gameLayer)
{
	_cardView = CardView::create();
	if (!_cardView) return false;
	_cardView->initViewWithModel(_cardModel);
	gameLayer->addChild(_cardView, 10);

	CardController::registerCardViewCallback();

	return true;
}

int CardController::getCardId()
{
	return _cardModel->id;
}

int CardController::getNumber()
{
	int number = static_cast<int>(_cardModel->face);
	return number;
}

CardView* CardController::getView()
{
	return _cardView;
}

CardModel CardController::getModel()
{
	return *_cardModel;
}

void CardController::setCanSelect(bool canSelect)
{
	_cardModel->canSelect = canSelect;
}

void CardController::registerCardViewCallback()
{
	_cardView->setClickCallback(
		std::bind(&CardController::handleCardClick, this)
	);
}

void CardController::handleCardClick()
{
	if (!_cardModel->canSelect)
		return;

	if (_cardClickCallback)
		_cardClickCallback(_cardModel->id);
}