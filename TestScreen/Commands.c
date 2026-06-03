#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

float argToFloat(char *arg) {
  return atof(arg);
}

char *argToString(char *arg) {
  const int len = strlen(arg);
  char *out = malloc(len+1);
  memcpy(out, arg, len);
  out[len] = 0;
  return out;
}

Vector2 argToVector2(char *arg) {
  Vector2 v;

  char temp[10];
  
  int i = 0;
  char *p = arg;
  int n = 0;

  while (*p) {
    if (*p == '-') {
      // End
      temp[i] = 0;

      // TODO: Support float vector2s
      ((float*)&v)[n++] = (float)atoi(temp);

      i = 0;
    } else {
      temp[i++] = *p;
    }
    
    ++p;
  }

  // End
  temp[i] = 0;
  ((float*)&v)[n++] = (float)atoi(temp);

  return v;
}

Rectangle argToRectangle(char *arg) {
  Rectangle r;

  char temp[10];
  
  int i = 0;
  char *p = arg;
  int n = 0;

  while (*p) {
    if (*p == '-') {
      // End
      temp[i] = 0;

      // TODO: Support float rects over wire
      ((float*)&r)[n++] = (float)atoi(temp);

      i = 0;
    } else {
      temp[i++] = *p;
    }
    
    ++p;
  }

  // End
  temp[i] = 0;
  ((float*)&r)[n++] = (float)atoi(temp);

  return r;
}

void *parseArg(char *arg, RSArgType t) {
  void *stackPtr;
  int size;

  switch (t) {
    case AT_INT:
      int i = argToInt(arg);
      stackPtr = &i;
      size = sizeof(int);

    case AT_COLOR:
      Color c = argToColor(arg);
      stackPtr = &c;
      size = sizeof(Color);

    case AT_FLOAT:
      float f = argToFloat(arg);
      stackPtr = &f;
      size = sizeof(float);

    case AT_STRING:
      char *s = argToString(arg);
      stackPtr = &s;
      size = sizeof(char *);

    case AT_VECTOR2:
      Vector2 v = argToVector2(arg);
      stackPtr = &v;
      size = sizeof(Vector2);

    case AT_RECTANGLE:
      Rectangle r = argToRectangle(arg);
      stackPtr = &r;
      size = sizeof(Rectangle);

    default:
      printf("Bad arg type\n");
      return NULL;
  }

  void *out = malloc(size);
  memcpy(out, stackPtr, size);
  return out;
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
