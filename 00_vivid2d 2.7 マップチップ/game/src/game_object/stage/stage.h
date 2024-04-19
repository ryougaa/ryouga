// stage.h
#pragma once

#include "vivid.h"

void InitializeMap(void);   // データの読み込み
void DrawMap(void);         // データ（マップ）の描画

int GetMapChipSize(void);	// マップチップのサイズ取得

vivid::Vector2 GetStartPos(void); // スタートフラッグのある位置

// 引数のマス目の場所が壁かどうかを調べる
// 壁ならtrue、通路ならfalseになる
bool CheckWall(int x, int y);

bool CheckGoal(int x, int y);