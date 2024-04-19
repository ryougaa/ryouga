// scene_manager.h
#pragma once
#include "scene_id.h"

void InitializeSceneManager(void);

void UpdateSceneManager(void);

void DrawSceneManager(void);

void FinalizeSceneManager(void);

void ChangeScene(SCENE_ID next_scene);