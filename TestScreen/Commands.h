#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include "../RaySplitter/winray.h"
#include "../RaySplitter/RaySplitter.h"

typedef void (*FuncWrapper)(void **argv);

typedef struct {
  FuncCode code;
  FuncWrapper func;
  int argc;
  RSArgType *argt;
} FuncStruct;

typedef struct {
  RSImageCode ref;
  Image img;
} ImageRef;

typedef struct {
  RSTextureCode ref;
  Texture tex;
} TextureRef;

// Converters into actual types
int argToInt(char *arg);
Color argToColor(char *arg);
float argToFloat(char *arg);
char *argToString(char *arg);
Vector2 argToVector2(char *arg);
Rectangle argToRectangle(char *arg);
ImageRef argToImage(char *arg);
TextureRef argToTexture(char *arg);

FuncStruct getFuncFromCode(int code);

void ExecuteFunc(FuncStruct f, int argc, char **argv);

#endif
