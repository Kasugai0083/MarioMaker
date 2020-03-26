
#include "../Utility/Vec2.h"
#include "Camera.h"

// �J����
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
		�ړ�����
			�J�����̈ړ��͈͂����͈͂ɂƂǂ߂�
			�`���FIELD�͈̔͂Ɏ��߂₷�����邽�߁A
			�E�B���h�E�̃T�C�Y���g�p���Ĕ͈͂̒������s��
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
	// �J�������W����X�N���[�����W�̌��_�ɕϊ�����
	t_Vec2 screen_origin_position =
	{
		g_CameraPos.x - WIN_W / 2.0f,
		g_CameraPos.y - WIN_H / 2.0f
	};

	// ���[���h���W����X�N���[�����W�ɕϊ�����
	t_Vec2 screen_position = t_Vec2(pos.x - screen_origin_position.x, pos.y - screen_origin_position.y);

	return screen_position;
}

t_Vec2 GetCameraPos()
{
	return g_CameraPos;
}

