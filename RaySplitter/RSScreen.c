#include <corecrt.h>
#include <string.h>
#include <stdio.h>

#include "RSScreen.h"

RSScreen *RSMainScreen = NULL;

errno_t RSScreenInit(RSScreen *screen) {
  if (!RSMainScreen) {
    // Start as main screen
    screen->isMain = true;

    return 0;
  }

  // Start as sub
  return RSScreenOpen(screen);
}

errno_t RSScreenOpen(RSScreen *screen) {
  screen->isMain = false;

  // Init proc info
  memset(&screen->start, 0, sizeof(screen->start));
  screen->start.cb = sizeof(screen->start);

  memset(&screen->process, 0, sizeof(screen->process));

  // Path to sub screen exe
  char commandLine[] = "./TestScreen/dev.exe";

  // Run the exe
  BOOL success = CreateProcess(
    NULL,
    commandLine,
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
