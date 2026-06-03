#include "RSScreenCommands.h"

RSImage RSScreenLoadImage(RSScreen *screen, cstring fileName) {
  const FuncCode func = FC_LOAD_IMAGE;
  void *argv[1] = {&fileName};
  RSDeployCommand(screen, func, argv);

  // TODO: Real size
  return RSScreenNewImage(screen, 10, 10);
}

RSImage RSScreenLoadImageRaw(RSScreen *screen, cstring fileName, int width, int height, int format, int headerSize) {
  const FuncCode func = FC_LOAD_IMAGE_RAW;
  void *argv[5] = {&fileName, &width, &height, &format, &headerSize};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}

RSImage RSScreenLoadImageFromTexture(RSScreen *screen, RSTexture texture) {
  const FuncCode func = FC_LOAD_IMAGE_FROM_TEXTURE;
  void *argv[1] = {&texture};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, texture.width, texture.height);
}

RSImage RSScreenLoadImageFromScreen(RSScreen *screen) {
  const FuncCode func = FC_LOAD_IMAGE_FROM_SCREEN;
  RSDeployCommand(screen, func, NULL);

  // TODO: Real size
  return RSScreenNewImage(screen, 10, 10);
}

void RSScreenUnloadImage(RSScreen *screen, RSImage image) {
  const FuncCode func = FC_UNLOAD_IMAGE;
  void *argv[1] = {&image};
  RSDeployCommand(screen, func, argv);
}


RSImage RSScreenGenImageColor(RSScreen *screen, int width, int height, Color color) {
  const FuncCode func = FC_GEN_IMAGE_COLOR;
  void *argv[3] = {&width, &height, &color};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}

RSImage RSScreenGenImageGradientLinear(RSScreen *screen, int width, int height, int direction, Color start, Color end) {
  const FuncCode func = FC_GEN_IMAGE_GRADIENT_LINEAR;
  void *argv[5] = {&width, &height, &direction, &start, &end};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}

RSImage RSScreenGenImageGradientRadial(RSScreen *screen, int width, int height, float density, Color inner, Color outer) {
  const FuncCode func = FC_GEN_IMAGE_GRADIENT_RADIAL;
  void *argv[5] = {&width, &height, &density, &inner, &outer};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}

RSImage RSScreenGenImageGradientSquare(RSScreen *screen, int width, int height, float density, Color inner, Color outer) {
  const FuncCode func = FC_GEN_IMAGE_GRADIENT_RADIAL;
  void *argv[5] = {&width, &height, &density, &inner, &outer};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}

RSImage RSScreenGenImageChecked(RSScreen *screen, int width, int height, int checksX, int checksY, Color col1, Color col2) {
  const FuncCode func = FC_GEN_IMAGE_CHECKED;
  void *argv[6] = {&width, &height, &checksX, &checksY, &col1, &col2};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}

RSImage RSScreenGenImageWhiteNoise(RSScreen *screen, int width, int height, float factor) {
  const FuncCode func = FC_GEN_IMAGE_WHITE_NOISE;
  void *argv[3] = {&width, &height, &factor};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}

RSImage RSScreenGenImagePerlinNoise(RSScreen *screen, int width, int height, int offsetX, int offsetY, float scale) {
  const FuncCode func = FC_GEN_IMAGE_PERLIN_NOISE;
  void *argv[5] = {&width, &height, &offsetX, &offsetY, &scale};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}

RSImage RSScreenGenImageCellular(RSScreen *screen, int width, int height, int tileSize) {
  const FuncCode func = FC_GEN_IMAGE_CELLULAR;
  void *argv[4] = {&width, &height, &tileSize};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}

RSImage RSScreenGenImageText(RSScreen *screen, int width, int height, cstring text) {
  const FuncCode func = FC_GEN_IMAGE_TEXT;
  void *argv[3] = {&width, &height, &text};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, width, height);
}


RSImage RSScreenImageCopy(RSScreen *screen, RSImage image) {
  const FuncCode func = FC_IMAGE_COPY;
  void *argv[1] = {&image};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, image.width, image.height);
}

