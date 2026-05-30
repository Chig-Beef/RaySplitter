#include <stdio.h>

#include "Commands.h"
#include "../RaySplitter/RaySplitter.h"

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

  // End
  temp[i] = 0;
  ((unsigned char*)&c)[n++] = atoi(temp);

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

void drawCircleWrapper(int argc, char **argv) {
  if (argc != 4) {
    printf("Bad num of args!\n");
    return;
  }

  int x = argToInt(argv[0]);
  int y = argToInt(argv[1]);
  int r = argToInt(argv[2]);
  Color clr = argToColor(argv[3]);

  DrawCircle(x, y, r, clr);
}

FuncWrapper funcs[RS_NUM_FUNCS] = {
  drawRectangleWrapper,
  drawCircleWrapper,
};

FuncWrapper getFuncFromCode(int code) {
  if (code < 0 || code >= RS_NUM_FUNCS) return NULL;
  return funcs[code];
}
