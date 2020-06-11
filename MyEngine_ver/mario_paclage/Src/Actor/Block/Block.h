#pragma once

#include "..//ActorBase.h"

/**
* @brief
* �u���b�N�𐧌䂷��N���X
*/

enum class BlockType
{
	NORMAL,
	ICE,
	ETC
};

class Block : public ActorBase
{
public:
	/**
	* @brief �R���X�g���N�^\n�����̒l�Ɋ�Â��ď���������
	* @param pos_ ������������W
	* @param fileName_ �ݒ肷��摜��
	*/
	Block(Pos2 pos_, std::map<std::string, std::string*> nameList_)
	{
		Accessor* acs = Accessor::GetInstance();
		if (!acs) { return; };
		m_camera_ptr = new Camera();
		m_camera_ptr = acs->GetCurrCameraPTR();

		m_name_list = nameList_;
		Init(pos_);
	};


	~Block() override;	//!< �f�X�g���N�^	

	void Init(Pos2 pos_)override;		//!< ������
	void Update()override;										//!< �X�V
	void Draw()override;	//!< �`��
	void Release()override;										//!< ���

private:

	float m_reaction; //!< @brief ����p�̗�
	BlockType m_type;
};

