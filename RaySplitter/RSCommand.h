#ifndef _RS_COMMAND_H_
#define _RS_COMMAND_H_

typedef enum {
  FC_DRAW_RECTANGLE,
} FuncCode;

// A single instruction for the target machine
typedef struct {
  FuncCode func;
  int argc;
  char **argv;
} RSCommand;

void RSCommandFree(RSCommand *cmd);

char *RSCommandPackage(RSCommand *cmd);

#endif
