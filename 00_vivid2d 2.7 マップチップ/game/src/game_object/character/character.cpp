// character.cpp

#include "character.h"
#include "../scene_manager/scene_manager.h"
#include"../stage/stage.h"

// サイズ
const int g_chara_width = 48;
const int g_chara_height = 48;

// 1マス移動するときの時間(フレーム数)
const int g_chara_move_time = 12;

// 移動速度（道のり÷時間）
const float g_chara_move_speed = (float)GetMapChipSize() / (float)g_chara_move_time;

// 向き
enum class CHARA_DIRECTION
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
};

// 状態
enum class CHARA_STATE
{
	WAIT,	// 待機
	MOVE,	// 移動
};

// 各種変数
vivid::Vector2	g_CharaPos			= { 0.0f,0.0f };
vivid::Rect		g_CharaRect			= { 0,0,g_chara_width,g_chara_height };
int				g_CharaAnimeFrame	= 0;
int				g_CharaAnimeTimer	= 0;
CHARA_DIRECTION	g_CharaDirection	= CHARA_DIRECTION::DOWN;
CHARA_STATE		g_CharaState		= CHARA_STATE::WAIT;
vivid::Vector2	g_CharaSpeed		= { 0.0f,0.0f };
int				g_CharaMoveTimer	= 0;

// 待機用の処理
void WaitCharacter(void)
{
	namespace keyboard = vivid::keyboard;

	// キャラクターの座標をマップチップのマス目番号に変換する
	int x = (int)((g_CharaPos.x + 0.5f) / (float)GetMapChipSize());
	int y = (int)((g_CharaPos.y + 0.5f) / (float)GetMapChipSize());

	// 入力判定
	if (keyboard::Button(keyboard::KEY_ID::LEFT))
	{
		g_CharaDirection = CHARA_DIRECTION::LEFT;

		// 自分のいるマス目から一つ左側を調べる。これがtrue（木）であれば進めない！
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

// 移動用の処理
void MoveCharacter(void)
{

	// キャラクターの座標をマップチップのマス目番号に変換する
	int x = (int)((g_CharaPos.x + 0.5f) / (float)GetMapChipSize());
	int y = (int)((g_CharaPos.y + 0.5f) / (float)GetMapChipSize());
	// 移動時間の計測
	if (++g_CharaMoveTimer >= g_chara_move_time)
	{
		// 移動可能時間を超えたらリセット
		g_CharaMoveTimer = 0;
		g_CharaSpeed.x = 0;
		g_CharaSpeed.y = 0;

		// 状態を戻す
		g_CharaState = CHARA_STATE::WAIT;

		if (CheckGoal(x, y))
		{
			ChangeScene(SCENE_ID::TITLE);
		}

		return;
	}

	// アニメーションの更新
	if (++g_CharaAnimeTimer > 10)
	{
		g_CharaAnimeTimer = 0;

		// アニメーションフレームを更新
		++g_CharaAnimeFrame %= 3;
	}
}

// 初期化
void InitializeCharacter(void)
{
	g_CharaPos = GetStartPos();
}

// 更新
void UpdateCharacter(void)
{	
	// 状態による処理の切り替え
	switch (g_CharaState)
	{
	case CHARA_STATE::WAIT:
		WaitCharacter();		// 待機の処理
		break;
	case CHARA_STATE::MOVE:		// 移動の処理
		MoveCharacter();
		break;
	}

	// 移動計算
	g_CharaPos.x += g_CharaSpeed.x;
	g_CharaPos.y += g_CharaSpeed.y;
}

// 描画
void DrawCharacter(void)
{
	g_CharaRect.left	= g_CharaAnimeFrame * g_chara_width;
	g_CharaRect.right	= g_CharaRect.left + g_chara_width;
	g_CharaRect.top		= (int)g_CharaDirection * g_chara_height;
	g_CharaRect.bottom	= g_CharaRect.top + g_chara_height;

	vivid::DrawTexture("data/character.png", g_CharaPos, 0xffffffff, g_CharaRect);
}
