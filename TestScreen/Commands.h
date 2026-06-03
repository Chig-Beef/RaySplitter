#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include "../RaySplitter/winray.h"

// Converters into actual types
int argToInt(char *arg);
Color argToColor(char *arg);
float argToFloat(char *arg);
char *argToString(char *arg);
Vector2 argToVector2(char *arg);
Rectangle argToRectangle(char *arg);

void drawRectangleWrapper(int argc, char **argv);

typedef void (*FuncWrapper)(int argc, char **argv);

FuncWrapper getFuncFromCode(int code);

#endif
