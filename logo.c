#include "logo.h"
#include "mainMenu.h"
#include "quitESC.h"

CP_Image Dgp_Logo, Team_Logo;
int state = 0;

extern const int window_width;
extern const int window_height;

int Fade_Logo(CP_Image image, int w, int h, int a, int b, float time) 
{
	static float t = 0;
	t += CP_System_GetDt() / time;

	float x = (float)window_width / 2;
	float y = (float)window_height / 2;
	int alpha = CP_Math_LerpInt(a, b, t);

	CP_Image_Draw(image, x, y, (float)w, (float)h, alpha);

	if (t > 0.99f) {
		t = 0;
		return 1;
	}
	
	return 0;
}

void logo_init(void)
{
	Dgp_Logo = CP_Image_Load("Assets/DigiPen_RED.png");
	Team_Logo = CP_Image_Load("Assets/APETI.png");
}

void logo_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	switch (state)
	{
	case 0:
		if (Fade_Logo(Dgp_Logo, CP_Image_GetWidth(Dgp_Logo), CP_Image_GetHeight(Dgp_Logo), 0, 255, 3.f))
			state = 1;
		break;
	case 1:
		if (Fade_Logo(Dgp_Logo, CP_Image_GetWidth(Dgp_Logo), CP_Image_GetHeight(Dgp_Logo), 255, 0, 1.5f))
			state = 2;
		break;
	case 2:
		if (Fade_Logo(Team_Logo, CP_Image_GetWidth(Team_Logo), CP_Image_GetHeight(Team_Logo), 0, 255, 3.f))
			state = 3;
		break;
	case 3:
		if (Fade_Logo(Team_Logo, CP_Image_GetWidth(Team_Logo), CP_Image_GetHeight(Team_Logo), 255, 0, 1.5f))
			state = 4;
		break;
	case 4:
		CP_Engine_SetNextGameState(MainMenu_init, MainMenu_update, MainMenu_exit);
		break;
	}
	
	Quit_ESC();
}

void logo_exit(void)
{
	CP_Image_Free(&Dgp_Logo);
	CP_Image_Free(&Team_Logo);
}