#include "GamePlayScene.h"
#include "controllers/GameController.h"
#include "configs/LevelConfigLoader.h"

USING_NS_CC;

Scene* GamePlayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GamePlayScene::create();

	scene->addChild(layer);
	return scene;
}

bool GamePlayScene::init()
{
	if (!Layer::init()) return false;

	// 用户选择关卡
	// 选择关卡之后，由按键触发调用startGame
	// ToChange
	// 已经配置好关卡

	GameController* gameController = new GameController();

	gameController->init();
	if (!gameController->initView(this)) return false;

	if (!gameController->startGame(1)) return false;

	return true;
}