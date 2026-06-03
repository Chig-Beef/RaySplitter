#ifndef _RS_SCREEN_COMMANDS_H_
#define _RS_SCREEN_COMMANDS_H_

#include "winray.h"
#include "RSScreen.h"

typedef struct {
  int argc;
  RSArgType *argt;
} RSFuncMetaData;

RSFuncMetaData RSGetFuncMetadata(FuncCode func);

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

void RSScreenDrawCircle(RSScreen *screen, int centerX, int centerY, float radius, Color color);
void RSScreenDrawCircleV(RSScreen *screen, Vector2 center, float radius, Color color);
void RSScreenDrawCircleGradient(RSScreen *screen, Vector2 center, float radius, Color inner, Color outer);
void RSScreenDrawCircleSector(RSScreen *screen, Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);
void RSScreenDrawCircleSectorLines(RSScreen *screen, Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);
void RSScreenDrawCircleLines(RSScreen *screen, int centerX, int centerY, float radius, Color color);
void RSScreenDrawCircleLinesV(RSScreen *screen, Vector2 center, float radius, Color color);

void RSScreenDrawEllipse(RSScreen *screen, int centerX, int centerY, float radiusH, float radiusV, Color color);
void RSScreenDrawEllipseV(RSScreen *screen, Vector2 center, float radiusH, float radiusV, Color color);
void RSScreenDrawEllipseLines(RSScreen *screen, int centerX, int centerY, float radiusH, float radiusV, Color color);
void RSScreenDrawEllipseLinesV(RSScreen *screen, Vector2 center, float radiusH, float radiusV, Color color);

void RSScreenDrawRing(RSScreen *screen, Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);
void RSScreenDrawRingLines(RSScreen *screen, Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);

void RSScreenDrawRectangle(RSScreen *screen, int posX, int posY, int width, int height, Color color);
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
void RSScreenDrawSplineSegmentBezierQuadratic(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, float thick, Color color);
void RSScreenDrawSplineSegmentBezierCubic(RSScreen *screen, Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color);

// R_TEXTURES
RSImage RSScreenGenImageColor(RSScreen *screen, int width, int height, Color color);
RSTexture RSScreenLoadTextureFromImage(RSScreen *screen, RSImage image);
void RSScreenDrawTexture(RSScreen *screen, RSTexture texture, int posX, int posY, Color tint);

// R_TEXT
void RSScreenDrawFPS(RSScreen *screen, int posX, int posY);

void RSScreenDrawText(RSScreen *screen, int posX, int posY, int fontSize, Color color);

void RSScreenSetTextLineSpacing(RSScreen *screen, int spacing);

// R_MODELS
  
// R_AUDIO

#endif
