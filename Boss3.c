#include "Boss3.h"
#include "levelEditor.h"
#include "player.h"
#include "ui.h"
#include "enemyAi.h"
#include "wof.h"
#include "quitESC.h"
struct Music {
	int isPlaying;
};

CP_Sound Bgm;
CP_Sound shoot;
CP_Sound bwall;
CP_Sound Boss3die;
CP_Sound Boss3Hit;

struct Music BGM;
void Boss3_init(void)
{
	
	Load_Level_From_File("bosslvl3.lvl");
	Player_Init(-1, 300, 0);
	Wof_Init(1500, 0, 200, 1000, 10, 3);
	Bgm = CP_Sound_Load("./sound/wofbgm.mp3");
	shoot = CP_Sound_Load("./sound/wofbullet.wav");
	bwall = CP_Sound_Load("./sound/wall.wav");
	Boss3Hit = CP_Sound_Load("./sound/boss.wav");
	Boss3die = CP_Sound_Load("./sound/enemyhit.wav");
	BGM.isPlaying = 0;
}

void Boss3_update(void)
{
	if (BGM.isPlaying == 0) {
		CP_Sound_PlayAdvanced(Bgm, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_MUSIC);
		BGM.isPlaying = 1;
	}
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
	CP_Sound_Free(&Bgm);
	CP_Sound_Free(&shoot);
	CP_Sound_Free(&bwall);
	CP_Sound_Free(&Boss3die);
	CP_Sound_Free(&Boss3Hit);
	Player_Ability_Init(1, 1);
	Clear_Map();
}