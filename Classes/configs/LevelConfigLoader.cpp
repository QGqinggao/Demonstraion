#include "LevelConfigLoader.h"
#include "utils/JsonUtil.h"

LevelConfig LevelConfigLoader::loadLevelConfig(int levelId)
{
	std::string filePath = cocos2d::StringUtils::format("configs/levels/LevelConfig_%d.json", levelId);

	rapidjson::Document doc;
	if (!JsonUtil::loadJsonFile(filePath, doc))
	{
		return LevelConfig();
	}

	LevelConfig config;
	config.generateConfig(doc);

	return config;

}