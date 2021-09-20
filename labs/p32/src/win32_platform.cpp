#ifndef UNICODE
#define UNICODE
#endif

// GLOBAL VARIABLE DELETE LATER
char run = 1;

#include "utils.h"

#include "GameControl.h"
#include "GameLogic.h"
#include "Render.h"
#include "FileLoader.h"
#include "Draw.h"
#include "synchapi.h"

#include <windows.h>
#include <windowsx.h>
#include <WinUser.h>

// Global Variables!
static RenderBuffer GlobalRenderBuffer = {0};
static UserInput userInput;  

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnSize(HWND hwnd, UINT flag, int width, int height);

// CALLBACK ????? in the docs it says WINAPI
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    // Register the window class.
    WNDCLASS wc = { };
    // Required windows items
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"Minesweeper";
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);

    ////////////////////////////////////////////////////////////////////////////////////////
    // Create Objects to support the game
    GameControl gameControl;
    FileLoader fileLoader;
    Draw draw;
    GameLogic gameLogic;
    GlobalRenderBuffer.pixels = nullptr;

    // Startup the game
    gameControl.startUpGame(gameLogic, fileLoader);

    int windowsExtra = 30;
    int heightUI = 88;
    int windowWidth = (gameLogic.gameData.columns * gameLogic.gameData.lengthOfTile) + windowsExtra;
    int windowHeight = (gameLogic.gameData.rows * gameLogic.gameData.lengthOfTile) + heightUI + windowsExtra;
    GlobalRenderBuffer.pixels = (UINT32*)VirtualAlloc(0, sizeof(UINT32) * (windowWidth * windowHeight), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    Render render;

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

        // Game Loop!!! 
        gameControl.updateWindowAndUserInput(gameLogic, draw, fileLoader, render, GlobalRenderBuffer, userInput);

        // The followign code actually puts to the screen the Global Render buffer
        HDC deviceContext = GetDC(hwnd);
        int destWidth = rectWindow.right - rectWindow.left;
        int destHeight = rectWindow.bottom - rectWindow.top;
        StretchDIBits(deviceContext,
                        0, 0, destWidth, destHeight, // Window size
                        0, 0, GlobalRenderBuffer.width, GlobalRenderBuffer.height, // size of buffer
                        GlobalRenderBuffer.pixels, &GlobalRenderBuffer.bitmap_info,
                        DIB_RGB_COLORS, SRCCOPY);

        // GAME LOOP AREA END
        Sleep(15);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // MOUSE 
    POINT mousePt;
    HDC hdc;
    RECT rcCLient;
    POINT ptClientUL;
    POINT ptClientLR;


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
        case WM_LBUTTONDOWN: {
            // Capture mouse input

            userInput.point.x = GET_X_LPARAM(lParam);
            userInput.point.y = GET_Y_LPARAM(lParam);
            userInput.leftMouseClick = 1;
            userInput.isNewInput = 1;
            break;
        }
        case WM_LBUTTONUP: {
            break;
        }
        case WM_RBUTTONDOWN: {
            userInput.point.x = GET_X_LPARAM(lParam);
            userInput.point.y = GET_Y_LPARAM(lParam);
            userInput.rightMouseClick = 1;
            userInput.isNewInput = 1;
            break;
        }
        case WM_RBUTTONUP: {
            break;
        }
        case WM_KEYDOWN: {
            break;
        }
        case WM_SIZE: {
                int width = LOWORD(lParam);  // Macro to get the low-order word.
                int height = HIWORD(lParam); // Macro to get the high-order word.

                RECT rectWindow;
                GetClientRect(hwnd, &rectWindow);
                int renderBufferWidth = rectWindow.right - rectWindow.left;
                int renderBufferHeight = rectWindow.bottom - rectWindow.top;
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
