#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Utility/Vec2.h"
#include "../Engine/Device.h"

#define FIELD_WIDHT (WIN_W * 2)	//!< フィールドの横幅
#define FIELD_HEIGHT (WIN_H * 2)	//!< フィールドの縦幅

/** @brief カメラ座標取得関数 */
t_Vec2 GetCameraPos();

/**
* @brief ワールド座標 => スクリーン座標変換関数@n
* 引数で渡された座標をスクリーン座標に変換する
* @return 変換後の座標
* @param[in] pos 変換前の座標
*/
t_Vec2 ConvertPositionWorldToScreen(t_Vec2 pos);

/**
* @brief カメラ更新関数@n
* カメラを更新する
*/
void UpdateCamera();




class Camera
{

public:
	Camera() { Init(t_Vec2(WIN_W / 2.0f, WIN_H / 2.0f)); }
	Camera(t_Vec2 pos_) { Init(pos_); }

	void Init(t_Vec2 pos_);
	void Update();

	t_Vec2 ConvertScreen(t_Vec2 pos_);
	t_Vec2 GetPosition() { return m_pos; }
	
	void SetCameraPosition(t_Vec2 pos_) { if (!this) { return; } m_pos = pos_; };

private:
	t_Vec2 m_pos;

};

#endif
