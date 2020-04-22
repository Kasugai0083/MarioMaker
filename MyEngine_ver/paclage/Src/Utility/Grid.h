#pragma once
#pragma once

/**
* @file Grid.h
* @brief 2Dの情報を保存できる構造体の宣言(整数型)
*/

//=====================================================================//
//! Grid用構造体(2D版)
//=====================================================================//
struct t_Grid
{
	/** Constructor */
	t_Grid()
	{
		x = 0;
		y = 0;
	}

	/**
	* @brief Constructor
	* @param[in] x 横幅
	* @param[in] y 縦幅
	*/
	t_Grid(int x_, int y_)
	{
		x = x_;
		y = y_;
	}

	/**
	* @brief Constructor
	* @param[in] Vec2 コピー用Vec2データ
	*/
	t_Grid(const t_Grid& size)
	{
		this->x = size.x;
		this->y = size.y;
	}

	t_Grid operator + (const t_Grid& siz_)
	{
		t_Grid val;
		val.x = this->x + siz_.x;
		val.y = this->y + siz_.y;
		return val;
	}
	t_Grid operator - (const t_Grid& siz_)
	{
		t_Grid val;
		val.x = this->x - siz_.x;
		val.y = this->y - siz_.y;
		return val;
	}
	t_Grid operator * (const t_Grid& siz_)
	{
		t_Grid val;
		val.x = this->x * siz_.x;
		val.y = this->y * siz_.y;
		return val;
	}
	t_Grid operator / (const t_Grid& siz_)
	{
		t_Grid val;
		val.x = this->x / siz_.x;
		val.y = this->y / siz_.y;
		return val;
	}


	t_Grid& operator += (const t_Grid& siz_)
	{
		this->x += siz_.x;
		this->y += siz_.y;
		return *this;
	}

	int x;	//!< X値
	int y;	//!< Y値
};
