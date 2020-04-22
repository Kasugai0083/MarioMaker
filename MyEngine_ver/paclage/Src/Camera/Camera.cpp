
#include "../Utility/Vec2.h"
#include "Camera.h"

void Camera::Init(t_Vec2 pos_) 
{
	m_pos = pos_;

}

void Camera::Update(t_Vec2 pos_)
{
	m_pos = pos_;
	m_field_size = t_Grid(m_map_size.x * (int)MAP_CHIP_SIZE, m_map_size.y * (int)MAP_CHIP_SIZE);

	bool has_small_y = false;
	bool has_small_x = false;
	if (m_field_size.y <= WIN_H) { has_small_y = true; }
	else { has_small_y = false; }
	if (m_field_size.x <= WIN_W) { has_small_x = true; }
	else { has_small_x = false; }

	t_Vec2 window_half
	{
		WIN_W / 2.0f,
		WIN_H / 2.0f
	};
	/*
		�ړ�����
			�J�����̈ړ��͈͂����͈͂ɂƂǂ߂�
			�`���FIELD�͈̔͂Ɏ��߂₷�����邽�߁A
			�E�B���h�E�̃T�C�Y���g�p���Ĕ͈͂̒������s��
	*/

	if (has_small_x)
	{
		m_pos.x = m_field_size.x / 2.f;
	}
	else
	{
		if (m_pos.x <= window_half.x)
		{
			m_pos.x = window_half.x;
		}
		else if (m_pos.x >= m_field_size.x - window_half.x)
		{
			m_pos.x = m_field_size.x - window_half.x;
		}
	}

	if (has_small_y)
	{
		m_pos.y = m_field_size.y / 2.f;
	}
	else
	{
		if (m_pos.y <= window_half.y)
		{
			m_pos.y = window_half.y;
		}
		else if (m_pos.y >= m_field_size.y - window_half.y)
		{
			m_pos.y = m_field_size.y - window_half.y;
		}
	}
}

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