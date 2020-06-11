#pragma once

#pragma once

/**
* @file Vec.h
* @brief 3D�̏���ۑ��ł���\���̂̐錾
*/

//=====================================================================//
//! Vector�p�\����(3D��)
//=====================================================================//
typedef struct Vec3
{
	/** Constructor */
	Vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] x ����
	* @param[in] y �c��
	* @param[in] z ���s
	*/
	Vec3(float x_, float y_, float z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	/**
	* @brief Constructor
	* @param[in] Vec3 �R�s�[�pVec2�f�[�^
	*/
	Vec3(const Vec3& size)
	{
		this->x = size.x;
		this->y = size.y;
		this->z = size.z;
	}

	float x;	//!< X�l
	float y;	//!< Y�l
	float z;	//!< Z�l
}Pos3;
