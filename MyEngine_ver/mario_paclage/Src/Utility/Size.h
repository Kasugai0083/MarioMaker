#pragma once

/**
* @file Size.h
* @brief データのサイズ(横、縦)を保存できる構造体の宣言
*/
#ifndef SIZE_H_
#define SIZE_H_

//=====================================================================//
//! サイズデータ用構造体
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
	* @param[in] width 横幅
	* @param[in] height 縦幅
	*/
	t_Size(float width_, float height_)
	{
		width = width_;
		height = height_;
	}

	/**
	* @brief Constructor
	* @param[in] size コピー用サイズデータ
	*/
	t_Size(const t_Size& size)
	{
		this->width = size.width;
		this->height = size.height;
	}

	float width;		//!< 横幅
	float height;		//!< 縦幅
};

#endif
