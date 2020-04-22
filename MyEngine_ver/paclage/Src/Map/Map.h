#pragma once

#include "../Engine/Graphics/Drawer2D.h"
#include "..//Data/GameData.h"
#include "../Actor/ActorManager.h"
#include "../Camera/Camera.h"

#include <vector>
#include <string>

/**
* @brief
* �}�b�v�Ɠo�ꂷ��A�N�^�[�𐧌䂷��N���X
*/



class MapManager
{
public:
	MapManager() 	//!< �R���X�g���N�^
	{
	};
	~MapManager();	//!< �f�X�g���N�^

	void Init(std::string name_);	//!< ������
	void Update();	//!< �X�V
	void Draw();	//!< �`��
	void Release();	//!< ���

	bool GetHasClear() { return m_has_clear; }
private:
	std::string m_map_name;		//!< �}�b�v�̖��O
	float m_gravity;			//!< �}�b�v�̏d��
	ActorManager m_actor_mgr;	//!< �A�N�^�[���Ǘ�
	Camera m_map_camera;		//!< �}�b�v�̃J�������
	bool m_has_clear;			//!< �}�b�v�̃N���A���
};

