#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Drawer2D.h"


/**
* @brief
* �^�C�g���V�[���̏���
*/

class TitleScene :public SceneBase
{
public:
	TitleScene();			//!< �R���X�g���N�^
	~TitleScene()override;	//!< �f�X�g���N�^

private:
	void Init()override;	//!< �V�[���̏�����
	void Update()override;	//!< �V�[���̍X�V
	SceneID End()override;	//!< �V�[���̉��
	SceneID Control();		//!< �V�[���̐���
	void Draw()override;	//!< �V�[���̕`��
private:

	Drawer2D m_drawer2d;		//!< �t�H���g�\���Ɏg�p
};

