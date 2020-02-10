#ifndef DIRECTX_H_
#define DIRECTX_H_

#include "../../Utility/SingletonTemplate.h"
#include "..//..//Utility/Size.h"
#include "../../Utility/Vec3.h"
#include "../../Utility/Vec2.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>

/**
* @brief 
* DirectX���������E�Ǘ�����N���X
*/

/**
* Texture �̃f�[�^�ƃT�C�Y���Ǘ�����\����
*/
struct t_Texture {
	LPDIRECT3DTEXTURE9 texture_data;		//!< �e�N�X�`���f�[�^
	float width;						//!< ����
	float height;						//!< �c��
};

/**
* @brief �|���S���`��ɕK�v�Ȓ��_���
* @param pos ���W
* @param tex_pos �e�N�X�`�����W
*/
struct t_CustomVertex {

	float x, y, z;
	float rhw;
	float tu,tv;

	//D3DXVECTOR3 pos;
	//D3DXVECTOR2 tex_pos;

};

/**
* @brief �|���S���`��ɕK�v�Ȓ��_���
* @param pos ���W
* @param tex_pos_start �e�N�X�`�����W�J�n�_
* @param tex_pos_end �e�N�X�`�����W�I���_
*/
struct t_VertexPos {

	Pos2 pos;
	Pos2 tex_pos_start, tex_pos_end;

};

/**
* @enum �e�`��֐��̕`�掟�������Ă�����̂Ɏg�p
*/
enum class Dimendion {
	DIMENSION_2,
	DIMENSION_3,
};

/**
* @brief DirextX�X�e�[�^�X�\����\n
* �󂯓n�����ȗ������邽�߂ɍ\���̂ɓZ�߂�
*/
struct t_DxStatus 
{
	LPDIRECT3D9 d3d_interface;	//!< @brief DirectX�C���^�[�t�F�[�X
	
	D3DPRESENT_PARAMETERS* d3d_present_param; //!< @brief DirectX�̐ݒ�
	
	LPDIRECT3DDEVICE9 d3d_device; //!< @brief DirectX�f�o�C�X���
};

class DxManager : public Singleton<DxManager>
{
public:

	/**
	* @brief DirectX ��������
	* @param �E�B���h�E�n���h��
	* @return �������ɐ��������ꍇ => true
	*/
	bool InitDirectX(HWND windowHandle_);

	/**
	* @brief DirectX�ł̕`�����������\n
	* !�摜�o�O�F�����ُ͈�Ȃ�
	*/
	void StartDraw();

	/**
	* @brief DirectX�ł̕`��������
	*/
	void EndDraw();

	/**
	* @brief DirectX�̃X�e�[�^�X�����
	*/
	void Release();

	/**
	* @brief �t�H���g�̃f�o�C�X���쐬
	* @param �t�H���g�̑傫�����w��
	* @return �f�o�C�X�쐬�ɐ��� => true
	*/
	bool CreateFontDevice(t_Size size_);

	/**
	* @return DirectX �\���̂̃A�h���X��Ԃ�
	*/
	t_DxStatus* GetStatus() {
		if (!&m_dx_status) { return false; }
		return &m_dx_status;
	}

	/**
	* @return m_Font �̃A�h���X��Ԃ�
	*/
	LPD3DXFONT& GetFont() {
		return m_font;
	}
protected:


protected:

	t_DxStatus m_dx_status;		//!< @brief DirectX �̎��ӏ���ۊ�

	LPD3DXFONT m_font;			//!< @brief �t�H���g�̏��

private:
	friend Singleton<DxManager>;

	DxManager()
	{ 
		m_font = nullptr; 
	};
	virtual ~DxManager() {};

	DxManager(const DxManager&) = delete;
	DxManager& operator=(const DxManager&) = delete;
	DxManager(const DxManager&&) = delete;
	DxManager& operator=(const DxManager&&) = delete;
};



#endif