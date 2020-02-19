#pragma once

#include "..//ActorBase.h"

/**
* @brief
* �u���b�N�𐧌䂷��N���X
*/

class Block : public ActorBase
{
public:
	/**
	* @brief �R���X�g���N�^\n�����̒l�Ɋ�Â��ď���������
	* @param pos_ ������������W
	* @param fileName_ �ݒ肷��摜��
	*/
	Block(Pos2 pos_, std::string fileName_) 
	{
		Init(pos_,fileName_);
	};
	~Block() override;	//!< �f�X�g���N�^	

	void Init(Pos2 pos_, std::string fileName_)override;	//!< ������
	void Update()override;									//!< �X�V
	void Draw(std::string fileName_)override;				//!< �`��
	void Release()override;									//!< ���

private:

	float m_reaction; //!< @brief ����p�̗�

};

