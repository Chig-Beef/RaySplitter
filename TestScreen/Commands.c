#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Commands.h"
#include "../RaySplitter/winray.h"

typedef struct {
  RSImageCode ref;
  Image img;
} ImageRef;

ImageRef images[RSSCREEN_MAX_IMAGES];
int numImages = 0;

void registerImage(Image img) {
  printf("A\n");
  bool takenCodes[RSSCREEN_MAX_IMAGES];
  memset(takenCodes, 0, RSSCREEN_MAX_IMAGES*sizeof(bool));
  for (int i = 0; i < numImages; ++i) {
    takenCodes[images[i].ref] = true;
  }
  printf("B\n");

  RSImageCode code;
  for (int i = 0; i < RSSCREEN_MAX_IMAGES; ++i) {
    if (!takenCodes[i]) {
      code = i;
      break;
    }
  }
  printf("C\n");

  ImageRef ref;
  ref.ref = code;
  ref.img = img;
  printf("D\n");

  images[numImages++] = ref;
  printf("E\n");
}

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
      break;

    case AT_COLOR:
      Color c = argToColor(arg);
      stackPtr = &c;
      size = sizeof(Color);
      break;

    case AT_FLOAT:
      float f = argToFloat(arg);
      stackPtr = &f;
      size = sizeof(float);
      break;

    case AT_STRING:
      char *s = argToString(arg);
      stackPtr = &s;
      size = sizeof(char *);
      break;

    case AT_VECTOR2:
      Vector2 v = argToVector2(arg);
      stackPtr = &v;
      size = sizeof(Vector2);
      break;

    case AT_RECTANGLE:
      Rectangle r = argToRectangle(arg);
      stackPtr = &r;
      size = sizeof(Rectangle);
      break;

    default:
      printf("Bad arg type\n");
      return NULL;
  }

  void *out = malloc(size);
  memcpy(out, stackPtr, size);
  return out;
}

// R_CORE
void setWindowTitleWrapper(void **argv) {
  char *title = *(char**)argv[0];
  SetWindowTitle(title);
}

void setWindowPositionWrapper(void **argv) {
  int x = *(int*)argv[0];
  int y = *(int*)argv[1];
  SetWindowPosition(x, y);
}

void setWindowSizeWrapper(void **argv) {
  int width = *(int*)argv[0];
  int height = *(int*)argv[1];
  SetWindowSize(width, height);
}

void clearBackgroundWrapper(void **argv) {
  Color color = *(Color*)argv[0];
  ClearBackground(color);
}

void takeScreenshotWrapper(void **argv) {
  char* fileName = *(char**)argv[0];
  TakeScreenshot(fileName);
}


// R_SHAPES
void drawPixelWrapper(void **argv) {
  int posX = *(int*)argv[0];
  int posY = *(int*)argv[1];
  Color color = *(Color*)argv[2];
  DrawPixel(posX, posY, color);
}

void drawPixelVWrapper(void **argv) {
  Vector2 position = *(Vector2*)argv[0];
  Color color = *(Color*)argv[1];
  DrawPixelV(position, color);
}

void drawLineWrapper(void **argv) {
  int startPosX = *(int*)argv[0];
  int startPosY = *(int*)argv[1];
  int endPosX = *(int*)argv[2];
  int endPosY = *(int*)argv[3];
  Color color = *(Color*)argv[4];
  DrawLine(startPosX, startPosY, endPosX, endPosY, color);
}

void drawLineVWrapper(void **argv) {
  Vector2 startPos = *(Vector2*)argv[0];
  Vector2 endPos = *(Vector2*)argv[1];
  Color color = *(Color*)argv[2];
  DrawLineV(startPos, endPos, color);
}

void drawLineExWrapper(void **argv) {
  Vector2 startPos = *(Vector2*)argv[0];
  Vector2 endPos = *(Vector2*)argv[1];
  float thick = *(float*)argv[2];
  Color color = *(Color*)argv[3];
  DrawLineEx(startPos, endPos, thick, color);
}

void drawLineBezierWrapper(void **argv) {
  Vector2 startPos = *(Vector2*)argv[0];
  Vector2 endPos = *(Vector2*)argv[1];
  float thick = *(float*)argv[2];
  Color color = *(Color*)argv[3];
  DrawLineBezier(startPos, endPos, thick, color);
}

void drawLineDashedWrapper(void **argv) {
  // ???
}

