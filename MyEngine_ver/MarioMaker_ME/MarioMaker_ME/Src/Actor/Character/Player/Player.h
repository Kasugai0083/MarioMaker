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
	Player(Pos2 pos_, std::string fileName_) { Init(pos_, fileName_); };
	~Player() override;		//!< �f�X�g���N�^	

	void Init(Pos2 pos_, std::string fileName_) override;	//!< ������
	void Update() override;									//!< �X�V
	void Draw(std::string fileName_) override;				//!< �`��
	void Release() override;								//!< ���

private:
	int m_count;
	bool m_short_jump;
};

