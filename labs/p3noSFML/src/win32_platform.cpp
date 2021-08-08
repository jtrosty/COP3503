#ifndef UNICODE
#define UNICODE
#endif

//#include "LoadConfig.h"
/*
#include <string>
#include <fstream>
#include <iostream>

*/
#include <windows.h>

struct {
    int width;
    int height;
    UINT32 *pixels;

    BITMAPINFO bitmap_info;
} typedef RenderBuffer;


void readPNGfile(std::string fileName) {
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnSize(HWND hwnd, UINT flag, int width, int height);

// CALLBACK ????? in the docs it says WINAPI
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    bool run = TRUE;

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
        WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
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


//askldjfklasdjkl this is where I want to laod the config

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

/*
        RECT rectWindow;
        GetClientRect(hwnd, &rectWindow);

        HDC deviceContext = GetDC(hwnd);
        int destWidth = rectWindow.right - rectWindow.left;
        int destHeight = rectWindow.bottom - rectWindow.top;
        StretchDIBits(deviceContext,
                        10, 10, 
                        destWidth, destHeight,
                        0, 0, 64, 64, // size of the happy face
            const VOID       *lpBits,
            const BITMAPINFO *lpbmi,
            UINT             iUsage,
            DWORD            rop
        );
*/
        // GAME LOOP AREA
        /*
        HDC deviceContext = GetDC(hwnd);
        StretchDIBits(deviceContext,
            int              xDest,
            int              yDest,
            int              DestWidth,
            int              DestHeight,
            int              xSrc,
            int              ySrc,
            int              SrcWidth,
            int              SrcHeight,
            const VOID       *lpBits,
            const BITMAPINFO *lpbmi,
            UINT             iUsage,
            DWORD            rop
        );
        */
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
            break;
        }
        case WM_CLOSE: {
            if (MessageBox(hwnd, L"Realy Quit", L"My Application", MB_OKCANCEL) == IDOK) {
                DestroyWindow(hwnd);
            }
            return 0;
        }
        case WM_PAINT: {
            RECT rect; 
            GetClientRect(hwnd, &rect);


            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // Perform all painting
            // DELETE LATER FOR DEBUGGING
            HBRUSH brush = CreateSolidBrush(0x000000FF);

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

void readPNGfile(string fileName) {
	string path = "../images";
	path += fileName + ".cfg";
	int size = 8;
	textureData = new unsigned char[size];
	fstream fileInput;
	fileInput.open(path, std::ios_base::in | std::ios_base::binary);
	for (int i = 0; i < size; i++) {
		fileInput.read((char*)textureData[i], sizeof(char));
	}
	for (int i = 0; i < size; i++) {
		cout << textureData[i] << " ";
	}
	cout << endl;
	fileInput.close();
}