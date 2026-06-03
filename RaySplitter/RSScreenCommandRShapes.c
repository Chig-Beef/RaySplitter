#include "RSScreenCommands.h"

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

