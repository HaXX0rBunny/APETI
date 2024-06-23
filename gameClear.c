#include "gameClear.h"
#include "quitESC.h"

#define BLACK CP_Color_Create(0, 0, 0, 255)
#define WHITE CP_Color_Create(255, 255, 255, 255)

extern int window_width;
extern int window_height;

void GameClear_init(void)
{
	CP_Graphics_ClearBackground(BLACK);

	CP_Settings_TextSize(200);
	CP_Settings_Fill(WHITE);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("CONGRATULATIONS.", (window_width / 2.f), (window_height / 2.f));
}

void GameClear_update(void)
{
	Quit_ESC();
}

void GameClear_exit(void)
{

}
