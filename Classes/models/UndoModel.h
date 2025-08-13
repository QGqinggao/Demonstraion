#ifndef __UNDO_MODEL_H__
#define __UNDO_MODEL_H__

#include "cocos2d.h"
#include "models/CardModel.h"

enum FromZoneType
{
    PlayField,
    Stack,
    Tray,
    None
};

/// <summary>
/// 卡牌移动记录
/// </summary>
struct CardMoveRecord 
{     
    cocos2d::Vec2 fromPos; 
    cocos2d::Vec2 toPos;   
    cocos2d::Node* fromParent;      
    cocos2d::Node* toParent;
    CardModel cardModel;
    FromZoneType fromZone;
    FromZoneType toZone;
};

/// <summary>
/// 撤销步骤
/// </summary>
struct UndoStep
{
    std::vector<CardMoveRecord> moveRecords;
};

/// <summary>
/// 撤销数据
/// </summary>
class UndoModel 
{
public:
    std::vector<UndoStep> steps;
};


#endif