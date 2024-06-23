#include "game.h"
#include "levelEditor.h"
#include "player.h"
#include "ui.h"
#include "enemyAi.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "quitESC.h"

void Change_Mode(void)
{
	if (CP_Input_KeyTriggered(KEY_INSERT))
	{
		CP_Engine_SetNextGameStateForced(level_editor_state_init, level_editor_state_update, level_editor_state_exit);
	}
}

void Enter_Boss1(void)
{
	CP_Engine_SetNextGameState(Boss1_init, Boss1_update, Boss1_exit);
}

void Enter_Boss2(void)
{
	CP_Engine_SetNextGameState(Boss2_init, Boss2_update, Boss2_exit);
}

void Enter_Boss3(void)
{
	CP_Engine_SetNextGameState(Boss3_init, Boss3_update, Boss3_exit);
}

void game_init(void)
{
	Load_Level_From_File("myLevel.lvl");
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

	Change_Mode();
	updateEnemies();
	Player_Update();
	Player_Draw();
	Bullet_Update();
	Bullet_Draw();
	Bomb_Update();
	Bomb_Draw();

	Draw_AllPlatform();
	
	UI_Health();
	UI_Dash_Cooldown();

	UI_Health();
	UI_Dash_Cooldown();
	Draw_AllPlatform();

	Quit_ESC();
}

void game_exit(void)
{
	Clear_Map();
}