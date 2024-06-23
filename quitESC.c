#include "quitESC.h"

void Quit_ESC(void)
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
		CP_Engine_Terminate();
}
