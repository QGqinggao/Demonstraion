#ifndef __LEVEL_CONFIG_LOADER_H__
#define __LEVEL_CONFIG_LOADER_H__

#include "LevelConfig.h"

/// <summary>
/// 关卡配置文件加载器
/// </summary>
class LevelConfigLoader
{
public:

	/// <summary>
	/// 关卡配置文件加载，根据关卡 id 生成 LevelConfig
	/// </summary>
	/// <param name="levelId"></param>
	/// <returns></returns>
	static LevelConfig loadLevelConfig(int levelId);

};



#endif