#pragma once

#include "cprocessing.h"

int Fade_Logo(CP_Image image, int w, int h, int a, int b, float time);

void logo_init(void);
void logo_update(void);
void logo_exit(void);