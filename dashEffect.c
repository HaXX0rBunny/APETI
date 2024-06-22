#include "dashEffect.h"

void Dash_Effect(CP_Color color, CP_Vector* pos, CP_Vector* velocity, float w, float h, int cnt, float dis)
{
	int i = 1;
	for (i = cnt; i >= 1; i--)
	{
		color.a = (unsigned char)(200 / i);
		CP_Settings_Fill(color);
		CP_Graphics_DrawRect(pos->x + (-velocity->x * dis * i), pos->y + (-velocity->y * dis * i),
							 w * (1 - (0.05f * i)), h * (1 - (0.05f * i)));
	}
}
