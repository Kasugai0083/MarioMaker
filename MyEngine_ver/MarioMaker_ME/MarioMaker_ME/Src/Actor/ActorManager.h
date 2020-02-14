#pragma once

#include "ActorBase.h"
#include "Block/Block.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Player.h"

/**
* @brief
* �Q�[���V�[���œo�ꂷ��(�v���C���[�E�G�l�~�[�E�u���b�N)��\n
* ���䂷��N���X
*/
class ActorManager
{
public:
	ActorManager()	//!< �R���X�g���N�^
	{
		Init();
	}
	~ActorManager() //!< �f�X�g���N�^
	{
		Release();
	}

	void Init();	//!< ������
	void Update();	//!< �X�V
	void Draw();	//!< �`��
	void Release();	//!< ���

private:
	int* m_map[23][40];	//!< Csv�̏���ǂݍ��ݗp
	std::map<std::string, std::vector<ActorBase*>> m_actors;	//!< �A�N�^�[�̎��̂��Ǘ�
};