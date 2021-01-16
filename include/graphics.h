#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "types.h"

void DrawBoxAt(int x, int y, int width, int height);
void DrawStringBoxAt(int x, int y, StringList_t* List, int* returnWidth, int* returnHeight);

#endif