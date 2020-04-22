#pragma once
#pragma once

/**
* @file Grid.h
* @brief 2D�̏���ۑ��ł���\���̂̐錾(�����^)
*/

//=====================================================================//
//! Grid�p�\����(2D��)
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
	* @param[in] x ����
	* @param[in] y �c��
	*/
	t_Grid(int x_, int y_)
	{
		x = x_;
		y = y_;
	}

	/**
	* @brief Constructor
	* @param[in] Vec2 �R�s�[�pVec2�f�[�^
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

	int x;	//!< X�l
	int y;	//!< Y�l
};
