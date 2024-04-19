// game.cpp
#include "game.h"
#include "../game_object/stage/stage.h"
#include "../game_object/character/character.h"
#include "../game_object/scene_manager/scene_manager.h"
#include "../game_object/stage/stage.h"

void InitializeGame(void)
{
	// �V�[���}�l�[�W���[�̏�����
	InitializeSceneManager();
}

void UpdateGame(void)
{
	// �V�[���}�l�[�W���[�̍X�V
	UpdateSceneManager();
}

void DrawGame(void)
{
	// �V�[���}�l�[�W���[�̕`��
	DrawSceneManager();
}

void FinalizeGame(void)
{
	// �V�[���}�l�[�W���[�̉��
	FinalizeSceneManager();
}
