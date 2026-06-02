#ifndef _RS_SCREEN_H_
#define _RS_SCREEN_H_

#include "winray.h"
#include "RScommand.h"

#define RSSCREEN_QUEUE_MAX_LEN 100

// Holds all the info for a given screen
typedef struct {
  // Basic information (this is expected to be done outside)
  int width;
  int height;
  char *title;

  // The queue to hold command info
  RSCommand commandQueue[RSSCREEN_QUEUE_MAX_LEN];
  int commandQueueLen;

  HANDLE childWriteable; // The handle to send commands to
  STARTUPINFO start; // Info on how this scren started
  PROCESS_INFORMATION process; // The process this is running on
} RSScreen;

errno_t RSScreenInit(RSScreen *screen);

errno_t RSScreenOpen(RSScreen *screen);

errno_t RSScreenCloseWait(RSScreen *screen);

errno_t RSScreenCloseForce(RSScreen *screen);

errno_t RSScreenFrame(RSScreen *screen);

bool RSScreenQueueFull(RSScreen *screen);

void RSScreenQueuePush(RSScreen *screen, RSCommand cmd);

#endif
