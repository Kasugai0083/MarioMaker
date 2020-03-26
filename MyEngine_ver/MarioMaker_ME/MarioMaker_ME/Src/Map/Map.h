#pragma once

#include "../Engine/Graphics/Drawer2D.h"
#include "..//Data/GameData.h"
#include "../Actor/ActorManager.h"
#include "../Camera/Camera.h"

#include <vector>

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

	void Init();	//!< ������
	void Update();	//!< �X�V
	void Draw();	//!< �`��
	void Release();	//!< ���

private:
	float m_gravity;			//!< �}�b�v�̏d��
	ActorManager m_actor_mgr;	//!< �A�N�^�[���Ǘ�
	Camera m_map_camera;
};

