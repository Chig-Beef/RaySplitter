#include "RSScreenCommands.h"

void RSScreenSetWindowTitle(RSScreen *screen, cstring title) {
  const FuncCode func = FC_SET_WINDOW_TITLE;
  void *argv[1] = {&title};
  RSDeployCommand(screen, func, argv);
}

void RSScreenSetWindowPosition(RSScreen *screen, int x, int y) {
  const FuncCode func = FC_SET_WINDOW_POSITION;
  void *argv[2] = {&x, &y};
  RSDeployCommand(screen, func, argv);
}

void RSScreenSetWindowSize(RSScreen *screen, int width, int height) {
  const FuncCode func = FC_SET_WINDOW_SIZE;
  void *argv[2] = {&width, &height};
  RSDeployCommand(screen, func, argv);
}


void RSScreenClearBackground(RSScreen *screen, Color color) {
  const FuncCode func = FC_CLEAR_BACKGROUND;
  void *argv[1] = {&color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenTakeScreenShot(RSScreen *screen, cstring fileName) {
  const FuncCode func = FC_TAKE_SCREENSHOT;
  void *argv[1] = {&fileName};
  RSDeployCommand(screen, func, argv);
}

