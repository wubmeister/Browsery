#include <Windows.h>
#include "../FourtyTwo/Process.hpp"
#include <ShellScalingApi.h>

#define BROWSERY_WIDOWCLASS "BrowseryWindowClass"

static FourtyTwo::Process *gProcess;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WINDOWINFO wi;
	PAINTSTRUCT ps;
	FourtyTwo::PixelData pixelData;
	BITMAPINFO bi;
	UINT dpiX, dpiY;

	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		OutputDebugString("Painting\r\n");
		gProcess->getPixelData(&pixelData);

		if (!pixelData.pixels) {
			ValidateRgn(hWnd, NULL);
			return 0;
		}

		ZeroMemory(&(bi.bmiHeader), sizeof(bi.bmiHeader));
		bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
		bi.bmiHeader.biWidth = pixelData.width;
		bi.bmiHeader.biHeight = pixelData.height;
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biBitCount = 24;
		bi.bmiHeader.biCompression = BI_RGB;

		BeginPaint(hWnd, &ps);

		StretchDIBits(ps.hdc, 0, 0, pixelData.width, pixelData.height, 0, 0, pixelData.width, pixelData.height, pixelData.pixels, &bi, DIB_RGB_COLORS, SRCCOPY);

		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		OutputDebugString("Resize!");
		GetWindowInfo(hWnd, &wi);
		GetDpiForMonitor(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), MDT_EFFECTIVE_DPI, &dpiX, &dpiY);
		gProcess->setViewportSize(wi.rcClient.right - wi.rcClient.left, wi.rcClient.bottom - wi.rcClient.top, dpiX / 96);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nShowCmd)
{
	WNDCLASSEX wc;
	HWND hWnd;
	MSG msg;
	UINT dpiX, dpiY;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = BROWSERY_WIDOWCLASS;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window class registration failed", "Error", MB_ICONERROR | MB_OK);
		return 0;
	}

	POINT pt = { 0, 0 };
	GetDpiForMonitor(MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY), MDT_EFFECTIVE_DPI, &dpiX, &dpiY);

	hWnd = CreateWindowEx(
		0,
		BROWSERY_WIDOWCLASS,
		"Browsery",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640 * dpiX / 96,
		480 * dpiY / 96,
		NULL,
		NULL,
		hInstance,
		0
	);

	if (!hWnd) {
		MessageBox(NULL, "Window creation failed", "Error", MB_ICONERROR | MB_OK);
		return 0;
	}

	gProcess = new FourtyTwo::Process();

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, hWnd, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	delete gProcess;

	return msg.wParam;
}