void drawCircleWrapper(void **argv) {
  int x = *(int*)argv[0];
  int y = *(int*)argv[1];
  float r = *(float*)argv[2];
  Color clr = *(Color*)argv[3];
  DrawCircle(x, y, r, clr);
}

void drawCircleVWrapper(void **argv) {
  Vector2 center = *(Vector2*)argv[0];
  float radius = *(float*)argv[1];
  Color color = *(Color*)argv[2];
  DrawCircleV(center, radius, color);
}

void drawCircleGradientWrapper(void **argv) {
  int centerX = *(int*)argv[0];
  int centerY = *(int*)argv[1];
  float radius = *(float*)argv[2];
  Color color1 = *(Color*)argv[3];
  Color color2 = *(Color*)argv[4];
  DrawCircleGradient(centerX, centerY, radius, color1, color2);
}

void drawCircleSectorWrapper(void **argv) {
  Vector2 center = *(Vector2*)argv[0];
  float radius = *(float*)argv[1];
  float startAngle = *(float*)argv[2];
  float endAngle = *(float*)argv[3];
  int segments = *(int*)argv[4];
  Color color = *(Color*)argv[5];
  DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
}

void drawCircleSectorLinesWrapper(void **argv) {
  Vector2 center = *(Vector2*)argv[0];
  float radius = *(float*)argv[1];
  float startAngle = *(float*)argv[2];
  float endAngle = *(float*)argv[3];
  int segments = *(int*)argv[4];
  Color color = *(Color*)argv[5];
  DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
}

void drawCircleLinesWrapper(void **argv) {
  int centerX = *(int*)argv[0];
  int centerY = *(int*)argv[1];
  float radius = *(float*)argv[2];
  Color color = *(Color*)argv[3];
  DrawCircleLines(centerX, centerY, radius, color);
}

void drawCircleLinesVWrapper(void **argv) {
  Vector2 center = *(Vector2*)argv[0];
  float radius = *(float*)argv[1];
  Color color = *(Color*)argv[2];
  DrawCircleLinesV(center, radius, color);
}

void drawEllipseWrapper(void **argv) {
  int centerX = *(int*)argv[0];
  int centerY = *(int*)argv[1];
  float radiusH = *(float*)argv[2];
  float radiusV = *(float*)argv[3];
  Color color = *(Color*)argv[4];
  DrawEllipse(centerX, centerY, radiusH, radiusV, color);
}

void drawEllipseVWrapper(void **argv) {
  // ??
}

void drawEllipseLinesWrapper(void **argv) {
  int centerX = *(int*)argv[0];
  int centerY = *(int*)argv[1];
  float radiusH = *(float*)argv[2];
  float radiusV = *(float*)argv[3];
  Color color = *(Color*)argv[4];
  DrawEllipse(centerX, centerY, radiusH, radiusV, color);
}

void drawEllipseLinesVWrapper(void **argv) {
  int centerX = *(int*)argv[0];
  int centerY = *(int*)argv[1];
  float radiusH = *(float*)argv[2];
  float radiusV = *(float*)argv[3];
  Color color = *(Color*)argv[4];
  DrawEllipseLines(centerX, centerY, radiusH, radiusV, color);
}

void drawRingWrapper(void **argv) {
  Vector2 center = *(Vector2*)argv[0];
  float innerRadius = *(float*)argv[1];
  float outerRadius = *(float*)argv[2];
  float startAngle = *(float*)argv[3];
  float endAngle = *(float*)argv[4];
  int segments = *(int*)argv[5];
  Color color = *(Color*)argv[6];
  DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
}

void drawRingLinesWrapper(void **argv) {
  // ??
}

void drawRectangleWrapper(void **argv) {
  int x = *(int*)argv[0];
  int y = *(int*)argv[1];
  int w = *(int*)argv[2];
  int h = *(int*)argv[3];
  Color clr = *(Color*)argv[4];

  DrawRectangle(x, y, w, h, clr);
}

void drawRectangleVWrapper(void **argv) {
  Vector2 position = *(Vector2*)argv[0];
  Vector2 size = *(Vector2*)argv[1];
  Color color = *(Color*)argv[2];
  DrawRectangleV(position, size, color);
}

void drawRectangleRecWrapper(void **argv) {
  Rectangle rec = *(Rectangle*)argv[0];
  Color color = *(Color*)argv[1];
  DrawRectangleRec(rec, color);
}

