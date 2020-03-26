#pragma once

#include "../../ActorBase.h"

/**
* @brief
* �G�l�~�[�𐧌䂷��N���X
*/

class Enemy :
	public ActorBase
{
public:
	/**
	* @brief �R���X�g���N�^\n�����̒l�Ɋ�Â��ď���������
	* @param pos_ ������������W
	* @param fileName_ �ݒ肷��摜��
	*/
	Enemy(Pos2 pos_, std::string fileName_) { Init(pos_, fileName_); };
	~Enemy() override;	//!< �f�X�g���N�^

	void Init(Pos2 pos_, std::string fileName_) override;	//!< ������
	void Update() override;									//!< �X�V
	void Draw(std::string fileName_, Camera* camera_)override;	//!< �`��
	void Release() override;								//!< ���

private:

};

