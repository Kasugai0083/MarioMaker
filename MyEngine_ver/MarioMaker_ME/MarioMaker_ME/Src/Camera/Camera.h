#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Utility/Vec2.h"
#include "../Utility/Grid.h"
#include "../Engine/Device.h"
#include "../Data/GameData.h"

class Camera
{

public:
	Camera() { Init(t_Vec2(WIN_W / 2.0f, WIN_H / 2.0f)); }
	Camera(t_Vec2 pos_) { Init(pos_); }

	void Init(t_Vec2 pos_);
	void Update(t_Vec2 pos_);

	t_Vec2 ConvertScreen(t_Vec2 pos_);
	t_Vec2 GetPosition() { return m_pos; }

	t_Grid GetFieldSize() { return m_field_size; }
	
	void SetMapSize(t_Grid size_) { m_map_size = size_; }

private:
	t_Vec2 m_pos;
	t_Grid m_map_size;
	t_Grid m_field_size;

};

#endif