void drawRectangleProWrapper(void **argv) {
  Rectangle rec = *(Rectangle*)argv[0];
  Vector2 origin = *(Vector2*)argv[1];
  float rotation = *(float*)argv[2];
  Color color = *(Color*)argv[3];
  DrawRectanglePro(rec, origin, rotation, color);
}

void drawRectangleGradientVWrapper(void **argv) {
  int posX = *(int*)argv[0];
  int posY = *(int*)argv[1];
  int width = *(int*)argv[2];
  int height = *(int*)argv[3];
  Color color1 = *(Color*)argv[4];
  Color color2 = *(Color*)argv[5];
  DrawRectangleGradientV(posX, posY, width, height, color1, color2);
}

void drawRectangleGradientHWrapper(void **argv) {
  int posX = *(int*)argv[0];
  int posY = *(int*)argv[1];
  int width = *(int*)argv[2];
  int height = *(int*)argv[3];
  Color color1 = *(Color*)argv[4];
  Color color2 = *(Color*)argv[5];
  DrawRectangleGradientH(posX, posY, width, height, color1, color2);
}

void drawRectangleGradientExWrapper(void **argv) {
  Rectangle rec = *(Rectangle*)argv[0];
  Color col1 = *(Color*)argv[1];
  Color col2 = *(Color*)argv[2];
  Color col3 = *(Color*)argv[3];
  Color col4 = *(Color*)argv[4];
  DrawRectangleGradientEx(rec, col1, col2, col3, col4);
}

void drawRectangleLinesWrapper(void **argv) {
  int posX = *(int*)argv[0];
  int posY = *(int*)argv[1];
  int width = *(int*)argv[2];
  int height = *(int*)argv[3];
  Color color = *(Color*)argv[4];
  DrawRectangleLines(posX, posY, width, height, color);
}

void drawRectangleLinesExWrapper(void **argv) {
  Rectangle rec = *(Rectangle*)argv[0];
  float lineThick = *(float*)argv[1];
  Color color = *(Color*)argv[2];
  DrawRectangleLinesEx(rec, lineThick, color);
}

void drawRectangleRoundedWrapper(void **argv) {
  Rectangle rec = *(Rectangle*)argv[0];
  float roundness = *(float*)argv[1];
  int segments = *(int*)argv[2];
  Color color = *(Color*)argv[3];
  DrawRectangleRounded(rec, roundness, segments, color);
}

void drawRectangleRoundedLinesWrapper(void **argv) {
  Rectangle rec = *(Rectangle*)argv[0];
  float roundness = *(float*)argv[1];
  int segments = *(int*)argv[2];
  float lineThick = *(float*)argv[3];
  Color color = *(Color*)argv[4];
  DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color);
}

void drawRectangleRoundedLinesExWrapper(void **argv) {
  // ??
}

void drawTriangleWrapper(void **argv) {
  Vector2 v1 = *(Vector2*)argv[0];
  Vector2 v2 = *(Vector2*)argv[1];
  Vector2 v3 = *(Vector2*)argv[2];
  Color color = *(Color*)argv[3];
  DrawTriangle(v1, v2, v3, color);
}

void drawTriangleLinesWrapper(void **argv) {
  Vector2 v1 = *(Vector2*)argv[0];
  Vector2 v2 = *(Vector2*)argv[1];
  Vector2 v3 = *(Vector2*)argv[2];
  Color color = *(Color*)argv[3];
  DrawTriangleLines(v1, v2, v3, color);
}

void drawPolyWrapper(void **argv) {
  Vector2 center = *(Vector2*)argv[0];
  int sides = *(int*)argv[1];
  float radius = *(float*)argv[2];
  float rotation = *(float*)argv[3];
  Color color = *(Color*)argv[4];
  DrawPoly(center, sides, radius, rotation, color);
}

void drawPolyLinesWrapper(void **argv) {
  Vector2 center = *(Vector2*)argv[0];
  int sides = *(int*)argv[1];
  float radius = *(float*)argv[2];
  float rotation = *(float*)argv[3];
  Color color = *(Color*)argv[4];
  DrawPolyLines(center, sides, radius, rotation, color);
}

