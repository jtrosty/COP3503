#include "Draw.h"

void Draw::drawRectangle(int x0, int y0, int x1, int y1, UINT32 color, RenderBuffer& buffer) {
    x0 = clamp(0, x0, buffer.width);
    x1 = clamp(0, x1, buffer.width);
    y0 = clamp(0, y0, buffer.height);
    y1 = clamp(0, y1, buffer.height);

    for (int y = y0; y < y1; y++) {
        UINT32* pixel = buffer.pixels + x0 + (y * buffer.width);
        for (int x = x0; x < x1; x++) {
            *pixel++ = color;
        }
    }
}

int Draw::clamp(int min, int value, int max) {
    if (value > max) return max;
    if (value < min) return min;
    return value;
}