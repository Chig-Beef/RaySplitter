#include <corecrt.h>
#include <raylib.h>
#include <string.h>
#include <stdio.h>

#include "RSScreen.h"

char defaultScreenTitle[] = "RaySplitter sub-screen";
const int defaultScreenWidth = 320;
const int defaultScreenHeight = 240;

errno_t RSScreenInit(RSScreen *screen) {
  // Init proc info
  memset(&screen->start, 0, sizeof(screen->start));
  screen->start.cb = sizeof(screen->start);

  memset(&screen->process, 0, sizeof(screen->process));

  // Default props
  screen->title = defaultScreenTitle;
  screen->width = defaultScreenWidth;
  screen->height = defaultScreenHeight;

  return 0;
}

#define MAX_CMD_SIZE 100

errno_t RSScreenOpen(RSScreen *screen) {
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
    FALSE,
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
  return RSScreenCloseForce(screen);
}

errno_t RSScreenCloseForce(RSScreen *screen) {
  CloseHandle(screen->process.hProcess);
  CloseHandle(screen->process.hThread);
  return 0;
}
