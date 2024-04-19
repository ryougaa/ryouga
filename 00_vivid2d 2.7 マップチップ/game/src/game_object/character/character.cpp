// character.cpp

#include "character.h"
#include "../scene_manager/scene_manager.h"
#include"../stage/stage.h"

// �T�C�Y
const int g_chara_width = 48;
const int g_chara_height = 48;

// 1�}�X�ړ�����Ƃ��̎���(�t���[����)
const int g_chara_move_time = 12;

// �ړ����x�i���̂聀���ԁj
const float g_chara_move_speed = (float)GetMapChipSize() / (float)g_chara_move_time;

// ����
enum class CHARA_DIRECTION
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
};

// ���
enum class CHARA_STATE
{
	WAIT,	// �ҋ@
	MOVE,	// �ړ�
};

// �e��ϐ�
vivid::Vector2	g_CharaPos			= { 0.0f,0.0f };
vivid::Rect		g_CharaRect			= { 0,0,g_chara_width,g_chara_height };
int				g_CharaAnimeFrame	= 0;
int				g_CharaAnimeTimer	= 0;
CHARA_DIRECTION	g_CharaDirection	= CHARA_DIRECTION::DOWN;
CHARA_STATE		g_CharaState		= CHARA_STATE::WAIT;
vivid::Vector2	g_CharaSpeed		= { 0.0f,0.0f };
int				g_CharaMoveTimer	= 0;

// �ҋ@�p�̏���
void WaitCharacter(void)
{
	namespace keyboard = vivid::keyboard;

	// �L�����N�^�[�̍��W���}�b�v�`�b�v�̃}�X�ڔԍ��ɕϊ�����
	int x = (int)((g_CharaPos.x + 0.5f) / (float)GetMapChipSize());
	int y = (int)((g_CharaPos.y + 0.5f) / (float)GetMapChipSize());

	// ���͔���
	if (keyboard::Button(keyboard::KEY_ID::LEFT))
	{
		g_CharaDirection = CHARA_DIRECTION::LEFT;

		// �����̂���}�X�ڂ��������𒲂ׂ�B���ꂪtrue�i�؁j�ł���ΐi�߂Ȃ��I
		if (CheckWall(x - 1, y) != true)
		{
			g_CharaSpeed.x = -g_chara_move_speed;

			g_CharaState = CHARA_STATE::MOVE;
		}

	}
	else if (keyboard::Button(keyboard::KEY_ID::RIGHT))
	{
		g_CharaDirection = CHARA_DIRECTION::RIGHT;

		if (CheckWall(x + 1, y) != true)
		{
			g_CharaSpeed.x = g_chara_move_speed;

			g_CharaState = CHARA_STATE::MOVE;
		}
	}
	else if (keyboard::Button(keyboard::KEY_ID::UP))
	{
		g_CharaDirection = CHARA_DIRECTION::UP;

		if (CheckWall(x , y-1) != true)
		{
			g_CharaSpeed.y = -g_chara_move_speed;

			g_CharaState = CHARA_STATE::MOVE;
		}
	}
	else if (keyboard::Button(keyboard::KEY_ID::DOWN))
	{
		g_CharaDirection = CHARA_DIRECTION::DOWN;

		if (CheckWall(x , y+1) != true)
		{
			g_CharaSpeed.y = g_chara_move_speed;

			g_CharaState = CHARA_STATE::MOVE;
		}
	}
}

// �ړ��p�̏���
void MoveCharacter(void)
{

	// �L�����N�^�[�̍��W���}�b�v�`�b�v�̃}�X�ڔԍ��ɕϊ�����
	int x = (int)((g_CharaPos.x + 0.5f) / (float)GetMapChipSize());
	int y = (int)((g_CharaPos.y + 0.5f) / (float)GetMapChipSize());
	// �ړ����Ԃ̌v��
	if (++g_CharaMoveTimer >= g_chara_move_time)
	{
		// �ړ��\���Ԃ𒴂����烊�Z�b�g
		g_CharaMoveTimer = 0;
		g_CharaSpeed.x = 0;
		g_CharaSpeed.y = 0;

		// ��Ԃ�߂�
		g_CharaState = CHARA_STATE::WAIT;

		if (CheckGoal(x, y))
		{
			ChangeScene(SCENE_ID::TITLE);
		}

		return;
	}

	// �A�j���[�V�����̍X�V
	if (++g_CharaAnimeTimer > 10)
	{
		g_CharaAnimeTimer = 0;

		// �A�j���[�V�����t���[�����X�V
		++g_CharaAnimeFrame %= 3;
	}
}

// ������
void InitializeCharacter(void)
{
	g_CharaPos = GetStartPos();
}

// �X�V
void UpdateCharacter(void)
{	
	// ��Ԃɂ�鏈���̐؂�ւ�
	switch (g_CharaState)
	{
	case CHARA_STATE::WAIT:
		WaitCharacter();		// �ҋ@�̏���
		break;
	case CHARA_STATE::MOVE:		// �ړ��̏���
		MoveCharacter();
		break;
	}

	// �ړ��v�Z
	g_CharaPos.x += g_CharaSpeed.x;
	g_CharaPos.y += g_CharaSpeed.y;
}

// �`��
void DrawCharacter(void)
{
	g_CharaRect.left	= g_CharaAnimeFrame * g_chara_width;
	g_CharaRect.right	= g_CharaRect.left + g_chara_width;
	g_CharaRect.top		= (int)g_CharaDirection * g_chara_height;
	g_CharaRect.bottom	= g_CharaRect.top + g_chara_height;

	vivid::DrawTexture("data/character.png", g_CharaPos, 0xffffffff, g_CharaRect);
}
