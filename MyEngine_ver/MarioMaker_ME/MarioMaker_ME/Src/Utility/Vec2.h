#pragma once

/**
* @file Vec.h
* @brief 2D�̏���ۑ��ł���\���̂̐錾
*/

//=====================================================================//
//! Vector�p�\����(2D��)
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
	* @param[in] x ����
	* @param[in] y �c��
	*/
	t_Vec2(float x_, float y_)
	{
		x = x_;
		y = y_;
	}

	/**
	* @brief Constructor
	* @param[in] Vec2 �R�s�[�pVec2�f�[�^
	*/
	t_Vec2(const t_Vec2& size)
	{
		this->x = size.x;
		this->y = size.y;
	}

	float x;	//!< X�l
	float y;	//!< Y�l
}Pos2;
