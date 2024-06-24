#include "Boss2.h"
#include "levelEditor.h"
#include "player.h"
#include "ui.h"
#include "enemyAi.h"
#include "sanic.h"
#include "quitESC.h"
struct Music {
	int isPlaying;
};

CP_Sound Bgm;
CP_Sound spin;
CP_Sound Boss2die;
CP_Sound Boss2Hit;

struct Music BGM;
void Boss2_init(void)
{

	Load_Level_From_File("bosslvl2.lvl");
	Player_Init(-1, 300, -300);
	Sanic_Init(300,-300, 60, 60, 10, 3);
	Bgm = CP_Sound_Load("./sound/bs2bgm.mp3");
	spin = CP_Sound_Load("./sound/spin.mp3");
	Boss2Hit = CP_Sound_Load("./sound/boss.wav");
	Boss2die = CP_Sound_Load("./sound/enemyhit.wav");
}

void Boss2_update(void)
{
	if (BGM.isPlaying == 0) {
		CP_Sound_PlayAdvanced(Bgm, 0.8f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
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

	Sanic_Update();
	Sanic_Draw();

	Draw_AllPlatform();
	UI_Health();
	UI_Dash_Cooldown();

	Quit_ESC();
}

void Boss2_exit(void)
{
	CP_Sound_Free(&Bgm);
	CP_Sound_Free(&spin);
	CP_Sound_Free(&Boss2die);
	CP_Sound_Free(&Boss2Hit);
	Player_Init(-1, 4500, -270);
	Player_Ability_Init(1, 1);
	Clear_Map();
}