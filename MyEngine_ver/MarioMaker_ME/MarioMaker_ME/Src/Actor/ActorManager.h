#pragma once

#include "ActorBase.h"
#include "Block/Block.h"
#include "Goal/Goal.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Player.h"
#include "../Camera/Camera.h"

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
		m_camera_ptr = new Camera();
	}
	~ActorManager() //!< �f�X�g���N�^
	{
		Release();
	}

	void Init(std::string map_name_);	//!< ������
	void Update();	//!< �X�V
	void Draw();	//!< �`��
	void Release();	//!< ���

	void GetCameraPTR(Camera* camera_) { m_camera_ptr = camera_; } //!< �J���������擾
	void GetClearPTR(bool* clear_) { m_clear_ptr = clear_; } //!< �J���������擾
private:
	/**
	* �O���Ŏg�p���Ȃ��֐��Q
	*/

	void PlayerAndBlockCollide();
	void PlayerAndGoalCollide();

private:
	int* m_map[MAX_MAP_H][MAX_MAP_W];	//!< Csv�̏���ǂݍ��ݗp
	std::map<std::string, std::vector<ActorBase*>> m_actors;	//!< �A�N�^�[�̎��̂��Ǘ�

	Camera* m_camera_ptr; //!< �}�b�v�̃J���������擾
	bool* m_clear_ptr;	  //!< �}�b�v�̃N���A�����擾
};