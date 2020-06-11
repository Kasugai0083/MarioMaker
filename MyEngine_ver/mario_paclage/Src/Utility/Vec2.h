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

	t_Vec2 operator + (const t_Vec2& siz_)
	{
		t_Vec2 val;
		val.x = this->x + siz_.x;
		val.y = this->y + siz_.y;
		return val;
	}
	t_Vec2 operator - (const t_Vec2& siz_)
	{
		t_Vec2 val;
		val.x = this->x - siz_.x;
		val.y = this->y - siz_.y;
		return val;
	}
	t_Vec2 operator * (const t_Vec2& siz_)
	{
		t_Vec2 val;
		val.x = this->x * siz_.x;
		val.y = this->y * siz_.y;
		return val;
	}
	t_Vec2 operator / (const t_Vec2& siz_)
	{
		t_Vec2 val;
		val.x = this->x / siz_.x;
		val.y = this->y / siz_.y;
		return val;
	}


	t_Vec2& operator += (const t_Vec2& siz_)
	{
		this->x += siz_.x;
		this->y += siz_.y;
		return *this;
	}

	float x;	//!< X値
	float y;	//!< Y値
}Pos2;
