#include <stdlib.h>
#include <stdio.h>

#include "RSCommand.h"

void RSCommandFree(RSCommand *cmd) {
  for (int i = 0; i < cmd->argc; ++i) {
    free(cmd->argv[i]);
  }
  free(cmd->argv);
}
