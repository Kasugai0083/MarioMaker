#pragma once

#include "..//Utility/Vec2.h"
#include <windows.h>
#include <string>

/**
* @brief �E�B���h�E�ƃ}�E�X���䂷��֐��Q
*/

const int WIN_W = 640;
const int WIN_H = 480;

namespace Device{
	
	/**
	* @brief �E�B���h�E���쐬����
	* @param x_ X���̃T�C�Y
	* @param y_ Y���̃T�C�Y
	* @param name_ �E�B���h�E�̃N���X��
	*/
	bool MakeWindow(int x_, int y_, std::string name_);

	/**
	* @brief ���b�Z�[�W����
	*/ 
	bool ProcessMessage();

	/**
	* @brief �L�[�{�[�h���͏�Ԃ��Ď�
	*/
	bool KeyUpdate();

	/**
	* @brief �L�[�{�[�h���͏�Ԃ��擾
	* @param n_virtKey ���̓L�[�� char (�啶��)�Ŏw��
	* @return �L�[�{�[�h�����͂���Ă��鎞 => true
	*/
	bool KeyOn(int nVirtKey_);

	/**
	* @brief �L�[�{�[�h���͎��̏�Ԃ��擾
	* @param n_virtKey ���̓L�[�� char (�啶��)�Ŏw��
	* @return �L�[�{�[�h�����͂��ꂽ�� => true
	*/
	bool KeyPress(int nVirtKey_);

	/**
	* @brief �L�[�{�[�h���͂�b�������̏�Ԃ��擾
	* @param n_virtKey ���̓L�[�� char (�啶��)�Ŏw��
	* @return �L�[�{�[�h���͂��������ꂽ�� => true
	*/
	bool KeyOff(int nVirtKey_);

	/**
	* @brief ���݂̃}�E�X���W���擾�H
	* @return �}�E�X�� X���W �� Y���W ��Ԃ�
	*/
	t_Vec2 GetMousePoint();

	/**
	* @brief �N���b�N���̃}�E�X���W���擾�H
	* @return �}�E�X�� X���W �� Y���W ��Ԃ�
	*/
	t_Vec2 GetPointOnDrag();

	/**
	* @brief �}�E�X���N���b�N���ꂽ���ǂ����𔻒�
	* @return �}�E�X���N���b�N���ꂽ�ꍇ => true
	*/
	const bool HasClickOnMouse();
}
