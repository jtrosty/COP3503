#pragma once
#include <Windows.h>

struct {
    int width;
    int height;
    UINT32 *pixels;

    BITMAPINFO bitmap_info;
} typedef RenderBuffer;

struct {
    int x0;
    int y0;
    int width;
    int heigth;
} typedef Rect;

struct UserInput {
    POINT point;
    char leftMouseClick = 0;
    char rightMouseClick = 0;
    char isNewInput = 0;
};