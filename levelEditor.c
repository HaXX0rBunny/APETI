#include "levelEditor.h"
#include "player.h"

extern const int window_width;
extern const int window_height;
extern struct Platform platformList[MAX_PLATFORM_LIST_SIZE];

extern struct Camera camera;

enum
{
	PLATFORM_W = 50,
	PLATFORM_H = 50
};

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
	int removable = 0;
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

	int mouseX = (int)floor(CP_Input_GetMouseWorldX());
	int mouseY = (int)floor(CP_Input_GetMouseWorldY());

	int gridCoordX = (mouseX / PLATFORM_W) - (mouseX < 0 ? 1 : 0);
	int gridCoordY = (mouseY / PLATFORM_H) - (mouseY < 0 ? 1 : 0);

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
			removable = 1;
			break;
		default:
			return;
			break;
		}

		struct Platform* platform = Get_First_Hidden_Platform();

		if (platform == NULL)
			return;

		Initialize_Platform(platform, (float)(gridCoordX * PLATFORM_W), (float)(gridCoordY * PLATFORM_H),
			(float)PLATFORM_W, (float)PLATFORM_H, color, removable, 1);
	}
}

void Edit_Grid(void)
{
	Edit_Delete_Platform();
	Edit_Add_Platform();
}

void Edit_Update_Text(void)
{
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));

	CP_Settings_TextSize(50);
	CP_Font_DrawText("Edit Mode", 0, 0);

	CP_Settings_TextSize(20);
	char buffer[50] = { '\0' };

	sprintf_s(buffer, 50, "X: %f", CP_Input_GetMouseWorldX());
	CP_Font_DrawText(buffer, 0, 50);

	sprintf_s(buffer, 50, "Y: %f", CP_Input_GetMouseWorldY());
	CP_Font_DrawText(buffer, 0, 70);
}

void Edit_Change_Mode(void)
{
	if (CP_Input_KeyTriggered(KEY_INSERT))
	{
		CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
	}
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
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
}

void level_editor_state_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

	Edit_Update_Text();
	Update_Camera();

	Draw_AllPlatform();
	Edit_Grid();

	Edit_Change_Mode();
}

void level_editor_state_exit(void)
{
	Save_Level_To_File("myLevel.lvl");
	Clear_Map();
}