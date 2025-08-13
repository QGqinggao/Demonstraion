#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include "CardModel.h"

/// <summary>
/// 游戏数据
/// </summary>
class GameModel
{
public:

	std::vector<CardModel> playFieldCards;
	std::vector<CardModel> stackCards;

};



#endif