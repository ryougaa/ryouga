// game.cpp
#include "game.h"
#include "../game_object/stage/stage.h"
#include "../game_object/character/character.h"
#include "../game_object/scene_manager/scene_manager.h"
#include "../game_object/stage/stage.h"

void InitializeGame(void)
{
	// シーンマネージャーの初期化
	InitializeSceneManager();
}

void UpdateGame(void)
{
	// シーンマネージャーの更新
	UpdateSceneManager();
}

void DrawGame(void)
{
	// シーンマネージャーの描画
	DrawSceneManager();
}

void FinalizeGame(void)
{
	// シーンマネージャーの解放
	FinalizeSceneManager();
}