void drawPolyLinesExWrapper(void **argv) {
  Vector2 center = *(Vector2*)argv[0];
  int sides = *(int*)argv[1];
  float radius = *(float*)argv[2];
  float rotation = *(float*)argv[3];
  float lineThick = *(float*)argv[4];
  Color color = *(Color*)argv[5];
  DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color);
}

void drawSplineSegmentLinearWrapper(void **argv) {
  Vector2 p1 = *(Vector2*)argv[0];
  Vector2 p2 = *(Vector2*)argv[1];
  float thick = *(float*)argv[2];
  Color color = *(Color*)argv[3];
  DrawSplineSegmentLinear(p1, p2, thick, color);
}

void drawSplineSegmentBasisWrapper(void **argv) {
  Vector2 p1 = *(Vector2*)argv[0];
  Vector2 p2 = *(Vector2*)argv[1];
  Vector2 p3 = *(Vector2*)argv[2];
  Vector2 p4 = *(Vector2*)argv[3];
  float thick = *(float*)argv[4];
  Color color = *(Color*)argv[5];
  DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);
}

void drawSplineSegmentCatmullRomWrapper(void **argv) {
  Vector2 p1 = *(Vector2*)argv[0];
  Vector2 p2 = *(Vector2*)argv[1];
  Vector2 p3 = *(Vector2*)argv[2];
  Vector2 p4 = *(Vector2*)argv[3];
  float thick = *(float*)argv[4];
  Color color = *(Color*)argv[5];
  DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);
}

void drawSplineSegmentBezierQuadraticWrapper(void **argv) {
  Vector2 p1 = *(Vector2*)argv[0];
  Vector2 c2 = *(Vector2*)argv[1];
  Vector2 p3 = *(Vector2*)argv[2];
  float thick = *(float*)argv[3];
  Color color = *(Color*)argv[4];
  DrawSplineSegmentBezierQuadratic(p1, c2, p3, thick, color);
}

void drawSplineSegmentBezierCubicWrapper(void **argv) {
  Vector2 p1 = *(Vector2*)argv[0];
  Vector2 c2 = *(Vector2*)argv[1];
  Vector2 c3 = *(Vector2*)argv[2];
  Vector2 p4 = *(Vector2*)argv[3];
  float thick = *(float*)argv[4];
  Color color = *(Color*)argv[5];
  DrawSplineSegmentBezierCubic(p1, c2, c3, p4, thick, color);
}


// R_TEXTURES
void genImageColorWrapper(void **argv) {
  int width = *(int*)argv[0];
  int height = *(int*)argv[1];
  Color color = *(Color*)argv[2];
  Image img = GenImageColor(width, height, color);
  registerImage(img);
}

// R_TEXT
void drawFpsWrapper(void **argv) {
  int posX = *(int*)argv[0];
  int posY = *(int*)argv[1];
  DrawFPS(posX, posY);
}

void drawTextWrapper(void **argv) {
  char *text = *(char**)argv[0];
  int posX = *(int*)argv[1];
  int posY = *(int*)argv[2];
  int fontSize = *(int*)argv[3];
  Color color = *(Color*)argv[4];
  DrawText(text, posX, posY, fontSize, color);
}

void setTextLineSpacingWrapper(void **argv) {
  int spacing = *(int*)argv[0];
  SetTextLineSpacing(spacing);
}


// R_MODELS
  
// R_AUDIO

