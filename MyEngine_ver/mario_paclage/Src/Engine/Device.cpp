#include "Device.h"
#include "Graphics/DirectX.h"

namespace {

	/**
	* マウス関連
	*/
	struct t_Point {
		POINT start = { 0,0 };//クリック時以外の座標を取得
		POINT end = { 0,0 };  //クリック時の座標を取得
	}pt;

	bool is_drag = false; //ドラッグ判定変数
	bool is_click = false;//ダブルクリック判定変数

	/**
	* キーボード関連
	*/
	const int INPUT_FRAME = 2;
	const int KEYNUM = 256;

	enum FLAME {

		KB_CUR = 0,
		KB_PRE,
	};
};

LRESULT CALLBACK WindowProc(HWND windowHandle_, UINT messageId_, WPARAM wParam_, LPARAM lParam_)
{
	int timer = 0;

	switch (messageId_)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	/*
	ダブルクリックが必要になったら
	case WM_LBUTTONDBLCLK:

		if (!is_click) {
			is_click = 1;
		}
	*/

	// マウスボタンクリック開始時
	case WM_LBUTTONDOWN:  // 左

		if (++timer >= 1) {
			is_click = true;
			pt.end.x = pt.start.x;
			pt.end.y = pt.start.y;
		}

		break;

	case WM_RBUTTONDOWN:  // 右
		MessageBox(NULL, "右クリック", NULL, MB_OK);
		break;
	case WM_MBUTTONDOWN:  // 中
		MessageBox(NULL, "ホイールクリック", NULL, MB_OK);
		break;
		// マウスボタンクリック終了時
	case WM_LBUTTONUP:
		is_click = false;

		pt.end = { 0,0 };
		break;

		// マウスカーソル(表示or非表示)
	case WM_CREATE:
		ShowCursor(TRUE);
		break;

	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:

		// 更新する座標を取得
		pt.start.x = LOWORD(lParam_);
		pt.start.y = HIWORD(lParam_);
		break;

	case WM_SYSKEYDOWN: // システムキー押下開始時
	case WM_SYSKEYUP:   // システムキー終了時
		MessageBox(NULL, "システムキー入力", NULL, MB_OK);
		break;

	}

	return DefWindowProc(windowHandle_, messageId_, wParam_, lParam_);
}

namespace Device{
	bool MakeWindow(int x_, int y_, std::string name_) {

		DxManager* mgr = DxManager::GetInstance();


		HWND hWnd;
		WNDCLASSEX window_class = {
			sizeof(WNDCLASSEX),									// 構造体のサイズ
			CS_HREDRAW | CS_VREDRAW,							// クラスのスタイル
			WindowProc,											// ウィンドウプロシージャ
			0,													// 補助メモリ
			0,													// 補助メモリ
			GetModuleHandle(nullptr),							// このプログラムのインスタンスハンドル
			LoadIcon(nullptr, IDI_APPLICATION),					// アイコン画像
			LoadCursor(NULL, IDC_ARROW),						// カーソル画像
			NULL,												// 背景ブラシ(背景色)
			NULL,												// メニュー名
			name_.c_str(),										// クラス名									
			NULL												// 小さいアイコン
		};
		
		// 構造体の登録
		if (RegisterClassEx(&window_class) == 0)
		{
			return false;
		}

		// ウィンドウ作成
		hWnd = CreateWindow(
			name_.c_str(),
			name_.c_str(),
			(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
			0,
			0,
			x_,
			y_,
			NULL,
			NULL,
			GetModuleHandle(nullptr),
			NULL);

		if (hWnd == NULL)
		{
			return false;
		}

		if (!mgr->InitDirectX(hWnd))
		{
			return false;
		}

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);

		return true;
	}

	bool ProcessMessage() {
		MSG msg;

		//　メッセージが０では無い間
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				return false;
			}
		}
		return true;
	}

	BYTE key[INPUT_FRAME][KEYNUM];

	bool KeyTest(const BYTE k) {
		return ((k & 0x80) != 0);
	}
	bool KeyUpdate() {
		memcpy(key[KB_PRE], key[KB_CUR], sizeof(*key));
		if (GetKeyboardState(key[KB_CUR])) { return true; }
		return false;
	}
	bool KeyOn(int nVirtKey_) {
		return KeyTest(key[KB_CUR][nVirtKey_]);
	}
	bool KeyPress(int nVirtKey_) {
		return KeyTest(key[KB_CUR][nVirtKey_]) && !KeyTest(key[1][nVirtKey_]);
	}
	bool KeyOff(int nVirtKey_) {
		return !KeyTest(key[KB_CUR][nVirtKey_]) && KeyTest(key[1][nVirtKey_]);
	}

	t_Vec2 GetMousePoint() {

		t_Vec2 vec(((float)pt.end.x),((float)pt.end.y));
		return vec;
	}

	t_Vec2 GetPointOnDrag() {
		t_Vec2 vec(((float)pt.start.x), ((float)pt.start.y));
		return vec;
	}
	
	const bool MouseOn() 
	{
		
		if (is_click)
		{
			return true;
		}
			
		return false;
		
	}
	
	const bool MousePress() 
	{
		
		if (is_click)
		{
			is_click = false;
			return true;
		}
			
		return false;
		
	}
}

