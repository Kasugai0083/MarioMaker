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
		
		m_name_list = nameList_;
		Init(pos_);
		m_camera_ptr = new Camera();
		m_camera_ptr = acs->GetCurrCameraPTR();
	};
	//Player(Pos2 pos_, std::string fileName_) 
	//{ 
	//	Accessor* acs = Accessor::GetInstance();
	//	if (!acs) { return; };

	//	Init(pos_, fileName_);
	//	m_camera_ptr = new Camera();
	//	m_camera_ptr = acs->GetCurrCameraPTR();
	//};
	~Player() override;		//!< �f�X�g���N�^	

	void Init(Pos2 pos__) override;	//!< ������
	void Init(Pos2 pos_, std::string fileName_) override;	//!< ������
	void Update() override;									//!< �X�V
	void Draw() override;				//!< �`��
	void Draw(std::string fileName_, Camera* camera_) override;				//!< �`��
	void Release() override;								//!< ���

private:
	int m_count;
	bool m_short_jump;

	Camera* m_camera_ptr;

	// ������
	std::map<std::string, std::string*> m_name_list;
};

