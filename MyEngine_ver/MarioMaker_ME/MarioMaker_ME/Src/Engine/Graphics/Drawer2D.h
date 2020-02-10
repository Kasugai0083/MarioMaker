#pragma once

#include "..//..//Utility/Vec2.h"
#include "..//..//Utility/Vec3.h"
#include "..//..//Utility/Size.h"
#include "DirectX.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <map>
#include <vector>


/**
* @brief
* 2D�|���S���p�̉摜��ۑ��E�`�悷��N���X
*/

struct t_LineDesc;

class Drawer2D
{
public:

	/**
	* @brief �e�N�X�`����\��t�����|���S����`�悷��
	* @param v_ �|���S���̒��_��� �� �e�N�X�`���̍��W���
	* @param fileName_ m_ptr_tex_list �̗v�f
	*/
	void DrawTexture(t_VertexPos v_, std::string fileName_);


	/**
	* @brief m_ptr_tex_list �Ƀe�N�X�`���������\n
	* �ǂݍ��݂Ɏ��s�����ꍇ�A�G���[���b�Z�[�W��Ԃ�
	* @param fileName_ �v�f�ԍ����w��
	*/
	void LoadTexture(std::string fileName_) {
		if (!CreateTexture(fileName_)) {
			std::string msg = " �̓ǂݍ��݂Ɏ��s";
			std::string pop_msg = fileName_ + msg;

			MessageBox(NULL, pop_msg.c_str(), NULL, MB_OK);
		}
	}

	/**
	* @brief �e�N�X�`�������擾
	* @return �e�N�X�`�����̃|�C���^��Ԃ�
	*/
	t_Texture* GetTexture(std::string fileName_) { return m_ptr_tex_list[fileName_]; }


	/**
	* @brief DrawTextA �Ńe�L�X�g��\��\n
	* DrawTextA �̓s����AZ���͐ݒ�ł��Ȃ�
	* @param pos_ �e�L�X�g�̍��W
	* @param text_ �e�L�X�g�̓��e
	*/
	void DrawFont(t_Vec2 pos_, std::string text_);

	/**
	* @brief �w�肵���e�N�X�`���̈�����
	* @param �̈���w��
	*/
	void Release(std::string fileName_);
	/**
	* @brief �S�Ẵe�N�X�`���̈�����
	*/
	void AllRelease();

private:
	/**
	* @brief m_ptr_tex_list �Ƀe�N�X�`���������
	* @param fileName_ �v�f�ԍ����w��
	*/
	bool CreateTexture(std::string fileName_);

private:

	std::map<std::string, t_Texture*>m_ptr_tex_list; //!< @brief �摜����ۊ�

};