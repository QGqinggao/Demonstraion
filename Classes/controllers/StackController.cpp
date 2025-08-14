#include "StackController.h"
#include <utils/Utils.h>


void StackController::init(const std::vector<CardModel>& stackCards)
{
	if (stackCards.empty()) return;
	_stackCards = stackCards;

	StackController::initCoverRelations();

	_stackCardControllers.clear();

	for (auto cardModel : _stackCards)
	{
		auto cardController = std::make_shared<CardController>();
		cardController->init(std::make_shared<CardModel>(cardModel));
		cardController->setClickCallback(
			std::bind(&StackController::_onCardClickCallback, this, std::placeholders::_1)
		);
		_stackCardControllers.push_back(cardController);
	}

}

bool StackController::initView(cocos2d::Node* parentLayer)
{
	_stackView = StackView::create();
	if (!_stackView) return false;
	parentLayer->addChild(_stackView);

	for (auto& cardController : _stackCardControllers)
	{
		if (!cardController) return false;
		if (!cardController->initView(_stackView)) return false;
	}

	StackController::initTrayCardController();
	_stackView->setButtonClickCallback(_buttonClickCallback);

	return true;
}

void StackController::initCoverRelations()
{
	_coverMap.clear();

	for (auto& card1 : _stackCards)
	{
		for (auto& card2 : _stackCards)
		{
			if (card1.id != card2.id && Utils::isCardCovering(card1, card2))
			{
				_coverMap[card1.id].push_back(card2.id);
			}
		}
	}

	for (auto& card : _stackCards)
	{
		card.canSelect = _coverMap[card.id].empty();
	}
}

void StackController::updateCoverRelations()
{
	StackController::initCoverRelations();

	for (auto cardController : _stackCardControllers)
	{
		auto cardModel = StackController::getCardModel(cardController->getCardId());
		cardController->setCanSelect(cardModel.canSelect);
		std::string str = (cardModel.canSelect ? "true" : "false");
		CCLOG("The Card %d is can select : %s", cardModel.id, str.c_str());
	}
}

void StackController::initTrayCardController() 
{
	for (auto cardModel : _stackCards)
	{
		if (cardModel.position.x == 700)
		{
			int cardId = cardModel.id;
			_trayCardController = this->getCardController(cardId);

			auto ctrlIt = std::find_if(_stackCardControllers.begin(), _stackCardControllers.end(),
				[cardId](const std::shared_ptr<CardController> ctrl) {
					return ctrl->getCardId() == cardId;
				});

			if (ctrlIt != _stackCardControllers.end())
			{
				_stackCardControllers.erase(ctrlIt);
			}
		}
	}

	CCLOG("zxzczczczczczczc %d", _stackCardControllers.size());
}

void StackController::pushController(std::shared_ptr<CardController> cardController)
{
	_stackCardControllers.push_back(cardController);
}

void StackController::pushModel(CardModel& model)
{
	_stackCards.push_back(model);
}

cocos2d::Node* StackController::getView()
{
	return _stackView;
}

void StackController::_onCardClickCallback(int cardId)
{

	StackController::handleCardClick(cardId);
}

void StackController::handleCardClick(int cardId)
{
	CCLOG("stack controller handle click");

	_cardClickCallback(cardId);
}

CardModel& StackController::getCardModel(int cardId)
{
	for (auto& cardModel : _stackCards)
	{
		if (cardModel.id == cardId)
		{
			return cardModel;
		}
	}
	return CardModel();
}

std::shared_ptr<CardController> StackController::getCardController(int cardId)
{
	for (auto& cardController : _stackCardControllers)
	{
		if (cardController->getCardId() == cardId)
		{
			return cardController;
		}
	}

	return nullptr;
}

std::shared_ptr<CardController> StackController::getTrayCardController()
{
	if (_trayCardController)
		return _trayCardController;

	return nullptr;
}

void StackController::setTrayCardController(std::shared_ptr<CardController> newTrayCardController)
{
	_trayCardController = newTrayCardController;
}

void StackController::replaceTray(std::shared_ptr<CardController> newTrayCardController)
{
	if (_trayCardController)
	{
		auto view = _trayCardController->getView();
		_trayCardController = newTrayCardController;
		auto delay = cocos2d::DelayTime::create(2.0f);
		auto callback = cocos2d::CallFunc::create([=]() {
			view->removeFromParent();
			});

		_stackView->runAction(cocos2d::Sequence::create(delay, callback, nullptr));
	}
}

void StackController::replaceTrayWithStack(int cardId)
{
	auto itCardModel = std::remove_if(
		_stackCards.begin(),
		_stackCards.end(),
		[cardId](const CardModel& cardModel) {
			return cardModel.id == cardId;
		}
	);
	_stackCards.erase(itCardModel, _stackCards.end());

	auto itCardController = std::remove_if(
		_stackCardControllers.begin(),
		_stackCardControllers.end(),
		[cardId](const std::shared_ptr<CardController> cardController) {
			return cardController->getCardId() == cardId;
		}
	);
	_stackCardControllers.erase(itCardController, _stackCardControllers.end());

	StackController::updateCoverRelations();
}

void StackController::registerCardClickCallback(std::shared_ptr<CardController> cardController)
{
	cardController->setClickCallback(
		std::bind(&StackController::_onCardClickCallback, this, std::placeholders::_1)
	);
}