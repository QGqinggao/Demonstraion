#ifndef __UTILS_H__
#define __UTILS_H__

#include "models/CardModel.h"
#include <string>

/// <summary>
/// Utils类，提供静态通用方法
/// </summary>
class Utils
{
public:
	/// <summary>
	/// 将 CardFaceType enum 类型转换为 string 类型
	/// </summary>
	/// <param name="face"></param>
	/// <returns></returns>
	static std::string cardFaceToStr(CardFaceType face);
	/// <summary>
	/// 将 CardSuitType enum 类型转换为 string 类型
	/// </summary>
	/// <param name="suit"></param>
	/// <returns></returns>
	static std::string cardSuitToStr(CardSuitType suit);
	/// <summary>
	/// 检测卡牌与卡牌之间是否有覆盖关系
	/// </summary>
	/// <param name="card1">检测是否被覆盖卡牌</param>
	/// <param name="card2">检测是否覆盖其它卡牌</param>
	/// <returns></returns>
	static bool isCardCovering(const CardModel& card1, const CardModel& card2);
	/// <summary>
	/// 将 GBK 编码转换为 UTF-8 编码，用于 vs 中文字体编码转换
	/// </summary>
	/// <param name="strGBK"></param>
	/// <returns></returns>
	static std::string GBKToUTF8(const std::string& strGBK);

};






#endif 