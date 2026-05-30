#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "Commands.h"
#include "../RaySplitter/winray.h"

bool checkCmdAvailable() {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD bytesAvail = 0;

  // How many bytes have been written?
  if (!PeekNamedPipe(hStdin, NULL, 0, NULL, &bytesAvail, NULL)) {
    return false;
  }

  // No data given
  if (bytesAvail == 0) {
    return false;
  }

  // Buffer to load in new bytes
  char* buffer = (char*)malloc(bytesAvail);
  if (buffer == NULL) return false;

  DWORD bytesRead = 0;
  // Don't remove data, but still load in
  if (PeekNamedPipe(hStdin, buffer, bytesAvail, &bytesRead, NULL, NULL)) {
    // Scan for newline
    for (DWORD i = 0; i < bytesRead; i++) {
      if (buffer[i] == '\n' || buffer[i] == '\r') {
        // Completed line
        free(buffer);
        return true;
      }
    }
  }

  // Haven't reached newline yet
  free(buffer);
  return false;
}

void executeCmd(char *cmd) {
  // Split command into its args
  int argc;
  char **argv = splitString(cmd, ' ', &argc);

  // Determine what to do
  int code = argv[0][0]-'0';
  FuncWrapper fn = getFuncFromCode(code);
  if (!fn) {
    printf("Invalid function\n");
  } else {
    fn(argc-1, argv+1);
  }

  // Free args
  for (int i = 0; i < argc; ++i) {
    free(argv[i]);
  }
  free(argv);
}

void attemptCmdExecute() {
  // Is there even anything to execute?
  if (!checkCmdAvailable()) {
    return;
  }

  // Read the line in
  char line[256];
  fgets(line, sizeof(line), stdin);

  // Replace newline with end
  for (int i = 0; i < 256; ++i) if (line[i] == '\r' || line[i] == '\n') line[i] = 0;
  
  // Execute
  executeCmd(line);
}
