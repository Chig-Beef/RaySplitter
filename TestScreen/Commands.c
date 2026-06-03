#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Commands.h"

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

// R_CORE
void setWindowTitleWrapper(void **argv) {

}

void setWindowPositionWrapper(void **argv) {

}

void setWindowSizeWrapper(void **argv) {

}

void clearBackgroundWrapper(void **argv) {

}

void takeScreenshotWrapper(void **argv) {

}


// R_SHAPES
void drawPixelWrapper(void **argv) {

}

void drawPixelVWrapper(void **argv) {

}

void drawLineWrapper(void **argv) {

}

void drawLineVWrapper(void **argv) {

}

void drawLineExWrapper(void **argv) {

}

void drawLineBezierWrapper(void **argv) {

}

void drawLineDashedWrapper(void **argv) {

}

void drawCircleWrapper(void **argv) {
  int x = *(int*)argv[0];
  int y = *(int*)argv[1];
  int r = *(int*)argv[2];
  Color clr = *(Color*)argv[3];

  DrawCircle(x, y, r, clr);
}

void drawCircleVWrapper(void **argv) {

}

void drawCircleGradientWrapper(void **argv) {

}

void drawCircleSectorWrapper(void **argv) {

}

void drawCircleSectorLinesWrapper(void **argv) {

}

void drawCircleLinesWrapper(void **argv) {

}

void drawCircleLinesVWrapper(void **argv) {

}

void drawEllipseWrapper(void **argv) {

}

void drawEllipseVWrapper(void **argv) {

}

void drawEllipseLinesWrapper(void **argv) {

}

void drawEllipseLinesVWrapper(void **argv) {

}

void drawRingWrapper(void **argv) {

}

void drawRingLinesWrapper(void **argv) {

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

}

void drawRectangleRecWrapper(void **argv) {

}

void drawRectangleProWrapper(void **argv) {

}

void drawRectangleGradientVWrapper(void **argv) {

}

void drawRectangleGradientHWrapper(void **argv) {

}

void drawRectangleGradientExWrapper(void **argv) {

}

void drawRectangleLinesWrapper(void **argv) {

}

void drawRectangleLinesExWrapper(void **argv) {

}

void drawRectangleRoundedWrapper(void **argv) {

}

void drawRectangleRoundedLinesWrapper(void **argv) {

}

void drawRectangleRoundedLinesExWrapper(void **argv) {

}

void drawTriangleWrapper(void **argv) {

}

void drawTriangleLinesWrapper(void **argv) {

}

void drawPolyWrapper(void **argv) {

}

void drawPolyLinesWrapper(void **argv) {

}

void drawPolyLinesExWrapper(void **argv) {

}

void drawSplineSegmentLinearWrapper(void **argv) {

}

void drawSplineSegmentBasisWrapper(void **argv) {

}

void drawSplineSegmentCatmullRomWrapper(void **argv) {

}

void drawSplineSegmentBezierQuadraticWrapper(void **argv) {

}

void drawSplineSegmentBezierCubicWrapper(void **argv) {

}


// R_TEXTURES

// R_TEXT
void drawFpsWrapper(void **argv) {

}

void drawTextWrapper(void **argv) {

}

void setTextLineSpacingWrapper(void **argv) {

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
  }

  // Execute the function
  f.func(v);

  // Free arg array
  free(v);
}
