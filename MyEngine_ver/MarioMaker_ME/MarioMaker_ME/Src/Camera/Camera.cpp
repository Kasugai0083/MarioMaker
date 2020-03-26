
#include "../Utility/Vec2.h"
#include "Camera.h"

// �J����
static t_Vec2 g_CameraPos{ WIN_W / 2.0f, WIN_H / 2.0f };

void UpdateCamera()
{
	if (Device::KeyOn(VK_UP)) { g_CameraPos.y -= 1.0f; }
	else if (Device::KeyOn(VK_DOWN)) { g_CameraPos.y += 1.0f; }
	if (Device::KeyOn(VK_LEFT)) { g_CameraPos.x -= 1.0f; }
	else if (Device::KeyOn(VK_RIGHT)) { g_CameraPos.x += 1.0f; }

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

void Camera::Init(t_Vec2 pos_) 
{
	m_pos = pos_;
}

void Camera::Update(t_Vec2 pos_)
{
	m_pos = pos_;

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
	if (m_pos.x <= window_half.x)
	{
		m_pos.x = window_half.x;
	}
	else if (m_pos.x >= FIELD_WIDHT - window_half.x)
	{
		m_pos.x = FIELD_WIDHT - window_half.x;
	}

	if (m_pos.y <= window_half.y)
	{
		m_pos.y = window_half.y;
	}
	else if (m_pos.y >= FIELD_HEIGHT - window_half.y)
	{
		m_pos.y = FIELD_HEIGHT - window_half.y;
	}
}
//void Camera::Update()
//{
//	if (Device::KeyOn(VK_UP)) { m_pos.y -= 1.0f; }
//	else if (Device::KeyOn(VK_DOWN)) { m_pos.y += 1.0f; }
//	if (Device::KeyOn(VK_LEFT)) { m_pos.x -= 1.0f; }
//	else if (Device::KeyOn(VK_RIGHT)) { m_pos.x += 1.0f; }
//
//	t_Vec2 window_half{
//		WIN_W / 2.0f,
//		WIN_H / 2.0f
//	};
//
//	/*
//		�ړ�����
//			�J�����̈ړ��͈͂����͈͂ɂƂǂ߂�
//			�`���FIELD�͈̔͂Ɏ��߂₷�����邽�߁A
//			�E�B���h�E�̃T�C�Y���g�p���Ĕ͈͂̒������s��
//	*/
//	if (m_pos.x <= window_half.x)
//	{
//		m_pos.x = window_half.x;
//	}
//	else if (m_pos.x >= FIELD_WIDHT - window_half.x)
//	{
//		m_pos.x = FIELD_WIDHT - window_half.x;
//	}
//
//	if (m_pos.y <= window_half.y)
//	{
//		m_pos.y = window_half.y;
//	}
//	else if (m_pos.y >= FIELD_HEIGHT - window_half.y)
//	{
//		m_pos.y = FIELD_HEIGHT - window_half.y;
//	}
//}

t_Vec2 Camera::ConvertScreen(t_Vec2 pos_)
{
	if (!this) { return t_Vec2(0,0); }
	// �J�������W����X�N���[�����W�̌��_�ɕϊ�����
	t_Vec2 screen_origin_position =
	{
		m_pos.x - WIN_W / 2.0f,
		m_pos.y - WIN_H / 2.0f
	};

	// ���[���h���W����X�N���[�����W�ɕϊ�����
	t_Vec2 screen_position = t_Vec2(pos_.x - screen_origin_position.x, pos_.y - screen_origin_position.y);

	return screen_position;
}