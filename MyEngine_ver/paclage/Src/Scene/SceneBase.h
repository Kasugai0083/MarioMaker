#pragma once

#include "..//Engine/Device.h"
#include "../Engine/Graphics/DirectX.h"
#include "SceneID.h"

/**
* @brief 
* �V�[���̊��N���X
*/

class SceneBase {
public:

	//!< �R���X�g���N�^
	SceneBase()
	{
		m_state = SceneState::INIT;
		m_can_next_scene = false;
	}
	virtual ~SceneBase() {}	//!< �f�X�g���N�^

	virtual void Init() = 0; //!< ����������

	virtual void Update() = 0; //!< �X�V����

	//!< �I������
	virtual SceneID End(){ return SceneID::UNKNOWN; }
	
	virtual void Draw() {}; //!< �`�揈��

	/**
	* @brief ��ԑJ�ڏ���
	* @return ���̃V�[��ID��Ԃ�
	*/
	virtual SceneID Control() { return SceneID::UNKNOWN; }

	void SwitchEnd() 
	{
		if (m_can_next_scene)
		{ 
			m_can_next_scene = false;
			m_state = SceneState::END;
		}
	}
protected:
	SceneState m_state;		//!< ���݂̃V�[���󋵂�ۊ�
	bool m_can_next_scene;	//!< ���̃V�[���Ɉڂ邩�ǂ���
};