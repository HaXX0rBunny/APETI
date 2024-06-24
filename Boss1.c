#include "Boss1.h"
#include "levelEditor.h"
#include "player.h"
#include "ui.h"
#include "enemyAi.h"
#include "demon.h"
#include "quitESC.h"
struct Music {
	int isPlaying;
};

CP_Sound Bgm;
CP_Sound YdAtk;
CP_Sound Bossdie;
CP_Sound BossHit;

struct Music BGM;


void Boss1_init(void)
{
	Load_Level_From_File("bosslvl1.lvl");
	Player_Init(-1, 300, 0);

	Bgm = CP_Sound_Load("./sound/ydbgm.mp3");
	YdAtk = CP_Sound_Load("./sound/ydatk.wav");
	BossHit = CP_Sound_Load("./sound/boss.wav");
	Bossdie = CP_Sound_Load("./sound/enemyhit.wav");
	BGM.isPlaying = 0;

	Demon_Init(-500, -150, 420, -150, 60, 60, 5, 3);
}

void Boss1_update(void)
{
	if (BGM.isPlaying == 0) {
		CP_Sound_PlayAdvanced(Bgm, 0.5f, 1.0f, FALSE, CP_SOUND_GROUP_MUSIC);
		BGM.isPlaying=1;
	}

	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

	updateEnemies();
	Player_Update();
	Player_Draw();
	Bullet_Update();
	Bullet_Draw();
	Bomb_Update();
	Bomb_Draw();
	Demon_Update();
	Demon_Draw();
	Draw_AllPlatform();
	UI_Health();
	UI_Dash_Cooldown();

	Quit_ESC();
}

void Boss1_exit(void)
{
	CP_Sound_Free(&Bgm);
	CP_Sound_Free(&YdAtk); 
	CP_Sound_Free(&Bossdie);
	CP_Sound_Free(&BossHit);
	Player_Init(-1, 500, 1000);
	Player_Ability_Init(1, 0);
	Clear_Map();
}