FuncWrapper funcs[RS_NUM_FUNCS] = {
  setWindowTitleWrapper, // FC_SET_WINDOW_TITLE
  setWindowPositionWrapper, // FC_SET_WINDOW_POSITION
  setWindowSizeWrapper, // FC_SET_WINDOW_SIZE
  clearBackgroundWrapper, // FC_CLEAR_BACKGROUND
  takeScreenshotWrapper, // FC_TAKE_SCREENSHOT
  drawPixelWrapper, // FC_DRAW_PIXEL
  drawPixelVWrapper, // FC_DRAW_PIXEL_V
  drawLineWrapper, // FC_DRAW_LINE
  drawLineVWrapper, // FC_DRAW_LINE_V
  drawLineExWrapper, // FC_DRAW_LINE_EX
  drawLineBezierWrapper, // FC_DRAW_LINE_BEZIER
  drawLineDashedWrapper, // FC_DRAW_LINE_DASHED
  drawCircleWrapper, // FC_DRAW_CIRCLE
  drawCircleVWrapper, // FC_DRAW_CIRCLE_V
  drawCircleGradientWrapper, // FC_DRAW_CIRCLE_GRADIENT
  drawCircleSectorWrapper, // FC_DRAW_CIRCLE_SECTOR
  drawCircleSectorLinesWrapper, // FC_DRAW_CIRCLE_SECTOR_LINES
  drawCircleLinesWrapper, // FC_DRAW_CIRCLE_LINES
  drawCircleLinesVWrapper, // FC_DRAW_CIRCLE_LINES_V
  drawEllipseWrapper, // FC_DRAW_ELLIPSE
  drawEllipseVWrapper, // FC_DRAW_ELLIPSE_V
  drawEllipseLinesWrapper, // FC_DRAW_ELLIPSE_LINES
  drawEllipseLinesVWrapper, // FC_DRAW_ELLIPSE_LINES_V
  drawRingWrapper, // FC_DRAW_RING
  drawRingLinesWrapper, // FC_DRAW_RING_LINES
  drawRectangleWrapper, // FC_DRAW_RECTANGLE
  drawRectangleVWrapper, // FC_DRAW_RECTANGLE_V
  drawRectangleRecWrapper, // FC_DRAW_RECTANGLE_REC
  drawRectangleProWrapper, // FC_DRAW_RECTANGLE_PRO
  drawRectangleGradientVWrapper, // FC_DRAW_RECTANGLE_GRADIENT_V
  drawRectangleGradientHWrapper, // FC_DRAW_RECTANGLE_GRADIENT_H
  drawRectangleGradientExWrapper, // FC_DRAW_RECTANGLE_GRADIENT_EX
  drawRectangleLinesWrapper, // FC_DRAW_RECTANGLE_LINES
  drawRectangleLinesExWrapper, // FC_DRAW_RECTANGLE_LINES_EX
  drawRectangleRoundedWrapper, // FC_DRAW_RECTANGLE_ROUNDED
  drawRectangleRoundedLinesWrapper, // FC_DRAW_RECTANGLE_ROUNDED_LINES
  drawRectangleRoundedLinesExWrapper, // FC_DRAW_RECTANGLE_ROUNDED_LINES_EX
  drawTriangleWrapper, // FC_DRAW_TRIANGLE
  drawTriangleLinesWrapper, // FC_DRAW_TRIANGLE_LINES
  drawPolyWrapper, // FC_DRAW_POLY
  drawPolyLinesWrapper, // FC_DRAW_POLY_LINES
  drawPolyLinesExWrapper, // FC_DRAW_POLY_LINES_EX
  drawSplineSegmentLinearWrapper, // FC_DRAW_SPLINE_SEGMENT_LINEAR
  drawSplineSegmentBasisWrapper, // FC_DRAW_SPLINE_SEGMENT_BASIS
  drawSplineSegmentCatmullRomWrapper, // FC_DRAW_SPLINE_SEGMENT_CATMULL_ROM
  drawSplineSegmentBezierQuadraticWrapper, // FC_DRAW_SPLINE_SEGMENT_BEZIER_QUADRATIC
  drawSplineSegmentBezierCubicWrapper, // FC_DRAW_SPLINE_SEGMENT_BEZIER_CUBIC
  genImageColorWrapper, // FC_GEN_IMAGE_COLOR
  drawFpsWrapper, // FC_DRAW_FPS
  drawTextWrapper, // FC_DRAW_TEXT
  setTextLineSpacingWrapper, // FC_SET_TEXT_LINE_SPACING
};

FuncStruct getFuncFromCode(int code) {
  if (code < 0 || code >= RS_NUM_FUNCS) return (FuncStruct){0, NULL, 0, NULL};
  RSFuncMetaData md = RSGetFuncMetadata(code);
  return (FuncStruct){code, funcs[code], md.argc, md.argt};
}

void ExecuteFunc(FuncStruct f, int argc, char **argv) {
  // Do we have the correct number of args?
  if (argc != f.argc) {
    printf("Invalid number of args\n");
    return;
  }
  
  // Create an array to hold all the args
  void **v = malloc(argc*sizeof(void*));

  // Parse each arg
  for (int i = 0; i < argc; ++i) {
    v[i] = parseArg(argv[i], f.argt[i]);
    if (v[i] == NULL) {
      return;
    }
  }

  // Execute the function
  f.func(v);

  // Free arg array
  for (int i = 0; i < argc; ++i) {
    free(v[i]);
  }
  free(v);
}
