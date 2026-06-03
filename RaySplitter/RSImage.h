#ifndef _RS_IMAGE_H_
#define _RS_IMAGE_H_

// A code that is used on the other side to reference the image
typedef unsigned long long RSImageCode;

typedef struct {
  int width, height; // Some helpful information about the image
  RSImageCode ref; // Both the controller and sub know the image by this code
} RSImage;

#endif
