#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

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
    DrawRectangle(10, 10, 50, 50, BLUE);
    EndDrawing();
  }

  CloseWindow();

  printf("Closing sub screen\n");
  return 0;
}
