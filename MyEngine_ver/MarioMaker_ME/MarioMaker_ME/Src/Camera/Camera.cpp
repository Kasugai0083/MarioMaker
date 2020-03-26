
#include "../Utility/Vec2.h"
#include "Camera.h"

// カメラ
static t_Vec2 g_CameraPos{ WIN_W / 2.0f, WIN_H / 2.0f };

void UpdateCamera()
{
	if (Device::KeyOn('I')) { g_CameraPos.y -= 1.0f; }
	else if (Device::KeyOn('K')) { g_CameraPos.y += 1.0f; }
	if (Device::KeyOn('J')) { g_CameraPos.x -= 1.0f; }
	else if (Device::KeyOn('L')) { g_CameraPos.x += 1.0f; }

	//g_CameraPos.x += 1.0f;

	//g_CameraPos.y += velocity.Y;

	t_Vec2 window_half{
		WIN_W / 2.0f,
		WIN_H / 2.0f
	};

	/*
		移動制限
			カメラの移動範囲を一定範囲にとどめる
			描画をFIELDの範囲に収めやすくするため、
			ウィンドウのサイズを使用して範囲の調整を行う
	*/
	if (g_CameraPos.x <= window_half.x)
	{
		g_CameraPos.x = window_half.x;
	}
	else if (g_CameraPos.x >= FIELD_WIDHT - window_half.x)
	{
		g_CameraPos.x = FIELD_WIDHT - window_half.x;
	}

	if (g_CameraPos.y <= window_half.y)
	{
		g_CameraPos.y = window_half.y;
	}
	else if (g_CameraPos.y >= FIELD_HEIGHT - window_half.y)
	{
		g_CameraPos.y = FIELD_HEIGHT - window_half.y;
	}

}

t_Vec2 ConvertPositionWorldToScreen(t_Vec2 pos)
{
	// カメラ座標からスクリーン座標の原点に変換する
	t_Vec2 screen_origin_position =
	{
		g_CameraPos.x - WIN_W / 2.0f,
		g_CameraPos.y - WIN_H / 2.0f
	};

	// ワールド座標からスクリーン座標に変換する
	t_Vec2 screen_position = t_Vec2(pos.x - screen_origin_position.x, pos.y - screen_origin_position.y);

	return screen_position;
}

t_Vec2 GetCameraPos()
{
	return g_CameraPos;
}

