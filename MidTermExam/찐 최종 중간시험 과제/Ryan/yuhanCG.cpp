#include <Windows.h>


POINT movePoint;
POINT headerSPoint;
POINT headerEPoint;

bool BoxMoving = false;
bool moveRect = false;

int radice;
int nradice;

int left;
int top;
int right;
int bottom;
int check = 0;

void DrawBox(HDC hdc, int isMouseRButtonPressed, POINT startPoint, POINT endPoint, POINT newstartPoint, POINT newendPoint) {
    HBRUSH RBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, RBrush);

    if (check == 0) {
        headerSPoint = startPoint;
        headerEPoint = endPoint;
    }
    else {
        headerSPoint = headerSPoint;
        headerEPoint = headerEPoint;
    }

    if (isMouseRButtonPressed == 1  && newstartPoint.y > headerSPoint.y && newendPoint.x < headerEPoint.x && newendPoint.y < headerEPoint.y && newstartPoint.x > headerSPoint.x)
    {
        BoxMoving = true;
    }
    else if (isMouseRButtonPressed == 2) {
        BoxMoving = false;
    }

    if (BoxMoving) {
        movePoint.x = newendPoint.x - newstartPoint.x;
        movePoint.y = newendPoint.y - newstartPoint.y;

        left = min(headerSPoint.x + movePoint.x, headerEPoint.x + movePoint.x);
        top = min(headerSPoint.y + movePoint.y, headerEPoint.y + movePoint.y);
        right = max(headerSPoint.x + movePoint.x, headerEPoint.x + movePoint.x);
        bottom = max(headerSPoint.y + movePoint.y, headerEPoint.y + movePoint.y);
        moveRect = true;
        check = 1;
    }
    else if (isMouseRButtonPressed == 2 && moveRect == true) {

        headerSPoint.x = headerSPoint.x + movePoint.x;
        headerSPoint.y = headerSPoint.y + movePoint.y;
        headerEPoint.x = headerEPoint.x + movePoint.x;
        headerEPoint.y = headerEPoint.y + movePoint.y;

        left = min(headerSPoint.x, headerEPoint.x);
        top = min(headerSPoint.y, headerEPoint.y);
        right = max(headerSPoint.x, headerEPoint.x);
        bottom = max(headerSPoint.y, headerEPoint.y);

        moveRect = false;
        isMouseRButtonPressed = 0;;
    }
    else {

        left = min(headerSPoint.x, headerEPoint.x);
        top = min(headerSPoint.y, headerEPoint.y);
        right = max(headerSPoint.x, headerEPoint.x);
        bottom = max(headerSPoint.y, headerEPoint.y);

    }

    Rectangle(hdc, left, top, right, bottom);
    DeleteObject(RBrush);
}

void DrawCircle(HDC hdc, int isMouseLButtonPressed,  int isMouseRButtonPressed, POINT startPoint, POINT endPoint, POINT newendPoint, POINT newstartPoint) {

    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
    SelectObject(hdc, hBrush);

    if (isMouseLButtonPressed == 1) {
        radice = 0;
        nradice = 0;
    }

    left = min(startPoint.x, endPoint.x);
    top = min(startPoint.y, endPoint.y);
    right = max(startPoint.x, endPoint.x);
    bottom = max(startPoint.y, endPoint.y);

    if (isMouseRButtonPressed == 1) {
        radice = nradice + newendPoint.x - newstartPoint.x;
    }
    if (isMouseRButtonPressed == 2) {
        nradice = radice;
    }

    Ellipse(hdc, left - radice / 2, top - radice / 2, right + radice / 2, bottom + radice / 2);
    DeleteObject(hBrush);
}

void DrawBonobono(HDC hdc, int blink) {

    HBRUSH SBrush = CreateSolidBrush(RGB(127, 200, 255));
    SelectObject(hdc, SBrush);
    Ellipse(hdc, 400 - 100, 284 - 100, 400 + 100, 284 + 100); //피부
    DeleteObject(SBrush);

    HBRUSH MBrush = CreateSolidBrush(RGB(255, 150, 255));
    SelectObject(hdc, MBrush);
    Ellipse(hdc, 400 - 15, 325 - 27, 400 + 15, 325 + 27); //입
    DeleteObject(MBrush);


    HBRUSH RBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, RBrush);
    Ellipse(hdc, 378 - 21, 300 - 18, 378 + 21, 300 + 18); //입술
    Ellipse(hdc, 422 - 21, 300 - 18, 422 + 21, 300 + 18); //입술
    DeleteObject(RBrush);

    HBRUSH BBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, BBrush);

    Ellipse(hdc, 400 - 15, 284 - 15, 400 + 15, 284 + 15); //코

    MoveToEx(hdc, 372, 294, NULL); //왼 수염
    LineTo(hdc, 351, 288);
    MoveToEx(hdc, 372, 294, NULL);
    LineTo(hdc, 351, 310);

    MoveToEx(hdc, 428, 294, NULL); //오른 수염 
    LineTo(hdc, 449, 288);
    MoveToEx(hdc, 428, 294, NULL);
    LineTo(hdc, 449, 310);
    DeleteObject(BBrush);

    if (blink == 0) {
        HBRUSH BBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, BBrush); //눈
        Ellipse(hdc, 320 - 5, 254 - 10, 320 + 5, 254 + 10);
        Ellipse(hdc, 480 - 5, 254 - 10, 480 + 5, 254 + 10);
        DeleteObject(BBrush);

        HBRUSH RBrush = CreateSolidBrush(RGB(255, 255, 255)); //동공
        SelectObject(hdc, RBrush);
        Ellipse(hdc, 320 - 2, 254 - 4, 320 + 2, 254 + 4);
        Ellipse(hdc, 480 - 2, 254 - 4, 480 + 2, 254 + 4);
        DeleteObject(RBrush);
    }
    else {
        HBRUSH BBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, BBrush);
        MoveToEx(hdc, 335, 254, NULL);
        LineTo(hdc, 315, 244);
        MoveToEx(hdc, 335, 254, NULL);
        LineTo(hdc, 315, 264);

        MoveToEx(hdc, 465, 254, NULL);
        LineTo(hdc, 485, 244);
        MoveToEx(hdc, 465, 254, NULL);
        LineTo(hdc, 485, 264);
        DeleteObject(BBrush);
    }
}

