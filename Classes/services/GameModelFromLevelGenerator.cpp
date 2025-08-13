#include "GameModelFromLevelGenerator.h"
#include <new>


GameModelFromLevelGenerator* GameModelFromLevelGenerator::s_instance = nullptr;

GameModelFromLevelGenerator* GameModelFromLevelGenerator::getInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new (std::nothrow) GameModelFromLevelGenerator();
		if (!s_instance)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}
	return s_instance;
}

void GameModelFromLevelGenerator::destroyInstance()
{
	delete s_instance;
	s_instance = nullptr;
}

void GameModelFromLevelGenerator::generatorGameModel(LevelConfig& levelConfig, std::unique_ptr<GameModel>& gameModel)
{
	gameModel = std::make_unique<GameModel>();

	int idCounter = 1;

	auto initCard = [&](const CardResConfig& cfg)
		{
			CardModel card;
			card.id = idCounter++;
			card.face = cfg.face;
			card.suit = cfg.suit;
			card.position = cfg.position;
			card.canSelect = false;
			return card;
		};

	for (auto& card : levelConfig.playFieldCards)
		gameModel->playFieldCards.push_back(initCard(card));

	// REFINEME;
	// 直接更改levelConfig中的堆牌区位置
	levelConfig.stackCards[0].position = cocos2d::Vec2(265, 300);
	levelConfig.stackCards[1].position = cocos2d::Vec2(400, 300);
	levelConfig.stackCards[2].position = cocos2d::Vec2(700, 300);


	for (auto& card : levelConfig.stackCards)
		gameModel->stackCards.push_back(initCard(card));
}