// stage.cpp
#include "stage.h"

const int g_map_chip_size = 48;
const int g_map_chip_count_width = vivid::WINDOW_WIDTH / g_map_chip_size + 1;
const int g_map_chip_count_height = vivid::WINDOW_HEIGHT / g_map_chip_size;

// �}�b�v�`�b�v�ԍ���񋓌^�Œ�`
enum class MAP_CHIP_ID
{
    ENPTY,          // �����Ȃ�
    TREE,           // �؁i�΂݁j
    START_FLAG,     // �X�^�[�g
    GOAL_FLAG,      // �S�[��
};

// �z�u�f�[�^�����Ă������߂̓񎟌��z��i�����j
unsigned char g_Map[g_map_chip_count_height][g_map_chip_count_width] =
{ (unsigned char)MAP_CHIP_ID::ENPTY };

void InitializeMap(void)
{
    /*
     *�t�@�C���̓ǂݍ���
     */

    FILE* fp = nullptr;

    //�t�@�C�����J��
    fopen_s(&fp, "data\\map.csv", "r");

    // �T�C�Y�𒲂ׂ�
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // �T�C�Y���������ꕨ��p�ӂ���i�ꎞ�I�ȃf�[�^�j
    char* buf = new char[size];

    // �f�[�^�iCSV�t�@�C�����̕�����j��ǂݍ���
    fread(buf, size, 1, fp);

    fclose(fp);

    /*
     *�f�[�^�̉��
     */
     // �f�[�^�̃T�C�Y���J��Ԃ�
    for (int i = 0, k = 0; i < size; ++i)
    {
        // ������0�`3�ł���ΐ��l�ɕϊ�����
        if (buf[i] >= '0' && buf[i] <= '3')
        {
            char t = buf[i];
            g_Map[k / g_map_chip_count_width]
                [k % g_map_chip_count_width] =
                (unsigned char)atoi(&t);
            ++k;
        }
    }
    // �ꎞ�I�ȃf�[�^���폜
    delete[]buf;
    buf = nullptr;
}

void DrawMap(void)
{
    // �w�i�̕`��
    vivid::DrawTexture("data/field.png", { 0.0f,0.0f });

    // �v�f�����J��Ԃ�
    for (int i = 0; i < g_map_chip_count_height; ++i)
    {
        for (int k = 0; k < g_map_chip_count_width; ++k)
        {
            vivid::Vector2 pos;
            pos.x = (float)(k * g_map_chip_size);
            pos.y = (float)(i * g_map_chip_size);

            // �ǂݍ��ݔ͈͂����߂�
            vivid::Rect rect;
            rect.left = g_Map[i][k] * g_map_chip_size;
            rect.top = 0;
            rect.right = rect.left + g_map_chip_size;
            rect.bottom = rect.top + g_map_chip_size;
            // �`��
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
            // �X�^�[�g�t���b�O��T��
            if (g_Map[i][k] == (unsigned char)MAP_CHIP_ID::START_FLAG)
            {
                // ������������W��pos�ɓ����
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

    // ID���؂Ȃ�i�߂Ȃ�
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
