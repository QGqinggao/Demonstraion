#ifndef __CARD_RES_CONFIG_H__
#define __CARD_RES_CONFIG_H__

#include "cocos2d.h"
#include "models/CardModel.h"

/// <summary>
/// 卡牌图形资源
/// </summary>
class CardResConfig
{
public:

	CardFaceType face;
	CardSuitType suit;
	cocos2d::Vec2 position;
};



#endif