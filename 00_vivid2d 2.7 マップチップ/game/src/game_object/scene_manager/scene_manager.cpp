// scene_manager.cpp
#include "scene_manager.h"
#include "title_scene/title_scene.h"
#include "gamemain_scene/gamemain_scene.h"

SCENE_ID g_SceneID = SCENE_ID::DUMMY;


void InitializeSceneManager(void)
{
	// 最初に動くシーンへの切り替え
	ChangeScene(SCENE_ID::TITLE);
}

void UpdateSceneManager(void)
{
	switch (g_SceneID)
	{
	case SCENE_ID::TITLE:		UpdataTitle();			break;
	case SCENE_ID::GAMEMAIN:	UpdateGameMain();		break;
	}
}

void DrawSceneManager(void)
{
	switch (g_SceneID)
	{
	case SCENE_ID::TITLE:		DrawTitle();			break;
	case SCENE_ID::GAMEMAIN:	DrawGameMain();			break;
	}
}

void FinalizeSceneManager(void)
{
}

void ChangeScene(SCENE_ID next_scene)
{
	// 現在のシーンと次に指定されたシーンが同じである場合は処理を行わない
	if (g_SceneID == next_scene)
		return;

	// 現在のシーンの解放処理を呼ぶ
	switch (g_SceneID)
	{
	case SCENE_ID::TITLE:		FinalizeTitle();		break;
	case SCENE_ID::GAMEMAIN:	FinalizeGameMain();		break;
	}

	// シーンIDの更新
	g_SceneID = next_scene;

	// 新しいシーンの初期化を呼ぶ
	switch (g_SceneID)
	{
	case SCENE_ID::TITLE:		InitializeTitle();		break;
	case SCENE_ID::GAMEMAIN:	InitializeGameMain();	break;
	}
}