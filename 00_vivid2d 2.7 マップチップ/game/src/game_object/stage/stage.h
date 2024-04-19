// stage.h
#pragma once

#include "vivid.h"

void InitializeMap(void);   // �f�[�^�̓ǂݍ���
void DrawMap(void);         // �f�[�^�i�}�b�v�j�̕`��

int GetMapChipSize(void);	// �}�b�v�`�b�v�̃T�C�Y�擾

vivid::Vector2 GetStartPos(void); // �X�^�[�g�t���b�O�̂���ʒu

// �����̃}�X�ڂ̏ꏊ���ǂ��ǂ����𒲂ׂ�
// �ǂȂ�true�A�ʘH�Ȃ�false�ɂȂ�
bool CheckWall(int x, int y);

bool CheckGoal(int x, int y);