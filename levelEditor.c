#include "levelEditor.h"
#include "player.h"

extern const int window_width;
extern const int window_height;
extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];

void Edit_Delete_Platform(void)
{
	if (CP_Input_MouseDown(MOUSE_BUTTON_RIGHT))
	{
		struct Platform* platform = Platform_Mouse_Collision();
		if (platform != NULL)
		{
			Remove_Platform(platform);
		}
	}
}

void Edit_Add_Platform(void)
{
	static CP_KEY LastKey = KEY_1;

	if (CP_Input_KeyTriggered(KEY_1))
		LastKey = KEY_1;
	if (CP_Input_KeyTriggered(KEY_2))
		LastKey = KEY_2;
	if (CP_Input_KeyTriggered(KEY_3))
		LastKey = KEY_3;
	if (CP_Input_KeyTriggered(KEY_4))
		LastKey = KEY_4;
	if (CP_Input_KeyTriggered(KEY_5))
		LastKey = KEY_5;
	if (CP_Input_KeyTriggered(KEY_6))
		LastKey = KEY_6;
	if (CP_Input_KeyTriggered(KEY_7))
		LastKey = KEY_7;
	if (CP_Input_KeyTriggered(KEY_8))
		LastKey = KEY_8;

	const int numberOfTilesW = 20;
	const int numberOfTilesH = 10;

	int platformW = window_width / numberOfTilesW;
	int platformH = window_height / numberOfTilesH;

	int mouseX = (int)floor(CP_Input_GetMouseWorldX());
	int mouseY = (int)floor(CP_Input_GetMouseWorldY());

	int gridCoordX = mouseX / platformW;
	int gridCoordY = mouseY / platformH;

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
	{
		if (Platform_Mouse_Collision() != NULL)
			return;

		CP_Color color;

		switch (LastKey)
		{
		case KEY_1:
			color = CP_Color_Create(0, 0, 0, 255);
			break;
		case KEY_2:
			color = CP_Color_Create(255, 0, 0, 255);
			break;
		case KEY_3:
			color = CP_Color_Create(0, 255, 0, 255);
			break;
		case KEY_4:
			color = CP_Color_Create(0, 0, 255, 255);
			break;
		case KEY_5:
			color = CP_Color_Create(0, 255, 255, 255);
			break;
		case KEY_6:
			color = CP_Color_Create(255, 0, 255, 255);
			break;
		case KEY_7:
			color = CP_Color_Create(255, 255, 0, 255);
			break;
		case KEY_8:
			color = CP_Color_Create(120, 120, 120, 255);
			break;
		default:
			return;
			break;
		}

		struct Platform* platform = Get_First_Hidden_Platform();

		if (platform == NULL)
			return;

		Initialize_Platform(platform, (float)(gridCoordX * platformW), (float)(gridCoordY * platformH),
			(float)platformW, (float)platformH, color, 0, 1);
	}
}

void Edit_Grid(void)
{
	Edit_Delete_Platform();
	Edit_Add_Platform();
}

struct Platform* Platform_Mouse_Collision()
{
	for (int i = 0; i < MAX_PLATFORM_LIST_SIZE; i++)
	{
		struct Platform* platform = &platformList[i];

		if (!platform->exist) continue;

		if (Platform_MouseIn(platform))
		{
			return platform;
		}
	}

	return NULL;
}

void level_editor_state_init(void)
{
	Load_Level_From_File("myLevel.lvl");
}

void level_editor_state_update(void)
{
	CP_Color color_white = CP_Color_Create(255, 255, 255, 255);
	CP_Graphics_ClearBackground(color_white);

	Draw_AllPlatform();
	Player_Update();
	Player_Draw();

	//edit mode text

	Edit_Grid();
}

void level_editor_state_exit(void)
{
	Save_Level_To_File("myLevel.lvl");
}