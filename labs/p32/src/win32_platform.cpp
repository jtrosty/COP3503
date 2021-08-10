#ifndef UNICODE
#define UNICODE
#endif

//#include "LoadConfig.h"
#include <string>
#include <fstream>
#include <iostream>

#include <fstream>
#include <iostream>
//#include <string>
#include <windows.h>

struct {
    int width;
    int height;
    UINT32 *pixels;

    BITMAPINFO bitmap_info;
} typedef RenderBuffer;

// GLOBAL VARIABLE DELETE LATER
char run = 1;

void readPNGfile(std::string fileName); 
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnSize(HWND hwnd, UINT flag, int width, int height);

// CALLBACK ????? in the docs it says WINAPI
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    // Register the window class.
    //const wchar_t CLASS_NAME[]  = "Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"Minesweeper";
    wc.style = CS_HREDRAW | CS_VREDRAW;
    
    RegisterClass(&wc);

    //Create a window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        wc.lpszClassName,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 720, 720,
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

// LETs map a test bitmap data
    int sideOfSquare = 64;
    int size = sideOfSquare * sideOfSquare;


    // 24 bit colors
    UINT32* testBitMap = new UINT32[size];
    for (int i = 0; i < size; i++) {
        testBitMap[i] = 0xff4400;
    }
    BITMAPINFO bitMapInfo = {0};
    bitMapInfo.bmiHeader.biSize = sizeof(bitMapInfo.bmiHeader);
    bitMapInfo.bmiHeader.biWidth = sideOfSquare;
    bitMapInfo.bmiHeader.biHeight = -sideOfSquare;
    bitMapInfo.bmiHeader.biPlanes = 1;
    bitMapInfo.bmiHeader.biBitCount = 32;
    bitMapInfo.bmiHeader.biCompression = BI_RGB;
    bitMapInfo.bmiHeader.biSizeImage = 0;
    bitMapInfo.bmiHeader.biXPelsPerMeter = 0;


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


        HDC deviceContext = GetDC(hwnd);
        int destWidth = rectWindow.right - rectWindow.left;
        int destHeight = rectWindow.bottom - rectWindow.top;
        StretchDIBits(deviceContext,
                        0, 0, sideOfSquare, sideOfSquare,
                        0, 0, sideOfSquare, sideOfSquare, // size of the happy face
                        testBitMap, &bitMapInfo,
                        DIB_RGB_COLORS, SRCCOPY);

        // GAME LOOP AREA
    }
    delete[] testBitMap;
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
            //renderBufferWidth = rectWindow.right - rectWindow.left;


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

/*
void readPNGfile(std::string fileName) {
	std::string path = "../images";
	path += fileName + ".cfg";
	int size = 8;
	unsigned char* textureData = new unsigned char[size];
	std::fstream fileInput;
	fileInput.open(path, std::ios_base::in | std::ios_base::binary);
	for (int i = 0; i < size; i++) {
		fileInput.read((char*)textureData[i], sizeof(char));
	}
	for (int i = 0; i < size; i++) {
		std::cout << textureData[i] << " ";
	}
	std::cout << std::endl;
	fileInput.close();
}
	const char* path = "../images.png";
	int size = 8;
	unsigned char* textureData = new unsigned char[size];
	std::fstream fileInput;
	fileInput.open(path, std::ios_base::in | std::ios_base::binary);
	for (int i = 0; i < size; i++) {
		fileInput.read((char*)textureData[i], sizeof(char));
	}
	for (int i = 0; i < size; i++) {
		std::cout << textureData[i] << " ";
	}
	std::cout << std::endl;
	fileInput.close();
*/