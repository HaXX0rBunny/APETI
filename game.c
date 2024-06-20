#include "game.h"
#include "levelEditor.h"
#include "player.h"

void Change_Mode(void)
{
	if (CP_Input_KeyTriggered(KEY_INSERT))
	{
		CP_Engine_SetNextGameStateForced(level_editor_state_init, level_editor_state_update, level_editor_state_exit);
	}
}

void Reset_Player()
{
	if (CP_Input_KeyTriggered(KEY_R))
	{
		Player_Init();
	}
}

void game_init(void)
{
	Load_Level_From_File("myLevel.lvl");
	Player_Init();
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

	Change_Mode();
	Reset_Player();

	Player_Update();
	Player_Draw();
	Bullet_Update();
	Bullet_Draw();
	Bomb_Update();
	Bomb_Draw();
	Draw_AllPlatform();
}

void game_exit(void)
{
	Save_Level_To_File("myLevel.lvl");
	Clear_Map();
}