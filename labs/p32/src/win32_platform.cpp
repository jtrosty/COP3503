#ifndef UNICODE
#define UNICODE
#endif

// GLOBAL VARIABLE DELETE LATER
char run = 1;

#include "utils.h"

#include "FileLoader.h"
#include "Draw.h"

#include <windows.h>


RenderBuffer GlobalRenderBuffer = {0};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnSize(HWND hwnd, UINT flag, int width, int height);

// CALLBACK ????? in the docs it says WINAPI
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    // Register the window class.
    // TODO get config data here.  

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"Minesweeper";
    wc.style = CS_HREDRAW | CS_VREDRAW;
    
    RegisterClass(&wc);

    GlobalRenderBuffer.pixels = nullptr;
    int windowWidth = 720;
    int windowHeight = 720;
    Draw draw;
    GlobalRenderBuffer.pixels = (UINT32*)VirtualAlloc(0, sizeof(UINT32) * (windowWidth * windowHeight), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    //Create a window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        wc.lpszClassName,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    RECT rectWindow;
    GetClientRect(hwnd, &rectWindow);

    // FILE LOADING//////////////////////////////////////////////////
    FileLoader fileLoader;
    fileLoader.loadAllTextures();
    FileLoader::TextureData testPNG;
    //testPNG = FileLoader::getTextureChar("../images/test_1.png");
    testPNG = fileLoader.getTextureChar("../images/test_1.png");

    // The game loop
    MSG msg = { };
    while (run) {
        // Handle messages
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
        {
            switch (msg.message) {
                default: {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        }
        // Draw 
        //fileLoader.getTextureString("test_1")
        draw.drawRectangle(10, 40, 72, 400, 0xff00ff, GlobalRenderBuffer);
        draw.drawTexture(100, 100, testPNG, GlobalRenderBuffer);
        draw.drawTexture(170, 100, fileLoader.textures.at("face_win"), GlobalRenderBuffer);
        draw.drawTexture(200, 100, fileLoader.getTextureBMP("test_3"), GlobalRenderBuffer);

        HDC deviceContext = GetDC(hwnd);
        int destWidth = rectWindow.right - rectWindow.left;
        int destHeight = rectWindow.bottom - rectWindow.top;
        StretchDIBits(deviceContext,
                        0, 0, destHeight, destHeight, // Window size
                        0, 0, GlobalRenderBuffer.width, GlobalRenderBuffer.height, // size of buffer
                        GlobalRenderBuffer.pixels, &GlobalRenderBuffer.bitmap_info,
                        DIB_RGB_COLORS, SRCCOPY);

        // GAME LOOP AREA END
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY: {
            run = 0;
            PostQuitMessage(0);
            return 0;
            break;
        }
        case WM_CLOSE: {
            run = 0;
            DestroyWindow(hwnd);
            //if (MessageBox(hwnd, L"Realy Quit", L"My Application", MB_OKCANCEL) == IDOK) 
            return 0;
        }
        case WM_PAINT: {
            RECT rect; 
            GetClientRect(hwnd, &rect);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // Perform all painting
            // DELETE LATER FOR DEBUGGING
            HBRUSH brush = CreateSolidBrush(0x88888800);

            FillRect(hdc, &ps.rcPaint, brush);
            EndPaint(hwnd, &ps);

            break;
        }
        case WM_SIZE: {
                int width = LOWORD(lParam);  // Macro to get the low-order word.
                int height = HIWORD(lParam); // Macro to get the high-order word.

                RECT rectWindow;
                GetClientRect(hwnd, &rectWindow);
                int renderBufferWidth = rectWindow.right - rectWindow.left;
                int renderBufferHeight = rectWindow.right - rectWindow.left;
                if (GlobalRenderBuffer.pixels != nullptr) {
                    if (VirtualFree(GlobalRenderBuffer.pixels, 0, MEM_RELEASE)) {
                        // Success
                    }
                    else {
                        // Fail
                    }
                }
                GlobalRenderBuffer.pixels = (UINT32*)VirtualAlloc(0, sizeof(UINT32) * (renderBufferWidth * renderBufferHeight), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

                GlobalRenderBuffer.bitmap_info.bmiHeader.biSize = sizeof(GlobalRenderBuffer.bitmap_info.bmiHeader);
                GlobalRenderBuffer.bitmap_info.bmiHeader.biWidth = renderBufferWidth;
                GlobalRenderBuffer.bitmap_info.bmiHeader.biHeight = -renderBufferHeight;
                GlobalRenderBuffer.bitmap_info.bmiHeader.biPlanes = 1;
                GlobalRenderBuffer.bitmap_info.bmiHeader.biBitCount = 32;
                GlobalRenderBuffer.bitmap_info.bmiHeader.biCompression = BI_RGB;
                GlobalRenderBuffer.bitmap_info.bmiHeader.biSizeImage = 0;
                GlobalRenderBuffer.bitmap_info.bmiHeader.biXPelsPerMeter = 0;
                GlobalRenderBuffer.width = renderBufferWidth;
                GlobalRenderBuffer.height = renderBufferHeight;
                
                // Respond to the message:
                OnSize(hwnd, (UINT)wParam, width, height);
            }
            break;
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;

        }
    }
    return 0;
}

// **********************************************************************************
//                               HELPER FUNCTIONS
// **********************************************************************************

void OnSize(HWND hwnd, UINT flag, int width, int height) {
    // Handle resizing
}