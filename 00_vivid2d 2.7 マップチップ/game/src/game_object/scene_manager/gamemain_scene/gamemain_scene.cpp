// gamemain_scene.cpp
#include "gamemain_scene.h"
#include "../../stage/stage.h"
#include "../../character/character.h"

void InitializeGameMain(void)
{
	InitializeMap();

	InitializeCharacter();
}

void UpdateGameMain(void)
{
	UpdateCharacter();
}

void DrawGameMain(void)
{
	DrawMap();

	DrawCharacter();
}

void FinalizeGameMain(void)
{
}
