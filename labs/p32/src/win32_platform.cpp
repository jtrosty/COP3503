#ifndef UNICODE
#define UNICODE
#endif

//#include "LoadConfig.h"
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

////// FILE LOADING ////////////////////////////////////////////////////////////////

struct FileReadInData {
    LPVOID data;
    DWORD size;
};

static FileReadInData readEntireFile(char* path) {
    FileReadInData result = {0};

    DWORD fileSizeHigh = 0;
    DWORD bytesRead = 0;

    HANDLE fileHandle = CreateFileA( path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    result.size = GetFileSize(fileHandle, &fileSizeHigh);
    
    // Allocate memory for the file to be read
    result.data = VirtualAlloc( NULL, result.size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (ReadFile( fileHandle, result.data, result.size, &bytesRead, NULL) && result.size == bytesRead) {
        // Success, We read the file.
    }  
    else {
        // Fail!!!
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////////

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

    // FILE LOADING TEST /////////////////////////////

    FileReadInData test3 = readEntireFile("../images/test_3.png");
    int x, y, n;
    //unsigned char* pixelDataTest = stbi_load(test3, &x, &y, &n, 0);
    unsigned char* pixelDataTest = stbi_load_from_memory((stbi_uc*)test3.data, test3.size, &x, &y, &n, 4);

//////////////////////////////////////////////////////////////////

// TEST DISPLAYING PNG PIXEL DATA
    int testPNGSize = 64;

    BITMAPINFO testBitMapInfo = {0};
    testBitMapInfo.bmiHeader.biSize = sizeof(testBitMapInfo.bmiHeader);
    testBitMapInfo.bmiHeader.biWidth = testPNGSize;
    testBitMapInfo.bmiHeader.biHeight = -testPNGSize;
    testBitMapInfo.bmiHeader.biPlanes = 1;
    testBitMapInfo.bmiHeader.biBitCount = 32;
    testBitMapInfo.bmiHeader.biCompression = BI_RGB;
    testBitMapInfo.bmiHeader.biSizeImage = 0;
    testBitMapInfo.bmiHeader.biXPelsPerMeter = 0;

// LETs map a test png data /////////////////////////////////////
    int sideOfSquare = 64;
    int size = sideOfSquare * sideOfSquare;
    int midPoint = 10 * 64;


    // 24 bit colors
    UINT32* testBitMap = new UINT32[size];
    for (int i = 0; i < midPoint; i++) {
        testBitMap[i] = 0xff4400;
    }
    for (int i = midPoint; i < size; i++) {
        testBitMap[i] = 0x444444;
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
    ////////////////////////////////////////////////////////////////////////////////

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

        StretchDIBits(deviceContext,
                        64, 64, testPNGSize, testPNGSize,
                        0, 0, sideOfSquare, sideOfSquare, // size of the happy face
                        pixelDataTest, &testBitMapInfo,
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