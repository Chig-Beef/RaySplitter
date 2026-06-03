#ifndef _RS_SCREEN_COMMANDS_H_
#define _RS_SCREEN_COMMANDS_H_

#include "winray.h"
#include "RSScreen.h"

typedef const char * cstring;
typedef char * string;

typedef struct {
  int argc;
  RSArgType *argt;
} RSFuncMetaData;

RSFuncMetaData RSGetFuncMetadata(FuncCode func);

void RSDeployCommand(RSScreen *screen, FuncCode func, void **argv);

// R_CORE
void RSScreenSetWindowTitle(RSScreen *screen, cstring title);
void RSScreenSetWindowPosition(RSScreen *screen, int x, int y);
void RSScreenSetWindowSize(RSScreen *screen, int width, int height);

void RSScreenClearBackground(RSScreen *screen, Color color);

void RSScreenTakeScreenShot(RSScreen *screen, cstring fileName);

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
RSImage RSScreenLoadImage(RSScreen *screen, cstring fileName);
RSImage RSScreenLoadImageRaw(RSScreen *screen, cstring fileName, int width, int height, int format, int headerSize);
RSImage RSScreenLoadImageFromTexture(RSScreen *screen, RSTexture texture);
RSImage RSScreenLoadImageFromScreen(RSScreen *screen);
void RSScreenUnloadImage(RSScreen *screen, RSImage image);

RSImage RSScreenGenImageColor(RSScreen *screen, int width, int height, Color color);
RSImage RSScreenGenImageGradientLinear(RSScreen *screen, int width, int height, int direction, Color start, Color end);
RSImage RSScreenGenImageGradientRadial(RSScreen *screen, int width, int height, float density, Color inner, Color outer);
RSImage RSScreenGenImageGradientSquare(RSScreen *screen, int width, int height, float density, Color inner, Color outer);
RSImage RSScreenGenImageChecked(RSScreen *screen, int width, int height, int checksX, int checksY, Color col1, Color col2);
RSImage RSScreenGenImageWhiteNoise(RSScreen *screen, int width, int height, float factor);
RSImage RSScreenGenImagePerlinNoise(RSScreen *screen, int width, int height, int offsetX, int offsetY, float scale);
RSImage RSScreenGenImageCellular(RSScreen *screen, int width, int height, int tileSize);
RSImage RSScreenGenImageText(RSScreen *screen, int width, int height, const char *text);

RSImage RSScreenImageCopy(RSScreen *screen, RSImage image);
RSImage RSScreenImageFromImage(RSScreen *screen, RSImage image, Rectangle rec);
RSImage RSScreenImageFromChannel(RSScreen *screen, RSImage image, int selectedChannel);
RSImage RSScreenImageText(RSScreen *screen, cstring text, int fontsize, Color color);
void RSScreenImageFormat(RSScreen *screen, RSImage *image, int newFormat);
void RSScreenImageToPot(RSScreen *screen, RSImage *image, Color fill);
void RSScreenImageCrop(RSScreen *screen, RSImage *image, Rectangle crop);
void RSScreenImageAlphaCrop(RSScreen *screen, RSImage *image, float threshold);
void RSScreenImageAlphaClear(RSScreen *screen, RSImage *image, Color color, float threshold);
void RSScreenImageAlphaMask(RSScreen *screen, RSImage *image, RSImage alphaMask);
void RSScreenImageAlphaPremultiply(RSScreen *screen, RSImage *image);
void RSScreenImageBlurGaussian(RSScreen *screen, RSImage *image, int blurSize);
void RSScreenImageResize(RSScreen *screen, RSImage *image, int newWidth, int newHeight);
void RSScreenImageResizeNN(RSScreen *screen, RSImage *image, int newWidth, int newHeight);
void RSScreenImageResizeCanvas(RSScreen *screen, RSImage *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill);
void RSScreenImageMipmaps(RSScreen *screen, RSImage *image);
void RSScreenImageDither(RSScreen *screen, RSImage *image, int rBpp, int gBpp, int bBpp, int aBpp);
void RSScreenImageFlipVertical(RSScreen *screen, RSImage *image);
void RSScreenImageFlipHorizontal(RSScreen *screen, RSImage *image);
void RSScreenImageRotate(RSScreen *screen, RSImage *image, int degrees);
void RSScreenImageRotateCW(RSScreen *screen, RSImage *image);
void RSScreenImageRotateCCW(RSScreen *screen, RSImage *image);
void RSScreenImageColorTint(RSScreen *screen, RSImage *image, Color color);
void RSScreenImageColorInvert(RSScreen *screen, RSImage *image);
void RSScreenImageColorGrayscale(RSScreen *screen, RSImage *image);
void RSScreenImageColorContrast(RSScreen *screen, RSImage *image, float contrast);
void RSScreenImageColorBrightness(RSScreen *screen, RSImage *image, int brightness);
void RSScreenImageColorReplace(RSScreen *screen, RSImage *image, Color color, Color replace);

