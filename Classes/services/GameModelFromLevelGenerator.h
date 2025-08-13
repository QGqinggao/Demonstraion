#ifndef __GAME_MODEL_FROM_LEVEL_GENERATOR_H__
#define __GAME_MODEL_FROM_LEVEL_GENERATOR_H__

#include "models/GameModel.h"
#include "configs/LevelConfig.h"

/// <summary>
/// 关卡数据转换为 GameModel，单例
/// </summary>
class GameModelFromLevelGenerator
{
public:
	static GameModelFromLevelGenerator* getInstance();
	static void destroyInstance();

	/// <summary>
	/// 关卡数据生成 GameModel 方法
	/// </summary>
	/// <param name="levelConfig">关卡数据</param>
	/// <param name="gameModel">需要生成的 GameModel 智能指针</param>
	void generatorGameModel(LevelConfig& levelConfig, std::unique_ptr<GameModel>& gameModel);

private:

	static GameModelFromLevelGenerator* s_instance;
};





#endif