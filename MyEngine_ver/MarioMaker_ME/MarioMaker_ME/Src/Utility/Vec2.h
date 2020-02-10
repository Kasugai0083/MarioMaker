#pragma once

/**
* @file Vec.h
* @brief 2Dの情報を保存できる構造体の宣言
*/

//=====================================================================//
//! Vector用構造体(2D版)
//=====================================================================//
typedef struct t_Vec2
{
	/** Constructor */
	t_Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] x 横幅
	* @param[in] y 縦幅
	*/
	t_Vec2(float x_, float y_)
	{
		x = x_;
		y = y_;
	}

	/**
	* @brief Constructor
	* @param[in] Vec2 コピー用Vec2データ
	*/
	t_Vec2(const t_Vec2& size)
	{
		this->x = size.x;
		this->y = size.y;
	}

	float x;	//!< X値
	float y;	//!< Y値
}Pos2;
