// title_scene.cpp
#include "title_scene.h"
#include "vivid.h"
#include "../scene_manager.h"

void InitializeTitle(void)
{
}

void UpdataTitle(void)
{
	// ‰¼
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Z))
		ChangeScene(SCENE_ID::GAMEMAIN);
}

void DrawTitle(void)
{

#ifdef VIVID_DEBUG
	vivid::DrawText(40, "ƒ^ƒCƒgƒ‹", { 0.0f,0.0f });
#endif // VIVID_DEBUG

	vivid::DrawTexture("data\\forest.png", { 0.0f,0.0f });

}

void FinalizeTitle(void)
{
}
