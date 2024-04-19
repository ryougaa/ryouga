// stage.cpp
#include "stage.h"

const int g_map_chip_size = 48;
const int g_map_chip_count_width = vivid::WINDOW_WIDTH / g_map_chip_size + 1;
const int g_map_chip_count_height = vivid::WINDOW_HEIGHT / g_map_chip_size;

// マップチップ番号を列挙型で定義
enum class MAP_CHIP_ID
{
    ENPTY,          // 何もない
    TREE,           // 木（茂み）
    START_FLAG,     // スタート
    GOAL_FLAG,      // ゴール
};

// 配置データを入れておくための二次元配列（整数）
unsigned char g_Map[g_map_chip_count_height][g_map_chip_count_width] =
{ (unsigned char)MAP_CHIP_ID::ENPTY };

void InitializeMap(void)
{
    /*
     *ファイルの読み込み
     */

    FILE* fp = nullptr;

    //ファイルを開く
    fopen_s(&fp, "data\\map.csv", "r");

    // サイズを調べる
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // サイズ分だけ入れ物を用意する（一時的なデータ）
    char* buf = new char[size];

    // データ（CSVファイル内の文字列）を読み込む
    fread(buf, size, 1, fp);

    fclose(fp);

    /*
     *データの解析
     */
     // データのサイズ分繰り返し
    for (int i = 0, k = 0; i < size; ++i)
    {
        // 文字の0～3であれば数値に変換する
        if (buf[i] >= '0' && buf[i] <= '3')
        {
            char t = buf[i];
            g_Map[k / g_map_chip_count_width]
                [k % g_map_chip_count_width] =
                (unsigned char)atoi(&t);
            ++k;
        }
    }
    // 一時的なデータを削除
    delete[]buf;
    buf = nullptr;
}

void DrawMap(void)
{
    // 背景の描画
    vivid::DrawTexture("data/field.png", { 0.0f,0.0f });

    // 要素数分繰り返す
    for (int i = 0; i < g_map_chip_count_height; ++i)
    {
        for (int k = 0; k < g_map_chip_count_width; ++k)
        {
            vivid::Vector2 pos;
            pos.x = (float)(k * g_map_chip_size);
            pos.y = (float)(i * g_map_chip_size);

            // 読み込み範囲を求める
            vivid::Rect rect;
            rect.left = g_Map[i][k] * g_map_chip_size;
            rect.top = 0;
            rect.right = rect.left + g_map_chip_size;
            rect.bottom = rect.top + g_map_chip_size;
            // 描画
            vivid::DrawTexture("data\\map_chip.png", pos, 0xffffffff, rect);
        }
    }
}

int GetMapChipSize(void)
{
    return g_map_chip_size;
}

vivid::Vector2 GetStartPos(void)
{
    vivid::Vector2 pos = { 0.0f,0.0f };

    for (int i = 0; i < g_map_chip_count_height; ++i)
    {
        for (int k = 0; k < g_map_chip_count_width; ++k)
        {
            // スタートフラッグを探す
            if (g_Map[i][k] == (unsigned char)MAP_CHIP_ID::START_FLAG)
            {
                // 見つかったら座標をposに入れる
                pos.x = (float)(k * g_map_chip_size);
                pos.y = (float)(i * g_map_chip_size);
                return pos;
            }
        }
    }

    return pos;
}

bool CheckWall(int x, int y)
{
    if (x < 0) x = 0;
    if (x > g_map_chip_count_width) x = g_map_chip_count_width - 1;
    if (y < 0) y = 0;
    if (y > g_map_chip_count_height)y = g_map_chip_count_height - 1;

    // IDが木なら進めない
    if (g_Map[y][x] == (unsigned char)MAP_CHIP_ID::TREE)
        return true;

    return false;
}

bool CheckGoal(int x, int y)
{
    if (x < 0) x = 0;
    if (x > g_map_chip_count_width) x = g_map_chip_count_width - 1;
    if (y < 0) y = 0;
    if (y > g_map_chip_count_height)y = g_map_chip_count_height - 1;


    if (g_Map[y][x] == (unsigned char)MAP_CHIP_ID::GOAL_FLAG)
        return true;

    return false;
}
