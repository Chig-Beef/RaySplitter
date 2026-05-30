#include <time.h>
#include <stdio.h>

#include "RaySplitter.h"

// TODO: Make this changeable
int RSFPS = 60;

// The user must register their screens to see updates
#define MAX_SCREENS 10
RSScreen *RSScreens[MAX_SCREENS];
int numScreens;
clock_t lastFrame = 0;

// Call at the end of a frame to push commands to sub screens
// Also waits the given amount of time (FPS)
errno_t RSFrame() {
  // Send all the commands
  for (int i = 0; i < numScreens; ++i) {
    if (RSScreenFrame(RSScreens[i])) {
      printf("Screen %i couldn't be flushed\n", i);
    }
  }

  // Wait for next frame
  clock_t curTime = clock();
  clock_t diff = curTime - lastFrame;

  lastFrame = curTime;

  // How long do we need to wait?
  clock_t expectDiff = (clock_t)((double)CLOCKS_PER_SEC / (double)RSFPS);

  // Really need a move on
  if (diff >= expectDiff) return 0;

  // We've got time to kill
  clock_t waitTime = expectDiff - diff;

  // Wait
  Sleep(waitTime*1000/CLOCKS_PER_SEC);

  return 0;
}

errno_t RSRegisterScreen(RSScreen *screen) {
  // Ensure we don't open too many screens
  if (numScreens == MAX_SCREENS) {
    printf("Too many screens in use at once\n");
    return 1;
  }

  RSScreens[numScreens++] = screen;

  return 0;
}
