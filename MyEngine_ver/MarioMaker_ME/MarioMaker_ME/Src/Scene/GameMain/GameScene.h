#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Drawer2D.h"


/**
* @brief
* �Q�[�����C���̃V�[������
*/

class GameScene : public SceneBase
{
public:
	//!< �R���X�g���N�^
	GameScene() {};
	~GameScene()override;		//!< �f�X�g���N�^
private:
	void Init()override;		//!< �V�[���̏�����
	void Update()override;		//!< �V�[���̍X�V
	SceneID End()override;		//!< �V�[���̉��
	SceneID Control()override;	//!< �V�[���̐���
	void Draw()override;		//!< �V�[���̕`��
private:
	Drawer2D m_drawer2d;			//!< �t�H���g�\���Ɏg�p
};

