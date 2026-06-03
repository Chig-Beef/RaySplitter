#include <corecrt.h>
#include <raylib.h>
#include <string.h>
#include <stdio.h>

#include "RSScreen.h"
#include "RSCommand.h"

char defaultScreenTitle[] = "RaySplitter sub-screen";
const int defaultScreenWidth = 320;
const int defaultScreenHeight = 240;

errno_t RSScreenInit(RSScreen *screen) {
  // Init proc info
  memset(&screen->start, 0, sizeof(screen->start));
  screen->start.cb = sizeof(screen->start);
  screen->start.dwFlags = STARTF_USESTDHANDLES;

  memset(&screen->process, 0, sizeof(screen->process));

  // Default props
  screen->title = defaultScreenTitle;
  screen->width = defaultScreenWidth;
  screen->height = defaultScreenHeight;

  // Empty queue
  screen->commandQueueLen = 0;

  // No images
  screen->numImages = 0;
  memset(screen->takenImages, 0, RSSCREEN_MAX_IMAGES*sizeof(bool));

  // No textures
  screen->numTextures = 0;
  memset(screen->takenTextures, 0, RSSCREEN_MAX_TEXTURES*sizeof(bool));

  return 0;
}

#define MAX_CMD_SIZE 100

errno_t RSScreenOpen(RSScreen *screen) {
  SECURITY_ATTRIBUTES sa = {
    .nLength = sizeof(SECURITY_ATTRIBUTES),
    .lpSecurityDescriptor = NULL,
    .bInheritHandle = TRUE
  };

  HANDLE childStdinRead = NULL;
  screen->childWriteable = NULL;

  // Create pipe for child's stdin
  if (!CreatePipe(&childStdinRead, &screen->childWriteable, &sa, 0))
  {
    printf("CreatePipe failed\n");
    return 1;
  }

  // Parent should not accidentally pass write end to child
  SetHandleInformation(screen->childWriteable, HANDLE_FLAG_INHERIT, 0);

  // Child's stdin comes from our pipe
  screen->start.hStdInput = childStdinRead;

  // Child's stdout/stderr can go wherever you want
  screen->start.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  screen->start.hStdError  = GetStdHandle(STD_ERROR_HANDLE);

  // Path to sub screen exe
  char command[] = "./TestScreen/dev.exe";

  char finalCommand[MAX_CMD_SIZE];

  if (!sprintf_s(finalCommand, MAX_CMD_SIZE, "%s \"%s\" %i %i", command, screen->title, screen->width, screen->height)) {
    printf("Couldn't format final command\n");
    return 1;
  }

  // Run the exe
  BOOL success = CreateProcess(
    NULL,
    finalCommand,
    NULL,
    NULL,
    TRUE,
    0,
    NULL,
    NULL,
    &screen->start,
    &screen->process
  );

  if (!success) {
    printf("CreateProcess failed. Error code: %lu\n", GetLastError());
    return 1;
  }

  // Process successfully created
  printf("Successfully started process with PID: %lu\n", screen->process.dwProcessId);

  return 0;
}

errno_t RSScreenCloseWait(RSScreen *screen) {
  WaitForSingleObject(screen->process.hProcess, INFINITE);
  CloseHandle(screen->process.hProcess);
  CloseHandle(screen->process.hThread);
  return 0;
}

errno_t RSScreenCloseForce(RSScreen *screen) {
  // Terminate the process unconditionally
  if (!TerminateProcess(screen->process.hProcess, 1)) {
    printf("Error: TerminateProcess failed. Error code: %lu\n", GetLastError());
    CloseHandle(screen->process.hProcess);
    return 1;
  }

  CloseHandle(screen->process.hProcess);
  CloseHandle(screen->process.hThread);
  return 0;
}

void RSScreenSendCommand(RSScreen *screen, RSCommand cmd) {
  char *msg = RSCommandPackage(&cmd);

  DWORD written;
  WriteFile(
      screen->childWriteable,
      msg,
      (DWORD)strlen(msg),
      &written,
      NULL);

  free(msg);
}

// Flushes commands to screen
errno_t RSScreenFrame(RSScreen *screen) {
  // Iterate over each command to send
  for (int i = 0; i < screen->commandQueueLen; ++i) {
    RSScreenSendCommand(screen, screen->commandQueue[i]);

    // Free the command
    RSCommandFree(&screen->commandQueue[i]);
  }

  // Clear the queue
  screen->commandQueueLen = 0;

  return 0;
}

bool RSScreenQueueFull(RSScreen *screen) {
  return screen->commandQueueLen == RSSCREEN_QUEUE_MAX_LEN;
}

void RSScreenQueuePush(RSScreen *screen, RSCommand cmd) {
  if (RSScreenQueueFull(screen)) {
    printf("Command queue full!\n");

    // Still have to free the command
    RSCommandFree(&cmd);
    return;
  }

  screen->commandQueue[screen->commandQueueLen++] = cmd;
}

RSImage RSScreenNewImage(RSScreen *screen, int width, int height) {
  if (screen->numImages == RSSCREEN_MAX_IMAGES) return (RSImage){-1, -1, -1};

  RSImage img;
  img.width = width;
  img.height = height;

  for (int i = 0; i < RSSCREEN_MAX_IMAGES; ++i) {
    if (screen->takenImages[i]) continue;

    img.ref = i;
    screen->takenImages[i] = true;
    screen->numImages++;
    screen->images[i] = img;
    return img;
  }

  // Couldn't find a spot
  return (RSImage){-1, -1, -1};
}

RSTexture RSScreenNewTexture(RSScreen *screen, int width, int height) {
  if (screen->numTextures == RSSCREEN_MAX_TEXTURES) return (RSTexture){-1, -1, -1};

  RSTexture img;
  img.width = width;
  img.height = height;

  for (int i = 0; i < RSSCREEN_MAX_TEXTURES; ++i) {
    if (screen->takenTextures[i]) continue;

    img.ref = i;
    screen->takenTextures[i] = true;
    screen->numTextures++;
    screen->textures[i] = img;
    return img;
  }

  // Couldn't find a spot
  return (RSTexture){-1, -1, -1};
}
