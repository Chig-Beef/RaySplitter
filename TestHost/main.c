#include <corecrt.h>
#include <stdio.h>

#include "../RaySplitter/RaySplitter.h"

int main() {
  printf("Starting test\n");

  RSScreen screenA;
  RSScreen screenB;

  // Start both screens
  RSScreenInit(&screenA);
  RSScreenInit(&screenB);

  // Open both screens
  RSScreenOpen(&screenA);
  RSScreenOpen(&screenB);

  // Start logic loop
  bool running = true;
  while (running) {
    // ... Do stuff ...
    running = false;
  }

  // Close both screens
  RSScreenCloseWait(&screenA);
  RSScreenCloseWait(&screenB);

  return 0;
}
