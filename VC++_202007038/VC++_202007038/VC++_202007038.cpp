#include <Windows.h>


// 도형 변수
bool isBoxVisible = false;
bool BoxMoving = false;
bool isCircleVisible = false;

HWND hWnd;
bool Mainbox = true;
bool drawbox = true;

//마우스 변수
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT newstartPoint = { 0 };
POINT newendPoint = { 0 };
POINT movePoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;

void Draw(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    if (Mainbox) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200));
        SelectObject(hdc, hBrush);
        Rectangle(hdc, 8, 8, 800 - 24 , 480 - 46);
        DeleteObject(hBrush);
    }

    if (drawbox) {

    }
    
        if (isBoxVisible) {
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
            SelectObject(hdc, hBrush);

            int left = min(startPoint.x, endPoint.x);
            int top = min(startPoint.y, endPoint.y);
            int right = max(startPoint.x, endPoint.x);
            int bottom = max(startPoint.y, endPoint.y);

            Rectangle(hdc, left, top, right, bottom);
            DeleteObject(hBrush);

        }
        if (isMouseRButtonPressed && newstartPoint.x > startPoint.x && newstartPoint.y > startPoint.y && newendPoint.x < endPoint.x && newendPoint.y < endPoint.y && !isCircleVisible)
        {
            BoxMoving = true;
        }
        if (BoxMoving) {
            RECT rect;
            GetClientRect(hWnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)(RGB(0, 0, 255)));
            movePoint.x = newendPoint.x - newstartPoint.x;
            movePoint.y = newendPoint.y - newstartPoint.y;


            int left = min(startPoint.x + movePoint.x, endPoint.x + movePoint.x);
            int top = min(startPoint.y + movePoint.y, endPoint.y + movePoint.y);
            int right = max(startPoint.x + movePoint.x, endPoint.x + movePoint.x);
            int bottom = max(startPoint.y + movePoint.y, endPoint.y + movePoint.y);


            RECT Rect = { left, top, right, bottom };
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &Rect, hBrush);
            DeleteObject(hBrush);
        }

        if (isCircleVisible) {
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            SelectObject(hdc, hBrush);

            int centerX = max(startPoint.x, endPoint.x) - (max(startPoint.x, endPoint.x) - min(startPoint.x, endPoint.x));
            int centerY = max(startPoint.y, endPoint.y) - (max(startPoint.y, endPoint.y) - min(startPoint.y, endPoint.y));
            int radius = startPoint.x - endPoint.x - (newendPoint.x - newstartPoint.x);

            Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
            DeleteObject(hBrush);
        }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
    case WM_CREATE:
        SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 240, 200)));
        break;

    case WM_LBUTTONDOWN:
    {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
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
        isMouseRButtonPressed = 0;

        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

   
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;
            isCircleVisible = false;
            isBoxVisible = true;
            InvalidateRect(hwnd, NULL, TRUE);

        }
        else if (LOWORD(wParam) == 2) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;

            isCircleVisible = true;
            isBoxVisible = false;

            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 3) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;

        }
        else if (LOWORD(wParam) == 4) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;

        }
        else if (LOWORD(wParam) == 5) {
            startPoint.x = 0;
            startPoint.y = 0;
            endPoint.x = 0;
            endPoint.y = 0;

        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        Draw(hwnd, hdc);

        EndPaint(hwnd, &ps);
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



HWND hButton1, hButton2, hButton3, hButton4, hButton5;

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
        TEXT("202007038_김광형 "),
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
                15, 15, 50, 20, hWnd, (HMENU)1, hInstance, NULL);
        
    hButton2 = CreateWindow(
                L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                70, 15, 50, 20, hWnd, (HMENU)2, hInstance, NULL);
    
    hButton3 = CreateWindow(
                L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                125, 15, 70, 20, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
                L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                200, 15, 50, 20, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
                L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                255, 15, 50, 20, hWnd, (HMENU)5, hInstance, NULL);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}





