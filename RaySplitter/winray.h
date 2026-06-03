#ifndef _RS_WIN_RAY_H_
#define _RS_WIN_RAY_H_

#define Rectangle winRectangle
#define CloseWindow winCloseWindow
#define ShowCursor winShowCursor
#define LoadImageA winLoadImageA
#define DrawTextA winDrawTextA
#define DrawText winDrawText
#define DrawTextExA winDrawTextExA
#define PlaySoundA winPlaySoundA

#include <windows.h>

#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef LoadImageA
#undef DrawTextA
#undef DrawText
#undef DrawTextExA
#undef PlaySoundA

#include <raylib.h>

#endif
