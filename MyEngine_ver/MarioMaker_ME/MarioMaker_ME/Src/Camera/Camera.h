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

#endif
