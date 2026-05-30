#include <stdio.h>
#include <raylib.h>

int main() {
  printf("Starting test\n");

  SetTraceLogLevel(LOG_WARNING);

  InitWindow(320, 240, "Test window main");

  while (!WindowShouldClose()) {
    BeginDrawing();
    DrawRectangle(10, 10, 50, 50, RED);
    EndDrawing();
  }

  CloseWindow();

  printf("Ending test\n");
  return 0;
}
