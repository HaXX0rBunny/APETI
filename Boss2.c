#include "Boss2.h"
#include "levelEditor.h"
#include "player.h"
#include "ui.h"
#include "enemyAi.h"
#include "sanic.h"
#include "quitESC.h"

void Boss2_init(void)
{
	Load_Level_From_File("bosslvl2.lvl");
	Player_Init(-1, 300, 0);
	Sanic_Init(300, 300, 60, 60, 5, 3);
}

void Boss2_update(void)
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

	Sanic_Update();
	Sanic_Draw();

	UI_Health();
	UI_Dash_Cooldown();

	UI_Health();
	UI_Dash_Cooldown();
	Draw_AllPlatform();

	Quit_ESC();
}

void Boss2_exit(void)
{
	Clear_Map();
}