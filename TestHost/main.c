#include <corecrt.h>
#include <stdio.h>

#include "../RaySplitter/RaySplitter.h"

int main() {
  printf("Starting test\n");

  RSScreen screenA;
  RSScreen screenB;

  // Start both screens
  printf("Init screens\n");
  RSScreenInit(&screenA);
  RSScreenInit(&screenB);

  // Open both screens
  printf("Open screens\n");
  RSScreenOpen(&screenA);
  RSScreenOpen(&screenB);

  printf("Register screens\n");
  RSRegisterScreen(&screenA);
  RSRegisterScreen(&screenB);

  // Start logic loop
  printf("Starting loop\n");
  bool running = true;
  int frameCount = 0;
  while (running) {
    RSScreenDrawRectangle(&screenA, 60, 10, 50, 50, GREEN);
    RSScreenDrawRectangle(&screenB, 60, 10, 50, 50, YELLOW);

    RSFrame();
    frameCount++;
    if (frameCount == 300) { // 5 seconds
      running = false;
    }
  }

  // Close both screens
  printf("Closing\n");
  RSScreenCloseForce(&screenA);
  RSScreenCloseForce(&screenB);

  return 0;
}
