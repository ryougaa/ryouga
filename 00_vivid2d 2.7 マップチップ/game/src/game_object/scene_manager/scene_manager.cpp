// scene_manager.cpp
#include "scene_manager.h"
#include "title_scene/title_scene.h"
#include "gamemain_scene/gamemain_scene.h"

SCENE_ID g_SceneID = SCENE_ID::DUMMY;


void InitializeSceneManager(void)
{
	// �ŏ��ɓ����V�[���ւ̐؂�ւ�
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
	// ���݂̃V�[���Ǝ��Ɏw�肳�ꂽ�V�[���������ł���ꍇ�͏������s��Ȃ�
	if (g_SceneID == next_scene)
		return;

	// ���݂̃V�[���̉���������Ă�
	switch (g_SceneID)
	{
	case SCENE_ID::TITLE:		FinalizeTitle();		break;
	case SCENE_ID::GAMEMAIN:	FinalizeGameMain();		break;
	}

	// �V�[��ID�̍X�V
	g_SceneID = next_scene;

	// �V�����V�[���̏��������Ă�
	switch (g_SceneID)
	{
	case SCENE_ID::TITLE:		InitializeTitle();		break;
	case SCENE_ID::GAMEMAIN:	InitializeGameMain();	break;
	}
}