RSImage RSScreenImageFromImage(RSScreen *screen, RSImage image, Rectangle rec) {
  const FuncCode func = FC_IMAGE_FROM_IMAGE;
  void *argv[2] = {&image, &rec};
  RSDeployCommand(screen, func, argv);

  // TODO: Real size
  return RSScreenNewImage(screen, 10, 10);
}

RSImage RSScreenImageFromChannel(RSScreen *screen, RSImage image, int selectedChannel) {
  const FuncCode func = FC_IMAGE_FROM_CHANNEL;
  void *argv[2] = {&image, &selectedChannel};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewImage(screen, image.width, image.height);
}

RSImage RSScreenImageText(RSScreen *screen, cstring text, int fontsize, Color color) {
  const FuncCode func = FC_IMAGE_TEXT;
  void *argv[3] = {&text, &fontsize, &color};
  RSDeployCommand(screen, func, argv);

  // TODO: Real size
  return RSScreenNewImage(screen, 10, 10);
}

void RSScreenImageFormat(RSScreen *screen, RSImage *image, int newFormat) {
  const FuncCode func = FC_IMAGE_FORMAT;
  void *argv[2] = {&*image, &newFormat};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageToPot(RSScreen *screen, RSImage *image, Color fill) {
  const FuncCode func = FC_IMAGE_TO_POT;
  void *argv[2] = {&*image, &fill};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageCrop(RSScreen *screen, RSImage *image, Rectangle crop) {
  const FuncCode func = FC_IMAGE_CROP;
  void *argv[2] = {&*image, &crop};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageAlphaCrop(RSScreen *screen, RSImage *image, float threshold) {
  const FuncCode func = FC_IMAGE_ALPHA_CROP;
  void *argv[2] = {&*image, &threshold};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageAlphaClear(RSScreen *screen, RSImage *image, Color color, float threshold) {
  const FuncCode func = FC_IMAGE_ALPHA_CLEAR;
  void *argv[3] = {&*image, &color, &threshold};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageAlphaMask(RSScreen *screen, RSImage *image, RSImage alphaMask) {
  const FuncCode func = FC_IMAGE_ALPHA_MASK;
  void *argv[2] = {&*image, &alphaMask};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageAlphaPremultiply(RSScreen *screen, RSImage *image) {
  const FuncCode func = FC_IMAGE_ALPHA_PREMULTIPLY;
  void *argv[1] = {&*image};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageBlurGaussian(RSScreen *screen, RSImage *image, int blurSize) {
  const FuncCode func = FC_IMAGE_BLUR_GAUSSIAN;
  void *argv[2] = {&*image, &blurSize};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageResize(RSScreen *screen, RSImage *image, int newWidth, int newHeight) {
  const FuncCode func = FC_IMAGE_RESIZE;
  void *argv[3] = {&*image, &newWidth, &newHeight};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageResizeNN(RSScreen *screen, RSImage *image, int newWidth, int newHeight) {
  const FuncCode func = FC_IMAGE_RESIZE_NN;
  void *argv[3] = {&*image, &newWidth, &newHeight};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageResizeCanvas(RSScreen *screen, RSImage *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill) {
  const FuncCode func = FC_IMAGE_RESIZE_CANVAS;
  void *argv[6] = {&*image, &newWidth, &newHeight, &offsetX, &offsetY, &fill};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageMipmaps(RSScreen *screen, RSImage *image) {
  const FuncCode func = FC_IMAGE_MIPMAPS;
  void *argv[1] = {&*image};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDither(RSScreen *screen, RSImage *image, int rBpp, int gBpp, int bBpp, int aBpp) {
  const FuncCode func = FC_IMAGE_DITHER;
  void *argv[5] = {&*image, &rBpp, &gBpp, &bBpp, &aBpp};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageFlipVertical(RSScreen *screen, RSImage *image) {
  const FuncCode func = FC_IMAGE_FLIP_VERTICAL;
  void *argv[1] = {&*image};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageFlipHorizontal(RSScreen *screen, RSImage *image) {
  const FuncCode func = FC_IMAGE_FLIP_HORIZONTAL;
  void *argv[1] = {&*image};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageRotate(RSScreen *screen, RSImage *image, int degrees) {
  const FuncCode func = FC_IMAGE_ROTATE;
  void *argv[2] = {&*image, &degrees};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageRotateCW(RSScreen *screen, RSImage *image) {
  const FuncCode func = FC_IMAGE_ROTATE_CW;
  void *argv[1] = {&*image};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageRotateCCW(RSScreen *screen, RSImage *image) {
  const FuncCode func = FC_IMAGE_ROTATE_CCW;
  void *argv[1] = {&*image};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageColorTint(RSScreen *screen, RSImage *image, Color color) {
  const FuncCode func = FC_IMAGE_COLOR_TINT;
  void *argv[2] = {&*image, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageColorInvert(RSScreen *screen, RSImage *image) {
  const FuncCode func = FC_IMAGE_COLOR_INVERT;
  void *argv[1] = {&*image};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageColorGrayscale(RSScreen *screen, RSImage *image) {
  const FuncCode func = FC_IMAGE_COLOR_GRAYSCALE;
  void *argv[1] = {&*image};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageColorContrast(RSScreen *screen, RSImage *image, float contrast) {
  const FuncCode func = FC_IMAGE_COLOR_CONTRAST;
  void *argv[2] = {&*image, &contrast};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageColorBrightness(RSScreen *screen, RSImage *image, int brightness) {
  const FuncCode func = FC_IMAGE_COLOR_BRIGHTNESS;
  void *argv[2] = {&*image, &brightness};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageColorReplace(RSScreen *screen, RSImage *image, Color color, Color replace) {
  const FuncCode func = FC_IMAGE_COLOR_REPLACE;
  void *argv[3] = {&*image, &color, &replace};
  RSDeployCommand(screen, func, argv);
}


void RSScreenImageClearBackground(RSScreen *screen, RSImage *dst, Color color) {
  const FuncCode func = FC_IMAGE_CLEAR_BACKGROUND;
  void *argv[2] = {&*dst, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawPixel(RSScreen *screen, RSImage *dst, int posX, int posY, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_PIXEL;
  void *argv[4] = {&*dst, &posX, &posY, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawPixelV(RSScreen *screen, RSImage *dst, Vector2 position, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_PIXEL_V;
  void *argv[3] = {&*dst, &position, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawLine(RSScreen *screen, RSImage *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_LINE;
  void *argv[6] = {&*dst, &startPosX, &startPosY, &endPosX, &endPosY, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawLineV(RSScreen *screen, RSImage *dst, Vector2 start, Vector2 end, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_LINE_V;
  void *argv[4] = {&*dst, &start, &end, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawLineEx(RSScreen *screen, RSImage *dst, Vector2 start, Vector2 end, int thick, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_LINE_EX;
  void *argv[5] = {&*dst, &start, &end, &thick, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawCircle(RSScreen *screen, RSImage *dst, int centerX, int centerY, int radius, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_CIRCLE;
  void *argv[5] = {&*dst, &centerX, &centerY, &radius, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawCircleV(RSScreen *screen, RSImage *dst, Vector2 center, int radius, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_CIRCLE_V;
  void *argv[4] = {&*dst, &center, &radius, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawCircleLines(RSScreen *screen, RSImage *dst, int centerX, int centerY, int radius, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_CIRCLE_LINES;
  void *argv[5] = {&*dst, &centerX, &centerY, &radius, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawCircleLinesV(RSScreen *screen, RSImage *dst, Vector2 center, int radius, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_CIRCLE_LINES_V;
  void *argv[4] = {&*dst, &center, &radius, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawRectangle(RSScreen *screen, RSImage *dst, int posX, int posY, int width, int height, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_RECTANGLE;
  void *argv[6] = {&*dst, &posX, &posY, &width, &height, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawRectangleV(RSScreen *screen, RSImage *dst, Vector2 position, Vector2 size, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_RECTANGLE_V;
  void *argv[4] = {&*dst, &position, &size, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawRectangleRec(RSScreen *screen, RSImage *dst, Rectangle rec, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_RECTANGLE_REC;
  void *argv[3] = {&*dst, &rec, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawRectangleLines(RSScreen *screen, RSImage *dst, Rectangle rec, int thick, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_RECTANGLE_LINES;
  void *argv[4] = {&*dst, &rec, &thick, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawTriangle(RSScreen *screen, RSImage *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_TRIANGLE;
  void *argv[5] = {&*dst, &v1, &v2, &v3, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawTriangleEx(RSScreen *screen, RSImage *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3) {
  const FuncCode func = FC_IMAGE_DRAW_TRIANGLE_EX;
  void *argv[7] = {&*dst, &v1, &v2, &v3, &c1, &c2, &c3};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawTriangleLines(RSScreen *screen, RSImage *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_TRIANGLE_LINES;
  void *argv[5] = {&*dst, &v1, &v2, &v3, &color};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDraw(RSScreen *screen, RSImage *dst, RSImage src, Rectangle srcRec, Rectangle dstRec, Color tint) {
  const FuncCode func = FC_IMAGE_DRAW;
  void *argv[5] = {&*dst, &src, &srcRec, &dstRec, &tint};
  RSDeployCommand(screen, func, argv);
}

void RSScreenImageDrawText(RSScreen *screen, RSImage *dst, cstring text, int posX, int posY, int fontSize, Color color) {
  const FuncCode func = FC_IMAGE_DRAW_TEXT;
  void *argv[6] = {&*dst, &text, &posX, &posY, &fontSize, &color};
  RSDeployCommand(screen, func, argv);
}


RSTexture RSScreenLoadTexture(RSScreen *screen, cstring fileName) {
  const FuncCode func = FC_LOAD_TEXTURE;
  void *argv[1] = {&fileName};
  RSDeployCommand(screen, func, argv);

  // TODO: Real size
  return RSScreenNewTexture(screen, 10, 10);
}

RSTexture RSScreenLoadTextureFromImage(RSScreen *screen, RSImage image) {
  const FuncCode func = FC_LOAD_TEXTURE_FROM_IMAGE;
  void *argv[1] = {&image};
  RSDeployCommand(screen, func, argv);

  return RSScreenNewTexture(screen, image.width, image.height);
}

void RSScreenUnloadTexture(RSScreen *screen, RSTexture texture) {
  const FuncCode func = FC_UNLOAD_TEXTURE;
  void *argv[1] = {&texture};
  RSDeployCommand(screen, func, argv);
}


void RSScreenGenTextureMipmaps(RSScreen *screen, RSTexture *texture) {
  const FuncCode func = FC_GEN_TEXTURE_MIPMAPS;
  void *argv[1] = {&*texture};
  RSDeployCommand(screen, func, argv);
}

void RSScreenSetTextureFilter(RSScreen *screen, RSTexture texture, int filter) {
  const FuncCode func = FC_SET_TEXTURE_FILTER;
  void *argv[2] = {&texture, &filter};
  RSDeployCommand(screen, func, argv);
}

void RSScreenSetTextureWrap(RSScreen *screen, RSTexture texture, int wrap) {
  const FuncCode func = FC_SET_TEXTURE_WRAP;
  void *argv[2] = {&texture, &wrap};
  RSDeployCommand(screen, func, argv);
}


void RSScreenDrawTexture(RSScreen *screen, RSTexture texture, int posX, int posY, Color tint) {
  const FuncCode func = FC_DRAW_TEXTURE;
  void *argv[4] = {&texture, &posX, &posY, &tint};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawTextureV(RSScreen *screen, RSTexture texture, Vector2 position, Color tint) {
  const FuncCode func = FC_DRAW_TEXTURE_V;
  void *argv[3] = {&texture, &position, &tint};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawTextureEx(RSScreen *screen, RSTexture texture, Vector2 position, float rotation, float scale, Color tint) {
  const FuncCode func = FC_DRAW_TEXTURE_EX;
  void *argv[5] = {&texture, &position, &rotation, &scale, &tint};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawTextureRec(RSScreen *screen, RSTexture texture, Rectangle source, Vector2 position, Color tint) {
  const FuncCode func = FC_DRAW_TEXTURE_REC;
  void *argv[4] = {&texture, &source, &position, &tint};
  RSDeployCommand(screen, func, argv);
}

void RSScreenDrawTexturePro(RSScreen *screen, RSTexture texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint) {
  const FuncCode func = FC_DRAW_TEXTURE_PRO;
  void *argv[6] = {&texture, &source, &dest, &origin, &rotation, &tint};
  RSDeployCommand(screen, func, argv);
}
