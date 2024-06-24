#include "quitESC.h"
#include "player.h"
void Quit_ESC(void)
{
	;
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
		Player_exit();
	}
}