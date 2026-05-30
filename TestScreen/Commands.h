#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include "../RaySplitter/winray.h"

int argToInt(char *arg);

Color argToColor(char *arg);

void drawRectangleWrapper(int argc, char **argv);

typedef void (*FuncWrapper)(int argc, char **argv);

FuncWrapper getFuncFromCode(int code);

#endif
