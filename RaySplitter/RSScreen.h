#ifndef _RS_SCREEN_H_
#define _RS_SCREEN_H_

#include "winray.h"

// Holds all the info for a given screen,
// regardless of whether it is the main or sub
typedef struct {
  bool isMain; // Is this the main screen? (in which case, no extra logic)
  STARTUPINFO start; // Info on how this scren started (if sub)
  PROCESS_INFORMATION process; // The process this is running on (if sub)
} RSScreen;

errno_t RSScreenInit(RSScreen *screen);

errno_t RSScreenOpen(RSScreen *screen);

errno_t RSScreenCloseWait(RSScreen *screen);

errno_t RSScreenCloseForce(RSScreen *screen);

#endif
