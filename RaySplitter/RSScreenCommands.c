#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "RSScreenCommands.h"
#include "RSCommand.h"
#include "RSScreen.h"

typedef enum {
  AT_INT,
  AT_COLOR,
  AT_FLOAT,
  AT_STRING,
  AT_VECTOR2,
  AT_RECTANGLE,
} RSArgType;

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

void RSDeployCommand(RSScreen *screen, FuncCode func, int argc, void **argv, RSArgType *argt) {
  RSCommand cmd;

  if (RSCommandInit(&cmd, argc, func)) {
    printf("Couldn't initialise command\n");
    return;
  }

  errno_t err = RSCommandPopulate(&cmd, argc, argv, argt);
  if (err) {
    printf("Couldn't populate command\n");
    return;
  }

  RSScreenQueuePush(screen, cmd);
}

// R_CORE
void RSScreenSetWindowTitle(RSScreen *screen, const char *title);
void RSScreenSetWindowPosition(RSScreen *screen, int x, int y);
void RSScreenSetWindowSize(RSScreen *screen, int width, int height);

void RSScreenClearBackground(RSScreen *screen, Color color);

void RSScreenTakeScreenShot(RSScreen *screen, const char *fileName);

// R_SHAPES
void RSScreenDrawPixel(RSScreen *screen, int posX, int posY, Color color);
void RSScreenDrawPixelV(RSScreen *screen, Vector2 position, Color color);

void RSScreenDrawLine(RSScreen *screen, int startPosX, int startPosY, int endPosX, int endPosY, Color color);
void RSScreenDrawLineV(RSScreen *screen, Vector2 startPos, Vector2 endPos, Color color);
void RSScreenDrawLineEx(RSScreen *screen, Vector2 startPos, Vector2 endPos, float thick, Color color);
void RSScreenDrawLineBezier(RSScreen *screen, Vector2 startPos, Vector2 endPos, float thick, Color color);
void RSScreenDrawLineDashed(RSScreen *screen, Vector2 startPos, Vector2 endPos, int dashSize, int spaceSize, Color color);

void RSScreenDrawCircle(RSScreen *screen, int centerX, int centerY, float radius, Color color) {
  // Line up args in an array
  void *argv[4] = {
    &centerX,
    &centerY,
    &radius,
    &color,
  };

  // Specify the types of each arg
  RSArgType argt[4] = {
    AT_INT,
    AT_INT,
    AT_FLOAT,
    AT_COLOR,
  };

  RSDeployCommand(screen, FC_DRAW_CIRCLE, 4, arv, argt);
}

void RSScreenDrawCircleV(RSScreen *screen, Vector2 center, float radius, Color color) {
  // Line up args in an array
  void *argv[3] = {
    &center,
    &radius,
    &color,
  };

  // Specify the types of each arg
  RSArgType argt[3] = {
    AT_VECTOR2,
    AT_FLOAT,
    AT_COLOR,
  };

  RSDeployCommand(screen, FC_DRAW_CIRCLE_V, 3, arv, argt);
}

void RSScreenDrawCircleGradient(RSScreen *screen, Vector2 center, float radius, Color color) {
  // Line up args in an array
  void *argv[3] = {
    &center,
    &radius,
    &color,
  };

  // Specify the types of each arg
  RSArgType argt[3] = {
    AT_VECTOR2,
    AT_FLOAT,
    AT_COLOR,
  };

  RSDeployCommand(screen, FC_DRAW_CIRCLE_GRADIENT, 3, arv, argt);
}

void RSScreenDrawCircleSector(RSScreen *screen, Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color) {
  // Line up args in an array
  void *argv[6] = {
    &center,
    &radius,
    &startAngle,
    &endAngle,
    &segments,
    &color,
  };

  // Specify the types of each arg
  RSArgType argt[6] = {
    AT_VECTOR2,
    AT_FLOAT,
    AT_FLOAT,
    AT_FLOAT,
    AT_INT,
    AT_COLOR,
  };

  RSDeployCommand(screen, FC_DRAW_CIRCLE_SECTOR, 6, arv, argt);
}

void RSScreenDrawCircleSectorLines(RSScreen *screen, Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);
void RSScreenDrawCircleLines(RSScreen *screen, int centerX, int centerY, float radius, Color color);
void RSScreenDrawCircleLinesV(RSScreen *screen, Vector2 center, float radius, Color color);

