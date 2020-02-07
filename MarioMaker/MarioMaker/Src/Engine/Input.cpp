#include "Input.h"
#include "../Utility/Vec.h"
#include "Window.h"
#include <Windows.h>
#include <dinput.h>
//#include "DirectX.h"
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//グローバル変数
static LPDIRECTINPUT8 g_InputInterface;
static LPDIRECTINPUTDEVICE8 g_KeyDevice;
static LPDIRECTINPUTDEVICE8 g_MouseDevice;		//!< DIRECTINPUTDEVICE8のポインタ

static DIMOUSESTATE g_PrevMouseState;			//!< マウスの１フレーム前の入力情報
static DIMOUSESTATE g_CurrentMouseState;		//!< マウスの現在の入力情報
static Vec2 g_MousePos;
static Vec2 g_MouseMoveVec;

// マウスの更新
void UpdateMouse();

#define MOUSE_ON_VALUE (0x80)		// オン状態の値

// @brief 入力状態の種類
enum INPUT_STATE
{
	NOT_PUSH,		//押されていない
	PUSH_DOWN,		//押された瞬間
	PUSH,			//押されている
	PUSH_UP,		//離した瞬間
};

//ライブラリ側のキー情報配列
int g_KeyInfo[] = {
	DIK_ESCAPE,
	DIK_SPACE,
	DIK_UP,
	DIK_DOWN,
	DIK_RIGHT,
	DIK_LEFT,
	DIK_A,
	DIK_W,
	DIK_S,
	DIK_D,
	DIK_RETURN,
	DIK_LCONTROL,
};

//キーの状態を保持するグローバル変数
static INPUT_STATE g_InputState[KEY_INFO::MAX_KEY_INFO];

bool InitInput()
{
	HRESULT hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)& g_InputInterface, NULL);

	if (FAILED(hr))
	{
		MessageBox(GetWindowHandle(), (char*)"error", (char*)"errorA", MB_OK);
		return false;
	}

	hr = g_InputInterface->CreateDevice(GUID_SysKeyboard, &g_KeyDevice, NULL);

	if (FAILED(hr))
	{
		MessageBox(GetWindowHandle(), (char*)"error", (char*)"errorB", MB_OK);
		return false;
	}

	hr = g_KeyDevice->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(hr))
	{
		MessageBox(GetWindowHandle(), (char*)"error", (char*)"errorC", MB_OK);
		return false;
	}

	hr = g_KeyDevice->SetCooperativeLevel(GetWindowHandle(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	if (FAILED(hr))
	{
		MessageBox(GetWindowHandle(), (char*)"error", (char*)"errorD", MB_OK);
		return false;
	}

	hr = g_KeyDevice->Acquire();

	// マウス用にデバイスオブジェクトを作成
	if (FAILED(g_InputInterface->CreateDevice(GUID_SysMouse, &g_MouseDevice, nullptr)))
	{
		// デバイスの作成に失敗
		return false;
	}

	// データフォーマットを設定
	if (FAILED(g_MouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		// データフォーマットに失敗
		return false;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(g_MouseDevice->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME.c_str(), nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		// モードの設定に失敗
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED(g_MouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return false;
	}

	// 入力制御開始
	g_MouseDevice->Acquire();

	ZeroMemory(&g_CurrentMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&g_PrevMouseState, sizeof(DIMOUSESTATE));

	return true;
}

void ReleaseInput()
{
	g_KeyDevice->Unacquire();
	g_KeyDevice->Release();
	g_InputInterface->Release();

	if (g_MouseDevice != nullptr)
	{
		g_MouseDevice->Release();
		g_MouseDevice = nullptr;
	}

	if (g_InputInterface != nullptr)
	{
		g_InputInterface->Release();
		g_InputInterface = nullptr;
	}
}

void KeyStateUpdate()
{
	BYTE Key[256];
	HRESULT hr = g_KeyDevice->GetDeviceState(256, Key);

	if (FAILED(hr))
	{
		return;
	}

	for (int i = 0; i < MAX_KEY_INFO; i++)
	{
		if (Key[g_KeyInfo[i]] & 0x80)
		{
			if (g_InputState[i] == INPUT_STATE::NOT_PUSH || g_InputState[i] == INPUT_STATE::PUSH_UP)
			{
				g_InputState[i] = INPUT_STATE::PUSH_DOWN;
			}
			else
			{
				g_InputState[i] = INPUT_STATE::PUSH;
			}
		}
		else
		{
			if (g_InputState[i] == INPUT_STATE::PUSH || g_InputState[i] == INPUT_STATE::PUSH_DOWN)
			{
				g_InputState[i] = INPUT_STATE::PUSH_UP;
			}
			else
			{
				g_InputState[i] = INPUT_STATE::NOT_PUSH;
			}
		}
	}
}

bool GetKey(KEY_INFO key)
{
	return (g_InputState[key] == INPUT_STATE::PUSH);
}

bool GetKeyDown(KEY_INFO key)
{
	return (g_InputState[key] == INPUT_STATE::PUSH_DOWN);
}

bool GetKeyUp(KEY_INFO key)
{
	return (g_InputState[key] == INPUT_STATE::PUSH_UP);
}

void UpdateInput()
{
	UpdateMouse();

	g_PrevMouseState = g_CurrentMouseState;
	// マウスの状態を取得します
	HRESULT	hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	if (FAILED(hr))
	{
		g_MouseDevice->Acquire();
		hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	}
}

bool OnMouseDown(MouseButton button_type)
{
	if (!(g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE) &&
		g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

bool OnMousePush(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

bool OnMouseUp(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		!(g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE))
	{
		return true;
	}

	return false;
}

void UpdateMouse()
{
	Vec2 prev = g_MousePos;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(FindWindowA(TEXT("XFileDraw"), nullptr), &p);

	g_MousePos.X = (float)p.x;
	g_MousePos.Y = (float)p.y;

	g_MouseMoveVec.X = g_MousePos.X - prev.X;
	g_MouseMoveVec.Y = g_MousePos.Y - prev.Y;
}

Vec2 GetMousePos()
{
	return g_MousePos;
}