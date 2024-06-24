#include "Boss3.h"
#include "levelEditor.h"
#include "player.h"
#include "ui.h"
#include "enemyAi.h"
#include "wof.h"
#include "quitESC.h"

void Boss3_init(void)
{
	
	Load_Level_From_File("bosslvl3.lvl");
	Player_Init(-1, 300, 0);
	Wof_Init(1500, 0, 200, 1000, 10, 3);
}

void Boss3_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

	updateEnemies();
	Player_Update();
	Player_Draw();
	Bullet_Update();
	Bullet_Draw();
	Bomb_Update();
	Bomb_Draw();

	Draw_AllPlatform();

	Wof_Draw();
	Wof_Update();

	Draw_AllPlatform();
	UI_Health();
	UI_Dash_Cooldown();

	Quit_ESC();
}

void Boss3_exit(void)
{
	Player_Ability_Init(1, 1);
	Clear_Map();
}