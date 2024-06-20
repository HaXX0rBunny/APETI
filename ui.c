#include "ui.h"
#include "player.h"

extern struct Player player;
extern const int window_width;
extern const int window_height;

enum
{
	HEALTH_PADDING_X = 30,
	HEALTH_PADDING_Y = 30,
};

void UI_Health()
{
	float window_left = player.Pos.x - (window_width / 2);
	float window_top = player.Pos.y - (window_height / 2);

	int i = 0;

	for (i = 0; i < player.maxHealth / 2; i++)
	{
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Graphics_DrawRect(window_left + HEALTH_PADDING_X + (30 * i), window_top + HEALTH_PADDING_Y, 20.f, 20.f);

		int current_health = player.health - (i * 2);

		if (current_health > 0)
		{
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawRect(window_left + HEALTH_PADDING_X + (30 * i), window_top + HEALTH_PADDING_Y, current_health == 1 ? 10.f : 20.f, 20.f);
		}
	}
}

void UI_Dash_Cooldown()
{
	float cooldown_gauge = player.w * (player.dashCooldown / player.maxDashCooldown);

	if (player.dashCooldown) 
	{
		CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
		CP_Graphics_DrawRect(player.Pos.x, player.Pos.y - 15, cooldown_gauge, 5);
	}
}
