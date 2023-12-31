﻿#include <Windows.h>

// 도형 변수
bool BoxMoving = false;
bool cubeMoving = false;
bool moveRect = false;
bool movecube = false;
bool isBoxOn = false;
int Blink = 0;
int drow = 0;

int left = 0;
int top = 0;
int right = 0;
int bottom = 0;
int radice = 0;


HWND hWnd;
HWND hButton1, hButton2, hButton3, hButton4, hButton5;

bool Mainbox = true;
bool drawbox = true;

//마우스 변수
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT newstartPoint = { 0 };
POINT newendPoint = { 0 };
POINT movePoint = { 0 };
POINT cubeMovePoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;


void Draw(HWND hWnd, HDC hdc) {
    HBRUSH RBrush = CreateSolidBrush(RGB(0, 0, 0));
    if (Mainbox) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200));
        SelectObject(hdc, hBrush);
        Rectangle(hdc, 8, 8, 776, 434);
        DeleteObject(hBrush);
    }

    if (drawbox) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, hBrush);
        Rectangle(hdc, 16, 104, 768, 426);
        DeleteObject(hBrush);
    }

    if (drow != 0 && startPoint.x > 16 && startPoint.y > 104 && startPoint.x < 768 && startPoint.y < 426) {
        if (endPoint.x > 16 && endPoint.y > 104 && endPoint.x < 768 && endPoint.y < 426) {
            switch (drow) {
            case 1:
            {
                if (isMouseRButtonPressed == 1 && newstartPoint.x > startPoint.x && newstartPoint.y > startPoint.y && newendPoint.x < endPoint.x && newendPoint.y < endPoint.y)
                {
                    BoxMoving = true;
                }
                else if (isMouseRButtonPressed == 2) {
                    BoxMoving = false;
                }

                if (BoxMoving) {
                    SelectObject(hdc, RBrush);
                    movePoint.x = newendPoint.x - newstartPoint.x;
                    movePoint.y = newendPoint.y - newstartPoint.y;
                    moveRect = true;

                    left = min(startPoint.x + movePoint.x, endPoint.x + movePoint.x);
                    top = min(startPoint.y + movePoint.y, endPoint.y + movePoint.y);
                    right = max(startPoint.x + movePoint.x, endPoint.x + movePoint.x);
                    bottom = max(startPoint.y + movePoint.y, endPoint.y + movePoint.y);
                }
                else if (isMouseRButtonPressed == 2 && moveRect == true) {
                    SelectObject(hdc, RBrush);

                    startPoint.x = startPoint.x + movePoint.x;
                    startPoint.y = startPoint.y + movePoint.y;
                    endPoint.x = endPoint.x + movePoint.x;
                    endPoint.y = endPoint.y + movePoint.y;

                    left = min(startPoint.x, endPoint.x);
                    top = min(startPoint.y, endPoint.y);
                    right = max(startPoint.x, endPoint.x);
                    bottom = max(startPoint.y, endPoint.y);

                    isMouseRButtonPressed = 0;
                    moveRect = false;
                }
                else {
                    SelectObject(hdc, RBrush);

                    left = min(startPoint.x, endPoint.x);
                    top = min(startPoint.y, endPoint.y);
                    right = max(startPoint.x, endPoint.x);
                    bottom = max(startPoint.y, endPoint.y);

                }

                Rectangle(hdc, left, top, right, bottom);
                DeleteObject(RBrush);

                break;
            }


            case 2:
            {

                HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
                SelectObject(hdc, hBrush);

                left = min(startPoint.x, endPoint.x);
                top = min(startPoint.y, endPoint.y);
                right = max(startPoint.x, endPoint.x);
                bottom = max(startPoint.y, endPoint.y);

                if (isMouseRButtonPressed == 1) {
                    radice = newendPoint.x - newstartPoint.x;
                }

                Ellipse(hdc, left + radice / 2, top + radice / 2, right - radice / 2, bottom - radice / 2);
                DeleteObject(hBrush);
                break;
            }

            case 3:
            {



                break;
            }
            case 4:
            {
                left = min(startPoint.x, endPoint.x);
                top = min(startPoint.y, endPoint.y);
                right = max(startPoint.x, endPoint.x);
                bottom = max(startPoint.y, endPoint.y);

                if (endPoint.y - startPoint.y >= 0) {
                    HBRUSH hBrush = CreateSolidBrush(RGB(255, 200, 15));
                    SelectObject(hdc, hBrush);
                    Ellipse(hdc, (left + (right - left) / 3) - 2 * (right - left) / 5, (top + (bottom - top) / 3) - (bottom - top) / 3, (right - (right - left) / 3) - 2 * (right - left) / 5, (bottom - (bottom - top) / 3) - (bottom - top) / 3); //왼쪽 귀
                    Ellipse(hdc, (left + (right - left) / 3) + 2 * (right - left) / 5, (top + (bottom - top) / 3) - (bottom - top) / 3, (right - (right - left) / 3) + 2 * (right - left) / 5, (bottom - (bottom - top) / 3) - (bottom - top) / 3); //오른쪽 귀

                    Ellipse(hdc, left, top, right, bottom); //얼굴
                    DeleteObject(hBrush);

                    HBRUSH WBrush = CreateSolidBrush(RGB(255, 255, 255));
                    SelectObject(hdc, WBrush);
                    Ellipse(hdc, (left + (right - left) * 3 / 7) - (right - left) / 14, (top + (bottom - top) * 3 / 7) + (bottom - top) / 13, (right - (right - left) * 3 / 7) - (right - left) / 14, (bottom - (bottom - top) * 3 / 7) + (bottom - top) / 13); //왼쪽 코
                    Ellipse(hdc, (left + (right - left) * 3 / 7) + (right - left) / 14, (top + (bottom - top) * 3 / 7) + (bottom - top) / 13, (right - (right - left) * 3 / 7) + (right - left) / 14, (bottom - (bottom - top) * 3 / 7) + (bottom - top) / 13); //오른쪽 코
                    DeleteObject(WBrush);

                    HBRUSH BBrush = CreateSolidBrush(RGB(0, 0, 0));
                    SelectObject(hdc, BBrush);
                    Ellipse(hdc, (left + (right - left) * 23 / 50) - (right - left) / 4, (top + (bottom - top) * 23 / 50) - (bottom - top) / 8, (right - (right - left) * 23 / 50) - (right - left) / 4, (bottom - (bottom - top) * 23 / 50) - (bottom - top) / 8); //왼쪽 눈
                    Ellipse(hdc, (left + (right - left) * 23 / 50) + (right - left) / 4, (top + (bottom - top) * 23 / 50) - (bottom - top) / 8, (right - (right - left) * 23 / 50) + (right - left) / 4, (bottom - (bottom - top) * 23 / 50) - (bottom - top) / 8); //오른쪽 눈

                    MoveToEx(hdc, left + (right - left) / 6, top + (bottom - top) * 25 / 100, NULL); //왼쪽 눈썹
                    LineTo(hdc, left + (right - left) * 2 / 6, top + (bottom - top) * 25 / 100);
                    MoveToEx(hdc, left + (right - left) / 6, top + (bottom - top) * 26 / 100, NULL);
                    LineTo(hdc, left + (right - left) * 2 / 6, top + (bottom - top) * 26 / 100);
                    MoveToEx(hdc, left + (right - left) / 6, top + (bottom - top) * 24 / 100, NULL);
                    LineTo(hdc, left + (right - left) * 2 / 6, top + (bottom - top) * 24 / 100);

                    MoveToEx(hdc, right - (right - left) / 6, top + (bottom - top) * 25 / 100, NULL); //오른쪽 눈썹
                    LineTo(hdc, right - (right - left) * 2 / 6, top + (bottom - top) * 25 / 100);
                    MoveToEx(hdc, right - (right - left) / 6, top + (bottom - top) * 26 / 100, NULL);
                    LineTo(hdc, right - (right - left) * 2 / 6, top + (bottom - top) * 26 / 100);
                    MoveToEx(hdc, right - (right - left) / 6, top + (bottom - top) * 24 / 100, NULL);
                    LineTo(hdc, right - (right - left) * 2 / 6, top + (bottom - top) * 24 / 100);
                    DeleteObject(BBrush);
                }
                else {
                    HBRUSH hBrush = CreateSolidBrush(RGB(255, 200, 15));
                    SelectObject(hdc, hBrush);
                    Ellipse(hdc, (left + (right - left) / 3) - 2 * (right - left) / 5, (top + (bottom - top) / 3) + (bottom - top) / 3, (right - (right - left) / 3) - 2 * (right - left) / 5, (bottom - (bottom - top) / 3) + (bottom - top) / 3); //왼쪽 귀
                    Ellipse(hdc, (left + (right - left) / 3) + 2 * (right - left) / 5, (top + (bottom - top) / 3) + (bottom - top) / 3, (right - (right - left) / 3) + 2 * (right - left) / 5, (bottom - (bottom - top) / 3) + (bottom - top) / 3); //오른쪽 귀

                    Ellipse(hdc, left, top, right, bottom); //얼굴
                    DeleteObject(hBrush);

                    HBRUSH WBrush = CreateSolidBrush(RGB(255, 255, 255));
                    SelectObject(hdc, WBrush);
                    Ellipse(hdc, (left + (right - left) * 3 / 7) - (right - left) / 14, (top + (bottom - top) * 3 / 7) - (bottom - top) / 13, (right - (right - left) * 3 / 7) - (right - left) / 14, (bottom - (bottom - top) * 3 / 7) - (bottom - top) / 13); //왼쪽 코
                    Ellipse(hdc, (left + (right - left) * 3 / 7) + (right - left) / 14, (top + (bottom - top) * 3 / 7) - (bottom - top) / 13, (right - (right - left) * 3 / 7) + (right - left) / 14, (bottom - (bottom - top) * 3 / 7) - (bottom - top) / 13); //오른쪽 코
                    DeleteObject(WBrush);

                    HBRUSH BBrush = CreateSolidBrush(RGB(0, 0, 0));
                    SelectObject(hdc, BBrush);
                    Ellipse(hdc, (left + (right - left) * 23 / 50) - (right - left) / 4, (top + (bottom - top) * 23 / 50) + (bottom - top) / 8, (right - (right - left) * 23 / 50) - (right - left) / 4, (bottom - (bottom - top) * 23 / 50) + (bottom - top) / 8); //왼쪽 눈
                    Ellipse(hdc, (left + (right - left) * 23 / 50) + (right - left) / 4, (top + (bottom - top) * 23 / 50) + (bottom - top) / 8, (right - (right - left) * 23 / 50) + (right - left) / 4, (bottom - (bottom - top) * 23 / 50) + (bottom - top) / 8); //오른쪽 눈

                    MoveToEx(hdc, left + (right - left) / 6, bottom - (bottom - top) * 25 / 100, NULL); //왼쪽 눈썹
                    LineTo(hdc, left + (right - left) * 2 / 6, bottom - (bottom - top) * 25 / 100);
                    MoveToEx(hdc, left + (right - left) / 6, bottom - (bottom - top) * 26 / 100, NULL);
                    LineTo(hdc, left + (right - left) * 2 / 6, bottom - (bottom - top) * 26 / 100);
                    MoveToEx(hdc, left + (right - left) / 6, bottom - (bottom - top) * 24 / 100, NULL);
                    LineTo(hdc, left + (right - left) * 2 / 6, bottom - (bottom - top) * 24 / 100);

                    MoveToEx(hdc, right - (right - left) / 6, bottom - (bottom - top) * 25 / 100, NULL); //오른쪽 눈썹
                    LineTo(hdc, right - (right - left) * 2 / 6, bottom - (bottom - top) * 25 / 100);
                    MoveToEx(hdc, right - (right - left) / 6, bottom - (bottom - top) * 26 / 100, NULL);
                    LineTo(hdc, right - (right - left) * 2 / 6, bottom - (bottom - top) * 26 / 100);
                    MoveToEx(hdc, right - (right - left) / 6, bottom - (bottom - top) * 24 / 100, NULL);
                    LineTo(hdc, right - (right - left) * 2 / 6, bottom - (bottom - top) * 24 / 100);
                    DeleteObject(BBrush);
                }

                break;
            }
            case 5:
            {
                HBRUSH RBrush = CreateSolidBrush(RGB(150, 150, 150));

                if (isMouseRButtonPressed == 1 && newstartPoint.x > startPoint.x && newstartPoint.y > startPoint.y && newendPoint.x < endPoint.x && newendPoint.y < endPoint.y)
                {
                    cubeMoving = true;
                }
                else if (isMouseRButtonPressed == 2) {
                    cubeMoving = false;
                }

                if (cubeMoving) {
                    SelectObject(hdc, RBrush);
                    movePoint.x = newendPoint.x - newstartPoint.x;
                    movePoint.y = newendPoint.y - newstartPoint.y;
                    movecube = true;

                    left = min(startPoint.x + movePoint.x, endPoint.x + movePoint.x);
                    top = min(startPoint.y + movePoint.y, endPoint.y + movePoint.y);
                    right = max(startPoint.x + movePoint.x, endPoint.x + movePoint.x);
                    bottom = max(startPoint.y + movePoint.y, endPoint.y + movePoint.y);
                }
                else if (isMouseRButtonPressed == 2 && movecube == true) {
                    SelectObject(hdc, RBrush);

                    startPoint.x = startPoint.x + movePoint.x;
                    startPoint.y = startPoint.y + movePoint.y;
                    endPoint.x = endPoint.x + movePoint.x;
                    endPoint.y = endPoint.y + movePoint.y;

                    left = min(startPoint.x, endPoint.x);
                    top = min(startPoint.y, endPoint.y);
                    right = max(startPoint.x, endPoint.x);
                    bottom = max(startPoint.y, endPoint.y);

                    isMouseRButtonPressed = 0;
                    movecube = false;
                }
                /*else if (isBoxOn) {
                    SelectObject(hdc, RBrush);
                    cubeMovePoint.x = endPoint.x - startPoint.x;
                    cubeMovePoint.y = endPoint.y - startPoint.y;


                    right = endPoint.x + cubeMovePoint.x;
                    bottom = endPoint.y + cubeMovePoint.y;
                }*/ //좌클릭 크기 조절인데 모르겠다!
                else {
                    SelectObject(hdc, RBrush);

                    left = min(startPoint.x, endPoint.x);
                    top = min(startPoint.y, endPoint.y);
                    right = max(startPoint.x, endPoint.x);
                    bottom = max(startPoint.y, endPoint.y);

                }

                Rectangle(hdc, left, top, right, bottom);
                DeleteObject(RBrush);

                if (endPoint.y - startPoint.y <= 0 && endPoint.x - startPoint.x <= 0) {
                    MoveToEx(hdc, right + (left - right) / 6, top, NULL);
                    LineTo(hdc, right + (left - right) / 6, bottom);
                    MoveToEx(hdc, left, bottom + (top - bottom) / 6, NULL);
                    LineTo(hdc, right, bottom + (top - bottom) / 6);
                }
                else if (endPoint.x - startPoint.x <= 0) {
                    MoveToEx(hdc, right + (left - right) / 6, top, NULL);
                    LineTo(hdc, right + (left - right) / 6, bottom);
                    MoveToEx(hdc, left, top + (bottom - top) / 6, NULL);
                    LineTo(hdc, right, top + (bottom - top) / 6);
                }
                else if (endPoint.y - startPoint.y <= 0) {
                    MoveToEx(hdc, left + (right - left) / 6, top, NULL);
                    LineTo(hdc, left + (right - left) / 6, bottom);
                    MoveToEx(hdc, left, bottom + (top - bottom) / 6, NULL);
                    LineTo(hdc, right, bottom + (top - bottom) / 6);
                }
                else {
                    MoveToEx(hdc, left + (right - left) / 6, top, NULL);
                    LineTo(hdc, left + (right - left) / 6, bottom);
                    MoveToEx(hdc, left, top + (bottom - top) / 6, NULL);
                    LineTo(hdc, right, top + (bottom - top) / 6);
                }
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

            radice = 0;

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
            radice = 0;

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
            HBRUSH SBrush = CreateSolidBrush(RGB(127, 200, 255));
            SelectObject(hdc, SBrush);
            Ellipse(hdc, 400 - 100, 256 - 100, 400 + 100, 256 + 100); //피부
            DeleteObject(SBrush);

            HBRUSH MBrush = CreateSolidBrush(RGB(255, 150, 255));
            SelectObject(hdc, MBrush);
            Ellipse(hdc, 400 - 15, 297 - 27, 400 + 15, 297 + 27); //입
            DeleteObject(MBrush);


            HBRUSH RBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, RBrush);
            Ellipse(hdc, 378 - 21, 272 - 18, 378 + 21, 272 + 18); //입술
            Ellipse(hdc, 422 - 21, 272 - 18, 422 + 21, 272 + 18); //입술
            DeleteObject(RBrush);

            HBRUSH BBrush = CreateSolidBrush(RGB(0, 0, 0));
            SelectObject(hdc, BBrush);

            Ellipse(hdc, 400 - 15, 256 - 15, 400 + 15, 256 + 15); //코

            MoveToEx(hdc, 372, 266, NULL); //왼 수염
            LineTo(hdc, 351, 260);
            MoveToEx(hdc, 372, 276, NULL);
            LineTo(hdc, 351, 282);

            MoveToEx(hdc, 428, 266, NULL); //오른 수염 
            LineTo(hdc, 449, 260);
            MoveToEx(hdc, 428, 272, NULL);
            LineTo(hdc, 449, 282);
            DeleteObject(BBrush);

            if (Blink == 0) {
                HBRUSH BBrush = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, BBrush); //눈
                Ellipse(hdc, 320 - 5, 226 - 10, 320 + 5, 226 + 10);
                Ellipse(hdc, 480 - 5, 226 - 10, 480 + 5, 226 + 10);
                DeleteObject(BBrush);

                HBRUSH RBrush = CreateSolidBrush(RGB(255, 255, 255)); //동공
                SelectObject(hdc, RBrush);
                Ellipse(hdc, 320 - 2, 226 - 4, 320 + 2, 226 + 4);
                Ellipse(hdc, 480 - 2, 226 - 4, 480 + 2, 226 + 4);
                DeleteObject(RBrush);
            }
            else {
                HBRUSH BBrush = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, BBrush);
                MoveToEx(hdc, 335, 226, NULL);
                LineTo(hdc, 315, 216);
                MoveToEx(hdc, 335, 226, NULL);
                LineTo(hdc, 315, 236);

                MoveToEx(hdc, 465, 226, NULL);
                LineTo(hdc, 485, 216);
                MoveToEx(hdc, 465, 226, NULL);
                LineTo(hdc, 485, 236);
                DeleteObject(BBrush);
            }
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
    // 윈도우 클래스 등록
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

    int width = 800;
    int height = 480;

    hWnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202007038_김광형"),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        0, 0,
        width, height,
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
        24, 24, 135, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        175, 24, 134, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        325, 24, 134, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        475, 24, 134, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        625, 24, 135, 64, hWnd, (HMENU)5, hInstance, NULL);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}