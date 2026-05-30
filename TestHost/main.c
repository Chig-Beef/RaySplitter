#include <corecrt.h>
#include <stdio.h>
#include <string.h>
#include "winray.h"

// Structures to hold configuration and output information
STARTUPINFO si;
PROCESS_INFORMATION pi;

errno_t openSubScreen() {
  // Init proc info
  memset(&si, 0, sizeof(si));
  si.cb = sizeof(si);
  memset(&pi, 0, sizeof(pi));

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
    &si,
    &pi
  );

  if (!success) {
    printf("CreateProcess failed. Error code: %lu\n", GetLastError());
    return 1;
  }

  // Process successfully created
  printf("Successfully started process with PID: %lu\n", pi.dwProcessId);

  return 0;
}

errno_t closeSubScreen() {
  // Optional: Wait until the child process exits
  WaitForSingleObject(pi.hProcess, INFINITE);
  printf("Child process has exited.\n");

  // CRITICAL: Always close handles to avoid kernel memory leaks
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  return 0;
}

int main() {
  printf("Starting test\n");

  if (openSubScreen()) {
    return 1;
  }

  SetTraceLogLevel(LOG_WARNING);

  InitWindow(320, 240, "Test window main");

  while (!WindowShouldClose()) {
    BeginDrawing();
    DrawRectangle(10, 10, 50, 50, RED);
    EndDrawing();
  }

  CloseWindow();

  closeSubScreen();

  printf("Ending test\n");

  return 0;
}
