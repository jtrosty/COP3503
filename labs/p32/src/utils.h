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
    int x1;
    int y0;
    int y1;
} typedef Rect;