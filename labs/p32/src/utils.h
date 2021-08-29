#pragma once
#include <Windows.h>

struct {
    int width;
    int height;
    UINT32 *pixels;

    BITMAPINFO bitmap_info;
} typedef RenderBuffer;

