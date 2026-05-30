#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "RSCommand.h"

void RSCommandFree(RSCommand *cmd) {
  for (int i = 0; i < cmd->argc; ++i) {
    free(cmd->argv[i]);
  }
  free(cmd->argv);
}

char *RSCommandPackage(RSCommand *cmd) {
  // A byte for the func
  int totalSize = 1;

  // Add bytes for the spaces
  totalSize += cmd->argc;

  // Add length of each arg
  for (int i = 0; i < cmd->argc; ++i) {
    totalSize += strlen(cmd->argv[i]);
  }

  // Allocate buffer
  char *out = malloc(totalSize+2);
  char *p = out;
  
  // Place in func
  *p = cmd->func+'0';
  ++p;

  // Place in args
  for (int i = 0; i < cmd->argc; ++i) {
    // Space at front
    *p = ' ';
    ++p;

    // Arg
    char *s = cmd->argv[i];
    while (*s) {
      *p = *s;
      ++s;
      ++p;
    }
  }

  // Close
  out[totalSize] = '\n';
  out[totalSize+1] = 0;
  return out;
}
