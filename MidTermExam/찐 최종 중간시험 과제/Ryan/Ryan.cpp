#include <Windows.h>
#include "yuhanCG.h"

// 도형 변수
bool cubeMoving = false;
bool movecube = false;
bool isBoxOn = false;
int Blink = 0;
int drow = 0;

HWND hWnd;
HWND hButton1, hButton2, hButton3, hButton4, hButton5;

bool Mainbox = true;
bool drawbox = true;

//마우스 변수
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT newstartPoint = { 0 };
POINT newendPoint = { 0 };
POINT cubeMovePoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;


void Draw(HWND hWnd, HDC hdc) {
    
    if (Mainbox) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200));
        SelectObject(hdc, hBrush);
        Rectangle(hdc, 8, 8, 792, 472);
        DeleteObject(hBrush);
    }

    if (drawbox) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, hBrush);
        Rectangle(hdc, 16, 104, 784, 464);
        DeleteObject(hBrush);
    }

    if (drow != 0 && startPoint.x > 16 && startPoint.y > 104 && startPoint.x < 784 && startPoint.y < 464) {
        if (endPoint.x > 16 && endPoint.y > 104 && endPoint.x < 784 && endPoint.y < 464) {
            switch (drow) {
            case 1:
            {
                DrawBox(hdc, isMouseRButtonPressed, startPoint, endPoint, newstartPoint, newendPoint);

                break;
            }


            case 2:
            {
                DrawCircle(hdc, isMouseLButtonPressed, isMouseRButtonPressed, startPoint, endPoint, newendPoint, newstartPoint);

                break;
            }

            case 4:
            {
                DrawRyan(hdc, startPoint, endPoint);

                break;
            }
            case 5:
            {
                DrawCube(hdc,startPoint, endPoint);

                break;
            }
            }
        }
    }


}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {

    case WM_KEYDOWN:
    {
        if (wParam == VK_SPACE) {
            Blink = 1;
        }
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

    case WM_KEYUP:
    {
        Blink = 0;

        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

    case WM_CREATE:
        SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 240, 200)));
        break;

    case WM_LBUTTONDOWN:
    {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        isMouseRButtonPressed = 0;
        isMouseLButtonPressed = 1;
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            InvalidateRect(hwnd, NULL, TRUE);
        }
        if (isMouseRButtonPressed)
        {
            newendPoint.x = LOWORD(lParam);
            newendPoint.y = HIWORD(lParam);

            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    break;

    case WM_LBUTTONUP:
    {
        endPoint.x = LOWORD(lParam);
        endPoint.y = HIWORD(lParam);
        isMouseLButtonPressed = 0;

        isBoxOn = true;
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

    case WM_RBUTTONDOWN:
    {
        newstartPoint.x = LOWORD(lParam);
        newstartPoint.y = HIWORD(lParam);
        isMouseRButtonPressed = 1;
    }
    break;

    case WM_RBUTTONUP:
    {
        newendPoint.x = LOWORD(lParam);
        newendPoint.y = HIWORD(lParam);
        isMouseRButtonPressed = 2;

        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;


    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;

            drow = 1;

            EnableWindow(hButton3, TRUE);
            InvalidateRect(hwnd, NULL, TRUE);

        }
        else if (LOWORD(wParam) == 2) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;
            newendPoint.x = 0;
            newstartPoint.x = 0;

            drow = 2;

            EnableWindow(hButton3, TRUE);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 3) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;
            EnableWindow(hButton3, FALSE);
            MessageBox(hWnd, L"보노보노를 그립니다", L"BONOBONO", MB_OK);
            drow = 3;

            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 4) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;

            drow = 4;

            EnableWindow(hButton3, TRUE);
            InvalidateRect(hwnd, NULL, TRUE);

        }
        else if (LOWORD(wParam) == 5) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;

            drow = 5;

            isBoxOn = false;
            EnableWindow(hButton3, TRUE);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        Draw(hwnd, hdc);

        if (drow == 3) {
            DrawBonobono(hdc, Blink);
        }

        EndPaint(hwnd, &ps);
        break;
    }

    case WM_SETCURSOR:
    {
        POINT mousePos;
        GetCursorPos(&mousePos);
        ScreenToClient(hwnd, &mousePos);

        if (mousePos.x > 16 && mousePos.x < 768 && mousePos.y > 87 && mousePos.y < 426) {
            SetCursor(LoadCursor(NULL, IDC_CROSS));
        }
        else {
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"ButtonWindowClass";

    if (!RegisterClass(&wc)) {
        return 1;
    }

    hWnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202007038_김광형"),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        0, 0,
        816, 518, //어째선지 800, 480으로 하면 실제로 그만큼의 크기로 만들어지지 않음
                  //그래서 실제 크기를 800, 480으로 하기위해 크기를 조절함
        NULL, NULL,
        hInstance,
        NULL
    );

    if (!hWnd) {
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        32, 24, 121, 64, hWnd, (HMENU)1, hInstance, NULL);
        //box 의 마진 & 패딩 8, 8 과 버튼의 마진 16
        //4개가 더해져 X좌표 32에서 시작

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        185, 24, 122, 64, hWnd, (HMENU)2, hInstance, NULL);
        //버튼간 마진 계산, 버튼간의 거리는 32로 정해짐

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        339, 24, 122, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        493, 24, 122, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        647, 24, 121, 64, hWnd, (HMENU)5, hInstance, NULL);
        //box 의 마진 & 패딩 8, 8 과 버튼의 마진 16
        //4개가 더해져 X좌표 768까지 그림

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}