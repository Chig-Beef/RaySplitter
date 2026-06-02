#ifndef _RS_IMAGE_H_
#define _RS_IMAGE_H_

#include "RSScreen.h"

// A code that is used on the other side to reference the image
typedef unsigned long long RSImageCode;

typedef struct {
  int width, height; // Some helpful information about the image
  RSScreen *owner; // The controller can only reference this image to this sub
  RSImageCode ref; // Both the controller and sub know the image by this code
} RSImage;

#endif
