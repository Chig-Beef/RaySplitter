#include <raylib.h>
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

int argToInt(char *arg) {
  return atoi(arg);
}

Color argToColor(char *arg) {
  Color c;

  char temp[10];
  
  int i = 0;
  char *p = arg;
  int n = 0;

  while (*p) {
    if (*p == '-') {
      // End
      temp[i] = 0;

      ((unsigned char*)&c)[n++] = atoi(temp);

      i = 0;
    } else {
      temp[i++] = *p;
    }
    
    ++p;
  }

  return c;
}

void drawRectangleWrapper(int argc, char **argv) {
  if (argc != 5) {
    printf("Bad num of args!\n");
    return;
  }

  int x = argToInt(argv[0]);
  int y = argToInt(argv[1]);
  int w = argToInt(argv[2]);
  int h = argToInt(argv[3]);
  Color clr = argToColor(argv[4]);

  DrawRectangle(x, y, w, h, clr);
}

void executeCmd(char *cmd) {
  // How many args?
  int argc = 1;
  for (char *p = cmd; *p; ++p) if (*p == ' ') ++argc;

  // Allocate buffer for args
  char **argv = malloc(argc*sizeof(char*));

  // Load in each arg
  int i = 0;
  int j = 0;
  char *p = cmd;
  for (p = cmd; *p; ++p) {
    // End of arg
    if (*p != ' ') {
      continue;
    }

    int size = p-(cmd+j);

    argv[i] = malloc(size+1);
    int n = 0;
    for (char* k = cmd+j; k < p; ++k) {
      argv[i][n++] = *k;
    }
    argv[i][size] = 0;

    ++i;
    j = p-cmd+1;
  }

  // Last arg
  int size = p-(cmd+j);

  argv[i] = malloc(size+1);
  int n = 0;
  for (char* k = cmd+j; k < p; ++k) {
    argv[i][n++] = *k;
  }
  argv[i][size] = 0;

  // Show each arg
  printf("ARGC: %i\n", argc);
  // for (int i = 0; i < argc; ++i) {
  //   printf("ARG: %s\n", argv[i]);
  // }

  // Determine what to do
  if (argv[0][0] == '0') {
    drawRectangleWrapper(argc-1, argv+1);
  }

  // Free args
  for (int i = 0; i < argc; ++i) {
    free(argv[i]);
  }
  free(argv);
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

      // Replace newline with end
      for (int i = 0; i < 256; ++i) if (line[i] == '\r' || line[i] == '\n') line[i] = 0;
      
      // Execute
      executeCmd(line);
    }

    DrawRectangle(10, 10, 50, 50, BLUE);

    EndDrawing();
  }

  CloseWindow();

  printf("Closing sub screen\n");
  return 0;
}
