#include <stdio.h>
#include <stdlib.h>

#include "RSScreenCommands.h"
#include "RSCommand.h"
#include "RSScreen.h"

char *argFromInt(int i) {
  int nDigits = 1;
  int n = i;
  while (n) {
    n /= 10;
    ++nDigits;
  }

  char *buffer = malloc(nDigits+1);
  if (!buffer) {
    return NULL;
  }

  itoa(i, buffer, 10);
  return buffer;
}

char *argFromColor(Color c) {
  char *buffer = malloc(100);
  if (!buffer) {
    return NULL;
  }
  sprintf_s(buffer, 100, "%i-%i-%i-%i", c.r, c.g, c.b, c.a);
  return buffer;
}

void RSScreenDrawRectangle(RSScreen *screen, int x, int y, int width, int height, Color clr) {
  if (screen->commandQueueLen == RSSCREEN_QUEUE_MAX_LEN) {
    printf("Too many commands attempted in a single frame\n");
    return;
  }

  RSCommand cmd;
  cmd.func = FC_DRAW_RECTANGLE;
  cmd.argc = 5;
  cmd.argv = malloc(5*sizeof(char*));
  if (!cmd.argv) {
    printf("Couldn't allocate argv buffer for cmd\n");
    return;
  }

  cmd.argv[0] = argFromInt(x);
  cmd.argv[1] = argFromInt(y);
  cmd.argv[2] = argFromInt(width);
  cmd.argv[3] = argFromInt(height);
  cmd.argv[4] = argFromColor(clr);

  screen->commandQueue[screen->commandQueueLen++] = cmd;
}
