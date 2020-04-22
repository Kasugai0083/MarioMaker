#pragma once

#include "../../ActorBase.h"

/**
* @brief
* �v���C���[�𐧌䂷��N���X
*/

class Player :
	public ActorBase
{
public:
	/**
	* @brief �R���X�g���N�^\n�����̒l�Ɋ�Â��ď���������
	* @param pos_ ������������W
	* @param fileName_ �ݒ肷��摜��
	*/
	Player(Pos2 pos_, std::map<std::string, std::string*> nameList_)
	{ 
		Accessor* acs = Accessor::GetInstance();
		if (!acs) { return; };
		m_camera_ptr = new Camera();
		m_camera_ptr = acs->GetCurrCameraPTR();

		m_name_list = nameList_;
		Init(pos_);
	};

	~Player() override;		//!< �f�X�g���N�^	

	void Init(Pos2 pos__) override;	//!< ������
	void Update() override;									//!< �X�V
	void Draw() override;				//!< �`��
	void Release() override;								//!< ���

private:	//!< �N���X���֐�
	/**
	* @brief ���S���̃A�j���[�V����,�V�[���J�ڂɕK�v�ȃp�����[�^��ύX
	*/
	bool DeathAnimation();

private:
	int m_count;
	bool m_short_jump;

};

