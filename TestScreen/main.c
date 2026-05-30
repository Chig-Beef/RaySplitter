#include <stdio.h>
#include <stdlib.h>
#include "../RaySplitter/winray.h"

bool checkCmdAvailable() {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD bytesAvail = 0;

  // How many bytes have been written?
  if (!PeekNamedPipe(hStdin, NULL, 0, NULL, &bytesAvail, NULL)) {
    return false;
  }

  // No data given
  if (bytesAvail == 0) {
    return false;
  }

  // Buffer to load in new bytes
  char* buffer = (char*)malloc(bytesAvail);
  if (buffer == NULL) return false;

  DWORD bytesRead = 0;
  // Don't remove data, but still load in
  if (PeekNamedPipe(hStdin, buffer, bytesAvail, &bytesRead, NULL, NULL)) {
    // Scan for newline
    for (DWORD i = 0; i < bytesRead; i++) {
      if (buffer[i] == '\n' || buffer[i] == '\r') {
        // Completed line
        free(buffer);
        return true;
      }
    }
  }

  // Haven't reached newline yet
  free(buffer);
  return false;
}

int main(int argc, char **argv) {
  printf("Starting sub screen\n");

  // Load in args to see how to create window
  if (argc != 4) {
    printf("Incorrect number of args given to sub screen\n");
    return 1;
  }

  char *title = argv[1];
  char *sWidth = argv[2];
  char *sHeight = argv[3];

  int width = atoi(sWidth);
  int height = atoi(sHeight);

  SetTraceLogLevel(LOG_WARNING);

  InitWindow(width, height, title);

  while (!WindowShouldClose()) {
    BeginDrawing();

    if (checkCmdAvailable()) {
      // Read the line in
      char line[256];
      fgets(line, sizeof(line), stdin);
      
      // Test, show it
      printf("You typed: %s", line);
    }

    DrawRectangle(10, 10, 50, 50, BLUE);

    EndDrawing();
  }

  CloseWindow();

  printf("Closing sub screen\n");
  return 0;
}
