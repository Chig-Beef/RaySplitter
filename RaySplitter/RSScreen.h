#ifndef _RS_SCREEN_H_
#define _RS_SCREEN_H_

#include "winray.h"
#include "RScommand.h"
#include "RSImage.h"
#include "RSTexture.h"

#define RSSCREEN_QUEUE_MAX_LEN 100
#define RSSCREEN_MAX_IMAGES 100
#define RSSCREEN_MAX_TEXTURES 100

// Holds all the info for a given screen
typedef struct {
  // Basic information (this is expected to be done outside)
  int width;
  int height;
  char *title;

  // The registered images for this screen
  RSImage images[RSSCREEN_MAX_IMAGES];
  bool takenImages[RSSCREEN_MAX_IMAGES];
  int numImages;

  // The registered images for this screen
  RSTexture textures[RSSCREEN_MAX_TEXTURES];
  bool takenTextures[RSSCREEN_MAX_TEXTURES];
  int numTextures;

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

RSImage RSScreenNewImage(RSScreen *screen, int width, int height);

RSTexture RSScreenNewTexture(RSScreen *screen, int width, int height);

#endif
