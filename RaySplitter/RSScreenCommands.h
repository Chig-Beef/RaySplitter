#ifndef _RS_SCREEN_COMMANDS_H_
#define _RS_SCREEN_COMMANDS_H_

#include "winray.h"
#include "RSScreen.h"

void RSScreenDrawRectangle(RSScreen *screen, int x, int y, int width, int height, Color clr);

void RSScreenDrawCircle(RSScreen *screen, int x, int y, int radius, Color clr);

#endif
