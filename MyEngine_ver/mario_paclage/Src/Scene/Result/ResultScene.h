#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Drawer2D.h"


/**
* @brief
* ���U���g�V�[���̏���
*/

namespace {
	Pos3 pos1(20.f, 50.f, 0.f);
	Pos3 pos2(50.f, 0.f, 0.f);
}

class ResultScene :public SceneBase
{
public:
	//!< �R���X�g���N�^
	ResultScene(){}
	~ResultScene()override;		//!< �f�X�g���N�^
private:
	void Init()override;		//!< �V�[���̏�����
	void Update()override;		//!< �V�[���̍X�V
	SceneID End()override;		//!< �V�[���̉��
	SceneID Control()override;	//!< �V�[���̐���
	void Draw()override;		//!< �V�[���̕`��
private:
	Drawer2D m_drawer2d;			//!< �t�H���g�\���Ɏg�p
	

};

