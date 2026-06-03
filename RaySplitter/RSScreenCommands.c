#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "RSScreenCommands.h"
#include "RSCommand.h"
#include "RSScreen.h"
#include "RScommand.h"

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

RSArgType funcArgTypes[RS_NUM_FUNCS][10] = {
  {AT_STRING}, // FC_SET_WINDOW_TITLE
  {AT_INT, AT_INT}, // FC_SET_WINDOW_POSITION
  {AT_INT, AT_INT}, // FC_SET_WINDOW_SIZE
  {AT_COLOR}, // FC_CLEAR_BACKGROUND
  {AT_STRING}, // FC_TAKE_SCREENSHOT
  {AT_INT, AT_INT, AT_COLOR}, // FC_DRAW_PIXEL
  {AT_VECTOR2, AT_COLOR}, // FC_DRAW_PIXEL_V
  {AT_INT, AT_INT, AT_INT, AT_INT, AT_COLOR}, // FC_DRAW_LINE
  {AT_VECTOR2, AT_VECTOR2, AT_COLOR}, // FC_DRAW_LINE_V
  {AT_VECTOR2, AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_LINE_EX
  {AT_VECTOR2, AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_LINE_BEZIER
  {AT_VECTOR2, AT_VECTOR2, AT_INT, AT_INT, AT_COLOR}, // DC_DRAW_LINE_DASHED
  {AT_INT, AT_INT, AT_FLOAT, AT_COLOR}, // FC_DRAW_CIRCLE
  {AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_CIRCLE_V
  {AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_CIRCLE_GRADIENT
  {AT_VECTOR2, AT_FLOAT, AT_FLOAT, AT_FLOAT, AT_INT, AT_COLOR}, // FC_DRAW_CIRCLE_SECTOR
  {AT_VECTOR2, AT_FLOAT, AT_FLOAT, AT_FLOAT, AT_INT, AT_COLOR}, // FC_DRAW_CIRCLE_SECTOR_LINES
  {AT_INT, AT_INT, AT_FLOAT, AT_COLOR}, // FC_DRAW_CIRCLE_LINES
  {AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_CIRCLE_LINES_V
  {AT_INT, AT_INT, AT_FLOAT, AT_FLOAT, AT_COLOR}, // FC_DRAW_ELLIPSE
  {AT_VECTOR2, AT_FLOAT, AT_FLOAT, AT_COLOR}, // FC_DRAW_ELLIPSE_V
  {AT_INT, AT_INT, AT_FLOAT, AT_FLOAT, AT_COLOR}, // FC_DRAW_ELLIPSE_LINES
  {AT_VECTOR2, AT_FLOAT, AT_FLOAT, AT_COLOR}, // FC_DRAW_ELLIPSE_LINES_V
  {AT_VECTOR2, AT_FLOAT, AT_FLOAT, AT_FLOAT, AT_FLOAT, AT_INT, AT_COLOR}, // FC_DRAW_RING
  {AT_VECTOR2, AT_FLOAT, AT_FLOAT, AT_FLOAT, AT_FLOAT, AT_INT, AT_COLOR}, // FC_DRAW_RING_LINES
  {AT_INT, AT_INT, AT_INT, AT_INT, AT_COLOR}, // FC_DRAW_RECTANGLE
  {AT_VECTOR2, AT_VECTOR2, AT_COLOR}, // FC_DRAW_RECTANGLE_V
  {AT_RECTANGLE, AT_COLOR}, // FC_DRAW_RECTANGLE_REC
  {AT_RECTANGLE, AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_RECTANGLE_PRO
  {AT_INT, AT_INT, AT_INT, AT_INT, AT_COLOR, AT_COLOR}, // FC_DRAW_RECTANGLE_GRADIENT_V
  {AT_INT, AT_INT, AT_INT, AT_INT, AT_COLOR, AT_COLOR}, // FC_DRAW_RECTANGLE_GRADIENT_H
  {AT_RECTANGLE, AT_COLOR, AT_COLOR, AT_COLOR, AT_COLOR}, // FC_DRAW_RECTANGLE_GRADIENT_EX
  {AT_INT, AT_INT, AT_INT, AT_INT, AT_COLOR}, // FC_DRAW_RECTANGLE_LINES
  {AT_RECTANGLE, AT_FLOAT, AT_COLOR}, // FC_DRAW_RECTANGLE_LINES_EX
  {AT_RECTANGLE, AT_FLOAT, AT_INT, AT_COLOR}, // FC_DRAW_RECTANGLE_ROUNDED
  {AT_RECTANGLE, AT_FLOAT, AT_INT, AT_COLOR}, // FC_DRAW_RECTANGLE_ROUNDED_LINES
  {AT_RECTANGLE, AT_FLOAT, AT_INT, AT_FLOAT, AT_COLOR}, // FC_DRAW_RECTANGLE_ROUNDED_LINES_EX
  {AT_VECTOR2, AT_VECTOR2, AT_VECTOR2, AT_COLOR}, // FC_DRAW_TRIANGLE
  {AT_VECTOR2, AT_VECTOR2, AT_VECTOR2, AT_COLOR}, // FC_DRAW_TRIANGLE_LINES
  {AT_VECTOR2, AT_INT, AT_FLOAT, AT_FLOAT, AT_COLOR}, // FC_DRAW_POLY
  {AT_VECTOR2, AT_INT, AT_FLOAT, AT_FLOAT, AT_COLOR}, // FC_DRAW_POLY_LINES
  {AT_VECTOR2, AT_INT, AT_FLOAT, AT_FLOAT, AT_FLOAT, AT_COLOR}, // FC_DRAW_POLY_LINES_EX
  {AT_VECTOR2, AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_SPLINE_SEGMENT_LINEAR
  {AT_VECTOR2, AT_VECTOR2, AT_VECTOR2, AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_SPLINE_SEGMENT_BASIS
  {AT_VECTOR2, AT_VECTOR2, AT_VECTOR2, AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_SPLINE_SEGMENT_CATMULL_ROM
  {AT_VECTOR2, AT_VECTOR2, AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_SPLINE_SEGMENT_BEZIER_QUADRATIC
  {AT_VECTOR2, AT_VECTOR2, AT_VECTOR2, AT_VECTOR2, AT_FLOAT, AT_COLOR}, // FC_DRAW_SPLINE_SEGMENT_BEZIER_CUBIC
  {AT_INT, AT_INT}, // FC_DRAW_FPS
  {AT_STRING, AT_INT, AT_INT, AT_INT, AT_COLOR}, // FC_DRAW_TEXT
  {AT_INT}, // FC_SET_TEXT_LINE_SPACING
};

int funcArgc[RS_NUM_FUNCS] = {
  1, // FC_SET_WINDOW_TITLE
  2, // FC_SET_WINDOW_POSITION
  2, // FC_SET_WINDOW_SIZE
  1, // FC_CLEAR_BACKGROUND
  1, // FC_TAKE_SCREENSHOT
  3, // FC_DRAW_PIXEL
  2, // FC_DRAW_PIXEL_V
  5, // FC_DRAW_LINE
  3, // FC_DRAW_LINE_V
  4, // FC_DRAW_LINE_EX
  4, // FC_DRAW_LINE_BEZIER
  5, // DC_DRAW_LINE_DASHED
  4, // FC_DRAW_CIRCLE
  3, // FC_DRAW_CIRCLE_V
  4, // FC_DRAW_CIRCLE_GRADIENT
  6, // FC_DRAW_CIRCLE_SECTOR
  6, // FC_DRAW_CIRCLE_SECTOR_LINES
  4, // FC_DRAW_CIRCLE_LINES
  3, // FC_DRAW_CIRCLE_LINES_V
  5, // FC_DRAW_ELLIPSE
  4, // FC_DRAW_ELLIPSE_V
  5, // FC_DRAW_ELLIPSE_LINES
  4, // FC_DRAW_ELLIPSE_LINES_V
  7, // FC_DRAW_RING
  7, // FC_DRAW_RING_LINES
  5, // FC_DRAW_RECTANGLE
  3, // FC_DRAW_RECTANGLE_V
  2, // FC_DRAW_RECTANGLE_REC
  4, // FC_DRAW_RECTANGLE_PRO
  6, // FC_DRAW_RECTANGLE_GRADIENT_V
  6, // FC_DRAW_RECTANGLE_GRADIENT_H
  5, // FC_DRAW_RECTANGLE_GRADIENT_EX
  5, // FC_DRAW_RECTANGLE_LINES
  3, // FC_DRAW_RECTANGLE_LINES_EX
  4, // FC_DRAW_RECTANGLE_ROUNDED
  4, // FC_DRAW_RECTANGLE_ROUNDED_LINES
  5, // FC_DRAW_RECTANGLE_ROUNDED_LINES_EX
  4, // FC_DRAW_TRIANGLE
  4, // FC_DRAW_TRIANGLE_LINES
  5, // FC_DRAW_POLY
  5, // FC_DRAW_POLY_LINES
  6, // FC_DRAW_POLY_LINES_EX
  4, // FC_DRAW_SPLINE_SEGMENT_LINEAR
  6, // FC_DRAW_SPLINE_SEGMENT_BASIS
  6, // FC_DRAW_SPLINE_SEGMENT_CATMULL_ROM
  5, // FC_DRAW_SPLINE_SEGMENT_BEZIER_QUADRATIC
  6, // FC_DRAW_SPLINE_SEGMENT_BEZIER_CUBIC
  2, // FC_DRAW_FPS
  5, // FC_DRAW_TEXT
  1, // FC_SET_TEXT_LINE_SPACING
};

RSFuncMetaData RSGetFuncMetadata(FuncCode func) {
  if (func >= RS_NUM_FUNCS) {
    return (RSFuncMetaData){0, NULL};
  }

  return (RSFuncMetaData){funcArgc[func], funcArgTypes[func]};
}

void RSDeployCommand(RSScreen *screen, FuncCode func, void **argv) {
  if (func >= RS_NUM_FUNCS) {
    printf("Invalid func code given\n");
    return;
  }

  RSCommand cmd;

  // Get some info about this func
  const int argc = funcArgc[func];
  RSArgType *argt = funcArgTypes[func];

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
void RSScreenSetWindowTitle(RSScreen *screen, const char *title) {
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


void RSScreenTakeScreenShot(RSScreen *screen, const char *fileName) {
  const FuncCode func = FC_TAKE_SCREENSHOT;
  void *argv[1] = {&fileName};
  RSDeployCommand(screen, func, argv);
}


// R_SHAPES
void RSScreenDrawPixel(RSScreen *screen, int posX, int posY, Color color) {
  const FuncCode func = FC_DRAW_PIXEL;
  void *argv[3] = {&posX, &posY, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawPixelV(RSScreen *screen, Vector2 position, Color color) {
  const FuncCode func = FC_DRAW_PIXEL_V;
  void *argv[2] = {&position, &color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawLine(RSScreen *screen, int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
  const FuncCode func = FC_DRAW_LINE;
  void *argv[5] = {&startPosX, &startPosY, &endPosX, &endPosY, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawLineV(RSScreen *screen, Vector2 startPos, Vector2 endPos, Color color) {
  const FuncCode func = FC_DRAW_LINE_V;
  void *argv[3] = {&startPos, &endPos, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawLineEx(RSScreen *screen, Vector2 startPos, Vector2 endPos, float thick, Color color) {
  const FuncCode func = FC_DRAW_LINE_EX;
  void *argv[4] = {&startPos, &endPos, &thick, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawLineBezier(RSScreen *screen, Vector2 startPos, Vector2 endPos, float thick, Color color) {
  const FuncCode func = FC_DRAW_LINE_BEZIER;
  void *argv[4] = {&startPos, &endPos, &thick, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawLineDashed(RSScreen *screen, Vector2 startPos, Vector2 endPos, int dashSize, int spaceSize, Color color) {
  const FuncCode func = FC_DRAW_LINE_DASHED;
  void *argv[5] = {&startPos, &endPos, &dashSize, &spaceSize, &color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawCircle(RSScreen *screen, int centerX, int centerY, float radius, Color color) {
  const FuncCode func = FC_DRAW_CIRCLE;
  void *argv[4] = {&centerX, &centerY, &radius, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawCircleV(RSScreen *screen, Vector2 center, float radius, Color color) {
  const FuncCode func = FC_DRAW_CIRCLE_V;
  void *argv[3] = {&center, &radius, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawCircleGradient(RSScreen *screen, Vector2 center, float radius, Color inner, Color outer) {
  const FuncCode func = FC_DRAW_CIRCLE_GRADIENT;
  void *argv[4] = {&center, &radius, &inner, &outer};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawCircleSector(RSScreen *screen, Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color) {
  const FuncCode func = FC_DRAW_CIRCLE_SECTOR;
  void *argv[6] = {&center, &radius, &startAngle, &endAngle, &segments, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawCircleSectorLines(RSScreen *screen, Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color) {
  const FuncCode func = FC_DRAW_CIRCLE_SECTOR_LINES;
  void *argv[6] = {&center, &radius, &startAngle, &endAngle, &segments, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawCircleLines(RSScreen *screen, int centerX, int centerY, float radius, Color color) {
  const FuncCode func = FC_DRAW_CIRCLE_LINES;
  void *argv[4] = {&centerX, &centerY, &radius, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawCircleLinesV(RSScreen *screen, Vector2 center, float radius, Color color) {
  const FuncCode func = FC_DRAW_CIRCLE_LINES_V;
  void *argv[3] = {&center, &radius, &color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawEllipse(RSScreen *screen, int centerX, int centerY, float radiusH, float radiusV, Color color) {
  const FuncCode func = FC_DRAW_ELLIPSE;
  void *argv[5] = {&centerX, &centerY, &radiusH, &radiusV, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawEllipseV(RSScreen *screen, Vector2 center, float radiusH, float radiusV, Color color) {
  const FuncCode func = FC_DRAW_ELLIPSE_V;
  void *argv[4] = {&center, &radiusH, &radiusV, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawEllipseLines(RSScreen *screen, int centerX, int centerY, float radiusH, float radiusV, Color color) {
  const FuncCode func = FC_DRAW_ELLIPSE_LINES;
  void *argv[5] = {&centerX, &centerY, &radiusH, &radiusV, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawEllipseLinesV(RSScreen *screen, Vector2 center, float radiusH, float radiusV, Color color) {
  const FuncCode func = FC_DRAW_ELLIPSE_LINES_V;
  void *argv[4] = {&center, &radiusH, &radiusV, &color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawRing(RSScreen *screen, Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) {
  const FuncCode func = FC_DRAW_RING;
  void *argv[7] = {&center, &innerRadius, &outerRadius, &startAngle, &endAngle, &segments, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRingLines(RSScreen *screen, Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) {
  const FuncCode func = FC_DRAW_RING_LINES;
  void *argv[7] = {&center, &innerRadius, &outerRadius, &startAngle, &endAngle, &segments, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangle(RSScreen *screen, int posX, int posY, int width, int height, Color color) {
  const FuncCode func = FC_DRAW_RECTANGLE;
  void *argv[5] = {&posX, &posY, &width, &height, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleV(RSScreen *screen, Vector2 position, Vector2 size, Color color) {
  const FuncCode func = FC_DRAW_RECTANGLE_V;
  void *argv[3] = {&position, &size, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleRec(RSScreen *screen, Rectangle rec, Color color) {
  const FuncCode func = FC_DRAW_RECTANGLE_REC;
  void *argv[2] = {&rec, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectanglePro(RSScreen *screen, Rectangle rec, Vector2 origin, float rotation, Color color) {
  const FuncCode func = FC_DRAW_RECTANGLE_PRO;
  void *argv[4] = {&rec, &origin, &rotation, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleGradientV(RSScreen *screen, int posX, int posY, int width, int height, Color top, Color bottom) {
  const FuncCode func = FC_DRAW_RECTANGLE_GRADIENT_V;
  void *argv[6] = {&posX, &posY, &width, &height, &top, &bottom};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleGradientH(RSScreen *screen, int posX, int posY, int width, int height, Color left, Color right) {
  const FuncCode func = FC_DRAW_RECTANGLE_GRADIENT_H;
  void *argv[6] = {&posX, &posY, &width, &height, &left, &right};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleGradientEx(RSScreen *screen, Rectangle rec, Color topLeft, Color bottomLeft, Color bottomRight, Color topRight) {
  const FuncCode func = FC_DRAW_RECTANGLE_GRADIENT_EX;
  void *argv[5] = {&rec, &topLeft, &bottomLeft, &bottomRight, &topRight};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleLines(RSScreen *screen, int posX, int posY, int width, int height, Color color) {
  const FuncCode func = FC_DRAW_RECTANGLE_LINES;
  void *argv[5] = {&posX, &posY, &width, &height, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleLinesEx(RSScreen *screen, Rectangle rec, float lineThick, Color color) {
  const FuncCode func = FC_DRAW_RECTANGLE_LINES_EX;
  void *argv[3] = {&rec, &lineThick, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleRounded(RSScreen *screen, Rectangle rec, float roundness, int segments, Color color) {
  const FuncCode func = FC_DRAW_RECTANGLE_ROUNDED;
  void *argv[4] = {&rec, &roundness, &segments, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleRoundedLines(RSScreen *screen, Rectangle rec, float roundness, int segments, Color color) {
  const FuncCode func = FC_DRAW_RECTANGLE_ROUNDED_LINES;
  void *argv[4] = {&rec, &roundness, &segments, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawRectangleRoundedLinesEx(RSScreen *screen, Rectangle rec, float roundness, int segments, float lineThick, Color color) {
  const FuncCode func = FC_DRAW_RECTANGLE_ROUNDED_LINES_EX;
  void *argv[5] = {&rec, &roundness, &segments, &lineThick, &color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawTriangle(RSScreen *screen, Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
  const FuncCode func = FC_DRAW_TRIANGLE;
  void *argv[4] = {&v1, &v2, &v3, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawTriangleLines(RSScreen *screen, Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
  const FuncCode func = FC_DRAW_TRIANGLE_LINES;
  void *argv[4] = {&v1, &v2, &v3, &color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawPoly(RSScreen *screen, Vector2 center, int sides, float radius, float rotation, Color color) {
  const FuncCode func = FC_DRAW_POLY;
  void *argv[5] = {&center, &sides, &radius, &rotation, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawPolyLines(RSScreen *screen, Vector2 center, int sides, float radius, float rotation, Color color) {
  const FuncCode func = FC_DRAW_POLY_LINES;
  void *argv[5] = {&center, &sides, &radius, &rotation, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawPolyLinesEx(RSScreen *screen, Vector2 center, int sides, float radius, float rotation, float lineThick, Color color) {
  const FuncCode func = FC_DRAW_POLY_LINES_EX;
  void *argv[6] = {&center, &sides, &radius, &rotation, &lineThick, &color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawSplineSegmentLinear(RSScreen *screen, Vector2 p1, Vector2 p2, float thick, Color color) {
  const FuncCode func = FC_DRAW_SPLINE_SEGMENT_LINEAR;
  void *argv[4] = {&p1, &p2, &thick, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawSplineSegmentBasis(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color) {
  const FuncCode func = FC_DRAW_SPLINE_SEGMENT_BASIS;
  void *argv[6] = {&p1, &p2, &p3, &p4, &thick, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawSplineSegmentCatmullRom(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color) {
  const FuncCode func = FC_DRAW_SPLINE_SEGMENT_CATMULL_ROM;
  void *argv[6] = {&p1, &p2, &p3, &p4, &thick, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawSplineSegmentBezierQuadratic(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, float thick, Color color) {
  const FuncCode func = FC_DRAW_SPLINE_SEGMENT_BEZIER_QUADRATIC;
  void *argv[5] = {&p1, &p2, &p3, &thick, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawSplineSegmentBezierCubic(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color) {
  const FuncCode func = FC_DRAW_SPLINE_SEGMENT_BEZIER_CUBIC;
  void *argv[6] = {&p1, &p2, &p3, &p4, &thick, &color};
  RSDeployCommand(screen, func, argv);
}


// R_TEXTURES

// R_TEXT
void RSScreenDrawFPS(RSScreen *screen, int posX, int posY) {
  const FuncCode func = FC_DRAW_FPS;
  void *argv[2] = {&posX, &posY};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawText(RSScreen *screen, int posX, int posY, int fontSize, Color color) {
  const FuncCode func = FC_DRAW_TEXT;
  void *argv[4] = {&posX, &posY, &fontSize, &color};
  RSDeployCommand(screen, func, argv);
}


void RSScreenSetTextLineSpacing(RSScreen *screen, int spacing) {
  const FuncCode func = FC_SET_TEXT_LINE_SPACING;
  void *argv[1] = {&spacing};
  RSDeployCommand(screen, func, argv);
}



// R_MODELS
  
// R_AUDIO
