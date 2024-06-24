#include "mainMenu.h"
#include "collision.h"
#include "game.h"
#include "quitESC.h"
#include "player.h"

#define BLACK CP_Color_Create(0, 0, 0, 255)
#define WHITE CP_Color_Create(255, 255, 255, 255)
#define RED CP_Color_Create(200, 0, 0, 255)

extern int window_width;
extern int window_height;

void MainMenu_Start(void)
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
	{
		Player_Init(10, 300, 0);
		Player_Ability_Init(1, 1);
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	}
}

void MainMenu_Quit(void)
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
		CP_Engine_Terminate();
}

void MainMenu_init(void)
{
}

void MainMenu_update(void)
{
	CP_Graphics_ClearBackground(BLACK);

	CP_Settings_TextSize(200);
	CP_Settings_Fill(WHITE);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
	CP_Font_DrawText("APETI", (window_width / 2.f), 50);

	CP_Settings_TextSize(110);

	if (CollisionIntersection_RectMouse(window_width / 2.f - 150.0f, window_height / 2.f - 110.f, 300.f, 110.f))
	{
		CP_Settings_Fill(RED);
		MainMenu_Start();
	}
	else
	{
		CP_Settings_Fill(WHITE);
	}

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_BOTTOM);
	CP_Font_DrawText("START", (window_width / 2.f), window_height / 2.f);

	if (CollisionIntersection_RectMouse(window_width / 2.f - 150.0f, window_height / 2.f, 300.f, 110.f))
	{
		CP_Settings_Fill(RED);
		MainMenu_Quit();
	}
	else
	{
		CP_Settings_Fill(WHITE);
	}

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
	CP_Font_DrawText("QUIT", (window_width / 2.f), window_height / 2.f);

	Quit_ESC();
}

void MainMenu_exit(void)
{
	
}
