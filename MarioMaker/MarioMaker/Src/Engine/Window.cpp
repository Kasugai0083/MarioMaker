#include "Window.h"

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

HWND hWnd;
HWND GetWindowHandle() { return hWnd; }
POINT start_point;
POINT end_point;
bool is_click = false;

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		is_click = true;
	
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
		is_click = false;
		end_point = start_point;

	case WM_MOVE:
		start_point.x = LOWORD(lparam);
		start_point.y = HIWORD(lparam);
		break;


	default:
		return DefWindowProc(window_handle, message_id, wparam, lparam);
		break;
	}

	return 0;
}

bool MakeWindow(int width, int height, const char* title)
{
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEXA),			// 構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,		// クラスのスタイル
		WindowProc,						// ウィンドウプロシージャ
		0,								// 補助メモリ
		0,								// 補助メモリ
		GetModuleHandle(nullptr),		// このプログラムのインスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),// アイコン画像
		LoadCursor(NULL, IDC_ARROW),	// カーソル画像
		NULL,							// 背景ブラシ(背景色)
		NULL,							// メニュー名
		WINDOW_CLASS_NAME.c_str(),				// クラス名									
		NULL							// 小さいアイコン
	};

	// 構造体の登録
	if (RegisterClassEx(&window_class) == 0)
	{
		return 0;
	}

	// ウィンドウ作成
	hWnd = CreateWindowA(
		WINDOW_CLASS_NAME.c_str(),
		title,
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE ,
		CW_USEDEFAULT,
		0,
		width,
		height,
		NULL,
		NULL,
		GetModuleHandle(nullptr),
		NULL);

	RECT window_rect;
	RECT client_rect;

	GetWindowRect(hWnd, &window_rect);
	GetClientRect(hWnd, &client_rect);

	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

	SetWindowPos(hWnd, NULL, CW_USEDEFAULT, CW_USEDEFAULT, frame_size_x + width, frame_size_y + height, SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;
}
