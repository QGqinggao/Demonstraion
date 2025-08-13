#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"

/// <summary>
/// GamePlay 游戏主场景
/// </summary>
class GamePlayScene : public cocos2d::Layer
{

public:

	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(GamePlayScene);
};

#endif