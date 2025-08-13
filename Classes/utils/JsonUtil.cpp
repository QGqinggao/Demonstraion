#include "JsonUtil.h"
#include "platform/CCFileUtils.h"
#include "json/error/en.h"


bool JsonUtil::loadJsonFile(const std::string& filePath, rapidjson::Document& outDoc)
{
	std::string content = cocos2d::FileUtils::getInstance()->getStringFromFile(filePath);
	if (content.empty())
	{
		cocos2d::log("JsonUtil: Failed to read file %s", filePath.c_str());
		return false;
	}

	outDoc.Parse(content.c_str());
	if (outDoc.HasParseError())
	{
		cocos2d::log("JsonUtil: Parse error at offset %zu: %s",
			outDoc.GetErrorOffset(),
			rapidjson::GetParseError_En(outDoc.GetParseError()));
		return false;
	}

	return true;
}
