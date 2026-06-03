#include <corecrt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "RSCommand.h"
#include "RSImage.h"
#include "RSTexture.h"
#include "winray.h"

void RSCommandFree(RSCommand *cmd) {
  for (int i = 0; i < cmd->argc; ++i) {
    free(cmd->argv[i]);
  }
  free(cmd->argv);
}

char *RSCommandPackage(RSCommand *cmd) {
  // A byte for the func
  int totalSize = 3;

  // Add bytes for the spaces
  totalSize += cmd->argc;

  // Add length of each arg
  for (int i = 0; i < cmd->argc; ++i) {
    totalSize += strlen(cmd->argv[i]);
  }

  // Allocate buffer
  char *out = malloc(totalSize+2);
  char *p = out;
  
  // Place in func
  *p = ((cmd->func/100)%10)+'0';
  ++p;
  *p = ((cmd->func/10)%10)+'0';
  ++p;
  *p = ((cmd->func)%10)+'0';
  ++p;

  // Place in args
  for (int i = 0; i < cmd->argc; ++i) {
    // Space at front
    *p = ' ';
    ++p;

    // Arg
    char *s = cmd->argv[i];
    while (*s) {
      *p = *s;
      ++s;
      ++p;
    }
  }

  // Close
  out[totalSize] = '\n';
  out[totalSize+1] = 0;
  return out;
}

errno_t RSCommandInit(RSCommand *cmd, int argc, FuncCode func) {
  cmd->func = func;
  cmd->argc = argc;
  cmd->argv = malloc(argc*sizeof(char*));
  if (!cmd->argv) {
    printf("Couldn't allocate argv buffer for cmd\n");
    return 1;
  }
  return 0;
}


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

char *argFromStr(const char *str) {
  const int len = strlen(str);
  char *buffer = malloc(len+1);
  memcpy(buffer, str, len);
  buffer[len] = 0;
  return buffer;
}

char *argFromFloat(float f) {
  char *buffer = malloc(20);
  sprintf_s(buffer, 20, "%f", f);
  return buffer;
}

char *argFromVector2(Vector2 v) {
  char *buffer = malloc(100);
  if (!buffer) {
    return NULL;
  }
  sprintf_s(buffer, 100, "%i-%i", v.x, v.y);
  return buffer;
}

char *argFromRectangle(Rectangle rect) {
  char *buffer = malloc(100);
  if (!buffer) {
    return NULL;
  }
  sprintf_s(buffer, 100, "%i-%i-%i-%i", rect.x, rect.y, rect.width, rect.height);
  return buffer;
}

char *argFromImage(RSImage img) {
  return argFromInt(img.ref);
}

char *argFromTexture(RSTexture tex) {
  return argFromInt(tex.ref);
}

char *stringifyRawArg(void *v, RSArgType t) {
  switch (t) {
    case AT_INT:
      return argFromInt(*(int*)v);
    case AT_COLOR:
      return argFromColor(*(Color*)v);
    case AT_FLOAT:
      return argFromFloat(*(float*)v);
    case AT_STRING:
      return argFromStr(*(char**)v);
    case AT_VECTOR2:
      return argFromVector2(*(Vector2*)v);
    case AT_RECTANGLE:
      return argFromRectangle(*(Rectangle*)v);
    case AT_IMAGE:
      return argFromImage(*(RSImage*)v);
    case AT_TEXTURE:
      return argFromTexture(*(RSTexture*)v);

    default: // Bad type
      return NULL;
  }
}

errno_t RSCommandPopulate(RSCommand *cmd, int argc, void **argv, RSArgType *argt) {
  // Over each arg
  for (int i = 0; i < argc; ++i) {
    // Using the type, convert the value to a string
    cmd->argv[i] = stringifyRawArg(argv[i], argt[i]);

    // If we failed
    if (cmd->argv[i] == NULL) {
      printf("Invalid arg!\n");
      // TODO: Cleanup
      return 1;
    }
  }

  return 0;
}
