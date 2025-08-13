#include "Utils.h"	
#include "configs/ConstValueConfig.h"

std::string Utils::cardFaceToStr(CardFaceType face)
{
    switch (face)
    {
        case CFT_TWO:      return "2";
        case CFT_THREE:    return "3";
        case CFT_FOUR:     return "4";
        case CFT_FIVE:     return "5";
        case CFT_SIX:      return "6";
        case CFT_SEVEN:    return "7";
        case CFT_EIGHT:    return "8";
        case CFT_NINE:     return "9";
        case CFT_TEN:      return "10";
        case CFT_JACK:     return "J";
        case CFT_ACE:      return "A";
        case CFT_QUEEN:    return "Q";
        case CFT_KING:     return "K";
        case CFT_NONE:
        default:           return "";
    }
}

std::string Utils::cardSuitToStr(CardSuitType suit)
{
    switch (suit)
    {
        case CST_CLUBS:    return "club";
        case CST_DIAMONDS: return "diamond";
        case CST_HEARTS:   return "heart";
        case CST_SPADES:   return "spade";
        case CST_NONE:
        default:           return "";
    }
}

bool Utils::isCardCovering(const CardModel& card1, const CardModel& card2)
{
    if (fabs(card1.position.x - card2.position.x) < kCoverThresholdX &&
        (card1.position.y > card2.position.y) &&
        fabs(card1.position.y - card2.position.y) < kCoverThresholdY)
    {
        return true;
    }
    else if (card2.position.x - card1.position.x < kCoverThresholdX &&
        card2.position.x - card1.position.x > 0 &&
        card1.position.y == card2.position.y)
    {
        return true;
    }

    return false;
}

std::string Utils::GBKToUTF8(const std::string& strGBK)
{
    std::string strOutUTF8 = "";
    WCHAR* str1;
    int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    str1 = new WCHAR[n];
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char* str2 = new char[n];
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    strOutUTF8 = str2;
    delete[]str1;
    str1 = NULL;
    delete[]str2;
    str2 = NULL;
    return strOutUTF8;
}