void DrawRyan(HDC hdc, POINT startPoint, POINT endPoint)
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


}

void DrawCube(HDC hdc, POINT startPoint, POINT endPoint) {
    HBRUSH hBrush = CreateSolidBrush(RGB(180, 180, 180));
    SelectObject(hdc, hBrush);

    int left, top, right, bottom;

    left = min(startPoint.x, endPoint.x);
    top = min(startPoint.y, endPoint.y);
    right = max(startPoint.x, endPoint.x);
    bottom = max(startPoint.y, endPoint.y);

    if (endPoint.y - startPoint.y <= 0 && endPoint.x - startPoint.x <= 0) {
        Rectangle(hdc, left + ((right - left) / 4), top + ((bottom - top) / 4), right, bottom);

        POINT topRect[] = {
             {left + ((right - left) / 4), top + ((bottom - top) / 4)},
             {left, top},
             {right - ((right - left) / 4), top},
             {right, top + ((bottom - top) / 4)}
        };

        Polygon(hdc, topRect, sizeof(topRect) / sizeof(topRect[0]));

        hBrush = CreateSolidBrush(RGB(120, 120, 120));
        SelectObject(hdc, hBrush);

        POINT leftRect[] = {
            {left + ((right - left) / 4), top + ((bottom - top) / 4)},
            {left, top},
            {left, bottom - ((bottom - top) / 4) - 1},
            {left + ((right - left) / 4), bottom - 1}
        };

        Polygon(hdc, leftRect, sizeof(leftRect) / sizeof(leftRect[0]));
        DeleteObject(hBrush);
    }
    else if (endPoint.x - startPoint.x <= 0) {
        Rectangle(hdc, left + ((right - left) / 4), top, right, bottom - ((bottom - top) / 4));

        POINT bottomRect[] = {
            {left + ((right - left) / 4), bottom - ((bottom - top) / 4) - 1},
            {left, bottom},
            {right - ((right - left) / 4), bottom},
            {right, bottom - ((bottom - top) / 4) - 1}
        };

        Polygon(hdc, bottomRect, sizeof(bottomRect) / sizeof(bottomRect[0]));

        hBrush = CreateSolidBrush(RGB(120, 120, 120));
        SelectObject(hdc, hBrush);

        POINT leftRect[] = {
            {left + ((right - left) / 4), top},
            {left, top + ((bottom - top) / 4)},
            {left, bottom},
            {left + ((right - left) / 4), bottom - ((bottom - top) / 4) - 1}
        };

        Polygon(hdc, leftRect, sizeof(leftRect) / sizeof(leftRect[0]));
        DeleteObject(hBrush);
    }
    else if (endPoint.y - startPoint.y <= 0) {
        Rectangle(hdc, left, top + ((bottom - top) / 4), right - ((right - left) / 4), bottom);

        POINT topRect[] = {
            {left, top + ((bottom - top) / 4)},
            {left + ((right - left) / 4), top},
            {right, top},
            {right - ((right - left) / 4), top + ((bottom - top) / 4)}
        };

        Polygon(hdc, topRect, sizeof(topRect) / sizeof(topRect[0]));

        hBrush = CreateSolidBrush(RGB(120, 120, 120));
        SelectObject(hdc, hBrush);

        POINT rightRect[] = {
            {right - ((right - left) / 4) - 1, top + ((bottom - top) / 4)},
            {right, top},
            {right, bottom - ((bottom - top) / 4) - 1},
            {right - ((right - left) / 4) - 1, bottom - 1}
        };

        Polygon(hdc, rightRect, sizeof(rightRect) / sizeof(rightRect[0]));
        DeleteObject(hBrush);
    }
    else {
        Rectangle(hdc, left, top, right - ((right - left) / 4), bottom - ((bottom - top) / 4));

        POINT bottomRect[] = {
            {left, bottom - ((bottom - top) / 4) - 1},
            {left + ((right - left) / 4), bottom},
            {right, bottom},
            {right - ((right - left) / 4), bottom - ((bottom - top) / 4) - 1}
        };

        Polygon(hdc, bottomRect, sizeof(bottomRect) / sizeof(bottomRect[0]));

        hBrush = CreateSolidBrush(RGB(120, 120, 120));
        SelectObject(hdc, hBrush);

        POINT rightRect[] = {
            {right - ((right - left) / 4) - 1, top},
            {right, top + ((bottom - top) / 4)},
            {right, bottom},
            {right - ((right - left) / 4) - 1, bottom - ((bottom - top) / 4)}
        };

        Polygon(hdc, rightRect, sizeof(rightRect) / sizeof(rightRect[0]));
        DeleteObject(hBrush);
    }
}