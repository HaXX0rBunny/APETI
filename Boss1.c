#include "Boss1.h"
#include "levelEditor.h"
#include "player.h"
#include "ui.h"
#include "enemyAi.h"
#include "demon.h"
#include "quitESC.h"

void Boss1_init(void)
{
	Load_Level_From_File("bosslvl1.lvl");
	Player_Init(-1, 300, 0);
	Demon_Init(-500, -150, 420, -150, 60, 60, 5, 3);
}

void Boss1_update(void)
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

	Demon_Update();
	Demon_Draw();

	Draw_AllPlatform();
	UI_Health();
	UI_Dash_Cooldown();

	Quit_ESC();
}

void Boss1_exit(void)
{
	Player_Init(-1, 500, 1000);
	Player_Ability_Init(1, 0);
	Clear_Map();
}
