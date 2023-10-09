#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT previousMousePos = { 0, 0 };
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT newSPoint = { 0 };
POINT newEPoint = { 0 };
POINT movePoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);
		isMouseLButtonPressed = 1;
	}
	break;

	//강의에 안나왔지만 마우스가 움직일때의 이벤트를 뜻합니다.
	case WM_MOUSEMOVE:
		{
			// 마우스 이동 중
			if (isMouseLButtonPressed)
			{
				endPoint.x = LOWORD(lParam);
				endPoint.y = HIWORD(lParam);
			
				// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
				InvalidateRect(hwnd, NULL, TRUE);
			}

			if (isMouseRButtonPressed)
			{
				newEPoint.x = LOWORD(lParam);
				newEPoint.y = HIWORD(lParam);

				// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			isMouseLButtonPressed = 0;

			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
			InvalidateRect(hwnd, NULL, TRUE);
		}

		break;

	case WM_RBUTTONDOWN:
	{
		newSPoint.x = LOWORD(lParam);
		newSPoint.y = HIWORD(lParam);
		isMouseRButtonPressed = 1;
	}
	break;

	case WM_RBUTTONUP:
	{
		newEPoint.x = LOWORD(lParam);
		newEPoint.y = HIWORD(lParam);
		isMouseRButtonPressed = 0;

		// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
		InvalidateRect(hwnd, NULL, TRUE);
	}

	break;

		case WM_PAINT:
		{
			HDC hdc = GetDC(hwnd);

			if (isMouseLButtonPressed)
			{
				RECT rect;
				GetClientRect(hwnd, &rect);
				FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

				int left = min(startPoint.x, endPoint.x);
				int top = min(startPoint.y, endPoint.y);
				int right = max(startPoint.x, endPoint.x);
				int bottom = max(startPoint.y, endPoint.y);

				RECT Rect = { left, top, right, bottom };
				HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
				FillRect(hdc, &Rect, hBrush);
				DeleteObject(hBrush);
			}
			if (isMouseRButtonPressed && newSPoint.x > startPoint.x && newSPoint.y > startPoint.y && newEPoint.x < endPoint.x && newEPoint.y < endPoint.y)
			{
				RECT rect;
				GetClientRect(hwnd, &rect);
				FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
				movePoint.x = newEPoint.x - newSPoint.x;
				movePoint.y = newEPoint.y - newSPoint.y;


				int left = min(startPoint.x + movePoint.x, endPoint.x + movePoint.x);
				int top = min(startPoint.y + movePoint.y, endPoint.y + movePoint.y);
				int right = max(startPoint.x + movePoint.x, endPoint.x + movePoint.x);
				int bottom = max(startPoint.y + movePoint.y, endPoint.y + movePoint.y);


				RECT Rect = { left, top, right, bottom };
				HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
				FillRect(hdc, &Rect, hBrush);
				DeleteObject(hBrush);
			}
			
			ReleaseDC(hwnd, hdc);

		}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);		
	}

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202007038_김광형 "),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//종료 메시지 보내기
	return (int)msg.wParam;

}