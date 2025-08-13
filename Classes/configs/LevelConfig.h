#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include "CardResConfig.h"
#include "json/document.h"
#include <string>

/// <summary>
/// 关卡配置数据
/// </summary>
class LevelConfig
{
public:

    std::vector<CardResConfig> playFieldCards;
    std::vector<CardResConfig> stackCards;

    /// <summary>
    /// 生成关卡
    /// </summary>
    /// <param name="doc"></param>
    void generateConfig(const rapidjson::Document& doc)
    {
        playFieldCards.clear();
        stackCards.clear();

        auto parseCards = [&](const rapidjson::Value& arr, std::vector<CardResConfig>& out)
            {
                if (!arr.IsArray()) {
                    CCLOG("解析失败：不是数组");
                    return;
                }

                for (rapidjson::SizeType i = 0; i < arr.Size(); ++i) {  
                    const rapidjson::Value& val = arr[i];

                    CardResConfig card;
                    card.face = static_cast<CardFaceType>(val["CardFace"].GetInt());
                    card.suit = static_cast<CardSuitType>(val["CardSuit"].GetInt());
                    card.position = cocos2d::Vec2(val["Position"]["x"].GetFloat(), val["Position"]["y"].GetFloat());  // 正确路径
                    out.push_back(card);
                }
            };

        parseCards(doc["Playfield"], playFieldCards);
        parseCards(doc["Stack"], stackCards);
    }
};



#endif