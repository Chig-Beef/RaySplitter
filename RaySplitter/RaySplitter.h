#ifndef _RS_RAY_SPLITTER_H_
#define _RS_RAY_SPLITTER_H_

#include "RSScreen.h"
#include "winray.h"
#include "RSScreenCommands.h"

// Call at the end of a frame to push commands to sub screens
// Also waits the given amount of time (FPS)
errno_t RSFrame();

errno_t RSRegisterScreen(RSScreen *screen);

#endif