void RSScreenImageClearBackground(RSScreen *screen, RSImage *dst, Color color);
void RSScreenImageDrawPixel(RSScreen *screen, RSImage *dst, int posX, int posY, Color color);
void RSScreenImageDrawPixelV(RSScreen *screen, RSImage *dst, Vector2 position, Color color);
void RSScreenImageDrawLine(RSScreen *screen, RSImage *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color);
void RSScreenImageDrawLineV(RSScreen *screen, RSImage *dst, Vector2 start, Vector2 end, Color color);
void RSScreenImageDrawLineEx(RSScreen *screen, RSImage *dst, Vector2 start, Vector2 end, int thick, Color color);
void RSScreenImageDrawCircle(RSScreen *screen, RSImage *dst, int centerX, int centerY, int radius, Color color);
void RSScreenImageDrawCircleV(RSScreen *screen, RSImage *dst, Vector2 center, int radius, Color color);
void RSScreenImageDrawCircleLines(RSScreen *screen, RSImage *dst, int centerX, int centerY, int radius, Color color);
void RSScreenImageDrawCircleLinesV(RSScreen *screen, RSImage *dst, Vector2 center, int radius, Color color);
void RSScreenImageDrawRectangle(RSScreen *screen, RSImage *dst, int posX, int posY, int width, int height, Color color);
void RSScreenImageDrawRectangleV(RSScreen *screen, RSImage *dst, Vector2 position, Vector2 size, Color color);
void RSScreenImageDrawRectangleRec(RSScreen *screen, RSImage *dst, Rectangle rec, Color color);
void RSScreenImageDrawRectangleLines(RSScreen *screen, RSImage *dst, Rectangle rec, int thick, Color color);
void RSScreenImageDrawTriangle(RSScreen *screen, RSImage *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color);
void RSScreenImageDrawTriangleEx(RSScreen *screen, RSImage *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3);
void RSScreenImageDrawTriangleLines(RSScreen *screen, RSImage *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color);
void RSScreenImageDraw(RSScreen *screen, RSImage *dst, RSImage src, Rectangle srcRec, Rectangle dstRec, Color tint);
void RSScreenImageDrawText(RSScreen *screen, RSImage *dst, const char *text, int posX, int posY, int fontSize, Color color);

RSTexture RSScreenLoadTexture(RSScreen *screen, cstring fileName);
RSTexture RSScreenLoadTextureFromImage(RSScreen *screen, RSImage image);
void RSScreenUnloadTexture(RSScreen *screen, RSTexture texture);

void RSScreenGenTextureMipmaps(RSScreen *screen, RSTexture *texture);
void RSScreenSetTextureFilter(RSScreen *screen, RSTexture texture, int filter);
void RSScreenSetTextureWrap(RSScreen *screen, RSTexture texture, int wrap);

void RSScreenDrawTexture(RSScreen *screen, RSTexture texture, int posX, int posY, Color tint);
void RSScreenDrawTextureV(RSScreen *screen, RSTexture texture, Vector2 position, Color tint);
void RSScreenDrawTextureEx(RSScreen *screen, RSTexture texture, Vector2 position, float rotation, float scale, Color tint);
void RSScreenDrawTextureRec(RSScreen *screen, RSTexture texture, Rectangle source, Vector2 position, Color tint);
void RSScreenDrawTexturePro(RSScreen *screen, RSTexture texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);


// R_TEXT
void RSScreenDrawFPS(RSScreen *screen, int posX, int posY);

void RSScreenDrawText(RSScreen *screen, cstring text, int posX, int posY, int fontSize, Color color);

void RSScreenSetTextLineSpacing(RSScreen *screen, int spacing);

// R_MODELS
  
// R_AUDIO

#endif