//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:WINDOWS")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:WINDOWS")
//#endif
//
//#include <windows.h>
//
//
//// 도형 변수
//bool isBoxVisible = false;
//bool isCircleVisible = false;
//
////마우스 변수
//POINT startPoint = { 0 };
//POINT endPoint = { 0 };
//int isMouseLButtonPressed = 0;
//int isMouseRButtonPressed = 0;
//
//void Draw(HWND hWnd, HDC hdc) {
//    RECT rect;
//    GetClientRect(hWnd, &rect);
//    
//
//    if (isBoxVisible) {
//        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
//        SelectObject(hdc, hBrush);
//
//        int left = min(startPoint.x, endPoint.x);
//        int top = min(startPoint.y, endPoint.y);
//        int right = max(startPoint.x, endPoint.x);
//        int bottom = max(startPoint.y, endPoint.y);
//
//        Rectangle(hdc, left, top, right, bottom);
//        DeleteObject(hBrush);
//    }
//    if (isCircleVisible) {
//        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
//        SelectObject(hdc, hBrush);
//
//        int centerX = 400;
//        int centerY = 125;
//        int radius = startPoint.x;
//
//        Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
//        DeleteObject(hBrush);
//    }
//}
//
//// 윈도우 프로시저
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//    switch (message) {
//    case WM_LBUTTONDOWN:
//    {
//        startPoint.x = LOWORD(lParam);
//        startPoint.y = HIWORD(lParam);
//        isMouseLButtonPressed = 1;
//    }
//    break;
//
//    case WM_MOUSEMOVE:
//    {
//        // 마우스 이동 중
//        if (isMouseLButtonPressed)
//        {
//            endPoint.x = LOWORD(lParam);
//            endPoint.y = HIWORD(lParam);
//
//            // WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
//            InvalidateRect(hWnd, NULL, TRUE);
//        }
//    }
//    break;
//
//    case WM_LBUTTONUP:
//    {
//        endPoint.x = LOWORD(lParam);
//        endPoint.y = HIWORD(lParam);
//        isMouseLButtonPressed = 0;
//
//        // WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
//        InvalidateRect(hWnd, NULL, TRUE);
//       // UpdateWindow(hWnd);
//    }
//
//    break;
//    case WM_COMMAND:
//        if (LOWORD(wParam) == 1) {
//            // 첫 번째 버튼 클릭
//            isBoxVisible = true;
//        }
//        else if (LOWORD(wParam) == 2) {
//            // 두 번째 버튼 클릭
//            isBoxVisible = false;
//        }
//        else if (LOWORD(wParam) == 3) {
//            // 두 번째 버튼 클릭
//            isCircleVisible = true;
//        }
//        else if (LOWORD(wParam) == 4) {
//            // 두 번째 버튼 클릭
//            isCircleVisible = false;
//        }
//        break;
//    case WM_PAINT: {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hWnd, &ps);
//        Draw(hWnd, hdc);
//
//        EndPaint(hWnd, &ps);
//        break;
//    }
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//
//
//// 프로그램 진입점
//HWND hWnd;
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//    // 윈도우 클래스 등록
//    WNDCLASS wc = {};
//    wc.style = CS_HREDRAW | CS_VREDRAW;
//    wc.lpfnWndProc = WndProc;
//    wc.hInstance = hInstance;
//    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
//    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//    wc.lpszClassName = L"ButtonWindowClass";
//
//    if (!RegisterClass(&wc)) {
//        return 0;
//    }
//
//    // 윈도우 생성
//    hWnd = CreateWindowEx(
//        0,
//        L"ButtonWindowClass",
//        L"My Window",
//        WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT, CW_USEDEFAULT, 800, 480,
//        nullptr,
//        nullptr,
//        hInstance,
//        nullptr
//    );
//
//    if (!hWnd) {
//        return 0;
//    }
//
//
//
//    /*버튼*/
//   /* hButton1 = CreateWindow(
//        L"BUTTON", L"사각형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
//        20, 20, 100, 40, hWnd, (HMENU)1, hInstance, NULL);
//
//    hButton2 = CreateWindow(
//        L"BUTTON", L"지우기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
//        20, 70, 100, 40, hWnd, (HMENU)2, hInstance, NULL);*/
//
//
//
//    ShowWindow(hWnd, nCmdShow);
//    UpdateWindow(hWnd);
//
//    MSG msg;
//    while (GetMessage(&msg, NULL, 0, 0)) {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    return (int)msg.wParam;
//}