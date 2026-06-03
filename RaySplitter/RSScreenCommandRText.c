#include "RSScreenCommands.h"

void RSScreenDrawFPS(RSScreen *screen, int posX, int posY) {
  const FuncCode func = FC_DRAW_FPS;
  void *argv[2] = {&posX, &posY};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawText(RSScreen *screen, cstring text, int posX, int posY, int fontSize, Color color) {
  const FuncCode func = FC_DRAW_TEXT;
  void *argv[5] = {&text, &posX, &posY, &fontSize, &color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenSetTextLineSpacing(RSScreen *screen, int spacing) {
  const FuncCode func = FC_SET_TEXT_LINE_SPACING;
  void *argv[1] = {&spacing};
  RSDeployCommand(screen, func, argv);
}
