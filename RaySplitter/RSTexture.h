#ifndef _RS_TEXTURE_H_
#define _RS_TEXTURE_H_

// A code that is used on the other side to reference the texture
typedef unsigned long long RSTextureCode;

typedef struct {
  int width, height; // Some helpful information about the texture
  RSTextureCode ref; // Both the controller and sub know the texture by this code
} RSTexture;

#endif
