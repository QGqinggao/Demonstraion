#ifndef __JSON_UTILS_H__
#define __JSON_UTILS_H__

#include "cocos2d.h"
#include "json/document.h"

/// <summary>
/// JsonUtil 提供 Json 相关的静态方法
/// </summary>
class JsonUtil
{
public:
	/// <summary>
	/// 加载 Json 文件
	/// </summary>
	/// <param name="filePath">文件路径</param>
	/// <param name="outDoc"></param>
	/// <returns></returns>
	static bool loadJsonFile(const std::string& filePath, rapidjson::Document& outDoc);
};




#endif