#pragma once

/**
* @file Size.h
* @brief �f�[�^�̃T�C�Y(���A�c)��ۑ��ł���\���̂̐錾
*/
#ifndef SIZE_H_
#define SIZE_H_

//=====================================================================//
//! �T�C�Y�f�[�^�p�\����
//=====================================================================//
struct t_Size
{
	/** Constructor */
	t_Size()
	{
		width = 0.0f;
		height = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] width ����
	* @param[in] height �c��
	*/
	t_Size(float width_, float height_)
	{
		width = width_;
		height = height_;
	}

	/**
	* @brief Constructor
	* @param[in] size �R�s�[�p�T�C�Y�f�[�^
	*/
	t_Size(const t_Size& size)
	{
		this->width = size.width;
		this->height = size.height;
	}

	float width;		//!< ����
	float height;		//!< �c��
};

#endif
