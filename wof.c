#include "wof.h"
#include "player.h"

#define EYE_PADDING 30

#define YELLOW CP_Color_Create(240, 240, 0, 255)
#define GRAY CP_Color_Create(110, 110, 110, 255)
#define MAX_TIMER 1.f

struct Wof wof;
extern struct Player player;

int eyeList[3];

void WofEye_Init(struct WofEye* wofEye, float x, float y, float w, float h, int damage)
{
	wofEye->pos.x = x;
	wofEye->pos.y = y;

	wofEye->w = w;
	wofEye->h = h;

	wofEye->damage = damage;

	wofEye->isOpen = 0;

	wofEye->eyeCover_color = GRAY;
	wofEye->color = YELLOW;
}

void WofEye_Attack(struct WofEye* wofEye)
{

}

int WofEye_Hit(struct WofEye* wofEye)
{
	return 0;
}

int WofEye_Open(struct WofEye* wofEye)
{
	static float rot_counter = 0;
	rot_counter += CP_System_GetDt();

	static float eyeH = 0;

	eyeH = CP_Math_LerpFloat(wofEye->h / 2.f, 0, rot_counter);

	CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y, wofEye->w, eyeH);
	CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y + wofEye->h - eyeH, wofEye->w, eyeH);

	if (eyeH < 0.01f)
	{
		rot_counter = 0;
		eyeH = wofEye->h / 2.f;
		return 1;
	}

	return 0;
}

int WofEye_Close(struct WofEye* wofEye)
{
	static float rot_counter = 0;
	rot_counter += CP_System_GetDt();

	static float eyeH = 0;

	eyeH = CP_Math_LerpFloat(0, wofEye->h / 2.f, rot_counter);

	CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y, wofEye->w, eyeH);
	CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y + wofEye->h - eyeH, wofEye->w, eyeH);

	if (eyeH > (wofEye->h / 2.f - 0.2f))
	{
		rot_counter = 0;
		eyeH = 0;
		return 1;
	}

	return 0;
}

void WofEye_Draw(struct WofEye* wofEye)
{
	CP_Settings_Fill(wofEye->color);
	CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y, wofEye->w, wofEye->h);

	if (!wofEye->isOpen)
	{
		CP_Settings_Fill(wofEye->eyeCover_color);
		CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y, wofEye->w, wofEye->h / 2.f);
		CP_Graphics_DrawRect(wofEye->pos.x, wofEye->pos.y + (wofEye->h / 2.f), wofEye->w, wofEye->h / 2.f);
	}
}

void Wof_Init(float x, float y, float w, float h, int health, int damage)
{
	wof.pos.x = x;
	wof.pos.y = y;

	wof.w = w;
	wof.h = h;

	wof.health = health;

	int i = 0;
	for (i = 0; i < 3; i++)
	{
		WofEye_Init(&wof.eye[i], x - EYE_PADDING, y + (h / 7.f * (2 * (i + 1) - 1)), EYE_PADDING, (h / 7.f), damage);
	}

	wof.state = 0;
	wof.color = GRAY;
}

void Wof_Hit()
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (wof.eye[i].isOpen)
		{
			if (WofEye_Hit(&wof.eye[i]))
			{
				wof.health--;
				Wof_Create_Wall();
			}
		}
	}
}

void Wof_Create_Wall()
{

}

int Wof_Timer()
{
	static float timer = 0;
	float t = CP_System_GetDt();

	timer += t;
	if (timer > MAX_TIMER)
	{
		timer = 0;
		return 1;
	}

	return 0;
}

void Wof_Draw()
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		WofEye_Draw(&wof.eye[i]);
	}

	CP_Settings_Fill(wof.color);
	CP_Graphics_DrawRect(wof.pos.x, wof.pos.y, wof.w, wof.h);
}

void Wof_Update()
{
	static int r = 0;

	switch (wof.state)
	{
	case 0:
		r = CP_Random_RangeInt(0, 2);
		wof.eye[r].isOpen = 1;
		wof.state = 1;
		break;
	case 1:
		if (WofEye_Open(&wof.eye[r]))
		{
			wof.state = 2;
		}
		break;
	case 2:
		WofEye_Attack(&wof.eye[r]);
		if (Wof_Timer())
		{
			wof.state = 3;
		}
		break;
	case 3:
		if (WofEye_Close(&wof.eye[r]))
		{
			wof.eye[r].isOpen = 0;
			wof.state = 0;
		}
		break;
	}
}
