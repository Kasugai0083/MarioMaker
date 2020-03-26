#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Utility/Vec2.h"
#include "../Engine/Device.h"

#define FIELD_WIDHT (WIN_W * 2)	//!< �t�B�[���h�̉���
#define FIELD_HEIGHT (WIN_H * 2)	//!< �t�B�[���h�̏c��

/** @brief �J�������W�擾�֐� */
t_Vec2 GetCameraPos();

/**
* @brief ���[���h���W => �X�N���[�����W�ϊ��֐�@n
* �����œn���ꂽ���W���X�N���[�����W�ɕϊ�����
* @return �ϊ���̍��W
* @param[in] pos �ϊ��O�̍��W
*/
t_Vec2 ConvertPositionWorldToScreen(t_Vec2 pos);

/**
* @brief �J�����X�V�֐�@n
* �J�������X�V����
*/
void UpdateCamera();

#endif