void RSScreenDrawEllipse(RSScreen *screen, int centerX, int centerY, float radiusH, float radiusV, Color color);
void RSScreenDrawEllipseV(RSScreen *screen, Vector2 center, float radiusH, float radiusV, Color color);
void RSScreenDrawEllipseLines(RSScreen *screen, int centerX, int centerY, float radiusH, float radiusV, Color color);
void RSScreenDrawEllipseLinesV(RSScreen *screen, Vector2 center, float radiusH, float radiusV, Color color);

void RSScreenDrawRing(RSScreen *screen, Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);
void RSScreenDrawRingLines(RSScreen *screen, Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);

void RSScreenDrawRectangle(RSScreen *screen, int posX, int posY, int width, int height, Color color) {
  // Line up args in an array
  void *argv[5] = {
    &posX,
    &posY,
    &width,
    &height,
    &color,
  };

  // Specify the types of each arg
  RSArgType argt[5] = {
    AT_INT,
    AT_INT,
    AT_INT,
    AT_INT,
    AT_COLOR,
  };

  RSDeployCommand(screen, FC_DRAW_RECTANGLE, 5, arv, argt);
}

void RSScreenDrawRectangleV(RSScreen *screen, Vector2 position, Vector2 size, Color color);
void RSScreenDrawRectangleRec(RSScreen *screen, Rectangle rec, Color color);
void RSScreenDrawRectanglePro(RSScreen *screen, Rectangle rec, Vector2 origin, float rotation, Color color);
void RSScreenDrawRectangleGradientV(RSScreen *screen, int posX, int posY, int width, int height, Color top, Color bottom);
void RSScreenDrawRectangleGradientH(RSScreen *screen, int posX, int posY, int width, int height, Color left, Color right);
void RSScreenDrawRectangleGradientEx(RSScreen *screen, Rectangle rec, Color topLeft, Color bottomLeft, Color bottomRight, Color topRight);
void RSScreenDrawRectangleLines(RSScreen *screen, int posX, int posY, int width, int height, Color color);
void RSScreenDrawRectangleLinesEx(RSScreen *screen, Rectangle rec, float lineThick, Color color);
void RSScreenDrawRectangleRounded(RSScreen *screen, Rectangle rec, float roundness, int segments, Color color);
void RSScreenDrawRectangleRoundedLines(RSScreen *screen, Rectangle rec, float roundness, int segments, Color color);
void RSScreenDrawRectangleRoundedLinesEx(RSScreen *screen, Rectangle rec, float roundness, int segments, float lineThick, Color color);

void RSScreenDrawTriangle(RSScreen *screen, Vector2 v1, Vector2 v2, Vector2 v3, Color color);
void RSScreenDrawTriangleLines(RSScreen *screen, Vector2 v1, Vector2 v2, Vector2 v3, Color color);

void RSScreenDrawPoly(RSScreen *screen, Vector2 center, int sides, float radius, float rotation, Color color);
void RSScreenDrawPolyLines(RSScreen *screen, Vector2 center, int sides, float radius, float rotation, Color color);
void RSScreenDrawPolyLinesEx(RSScreen *screen, Vector2 center, int sides, float radius, float rotation, float lineThick, Color color);

void RSScreenDrawSplineSegmentLinear(RSScreen *screen, Vector2 p1, Vector2 p2, float thick, Color color);
void RSScreenDrawSplineSegmentBasis(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color);
void RSScreenDrawSplineSegmentCatmullRom(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color);
void RSScreenDrawSplineSegmentQuadratic(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, float thick, Color color);
void RSScreenDrawSplineSegmentCubic(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color);

// R_TEXTURES

// R_TEXT
void RSScreenDrawFPS(RSScreen *screen, int x, int y, int width, int height, Color color);

void RSScreenDrawText(RSScreen *screen, int x, int y, int width, int height, Color color);
void RSScreenDrawTextEx(RSScreen *screen, int x, int y, int width, int height, Color color);
void RSScreenDrawTextPro(RSScreen *screen, int x, int y, int width, int height, Color color);
void RSScreenDrawTextCodepoint(RSScreen *screen, int x, int y, int width, int height, Color color);
void RSScreenDrawTextCodepoints(RSScreen *screen, int x, int y, int width, int height, Color color);

void RSScreenSetTextLineSpacing(RSScreen *screen, int x, int y, int width, int height, Color color);

// R_MODELS
  
// R_AUDIO
