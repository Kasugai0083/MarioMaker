#pragma once
#include "..//Utility/Vec2.h"
#include "..//Engine/Graphics/Drawer2D.h"

/**
* @brief 
* �Q�[���ɓo�ꂷ��(�v���C���[�E�G�l�~�[�E�u���b�N)�̊��N���X
*/

typedef struct t_ActorState {

	Pos2 pos;			//!< ���W
	float weight;		//!< �d��
	float speed;		//!< ���x
	float jump_power;	//!< �W�����v��
	float grav_accel;	//!< �d�͉����x
	bool is_jump;		//!< �W�����v�t���O�H
	t_Vec2 curr_vec;	//!< ���݂̃x�N�g�����

}t_ASta;

class ActorBase
{
public:
	ActorBase() {};				//!< �R���X�g���N�^
	virtual ~ActorBase() {};	//!< �f�X�g���N�^	

	virtual void Init(Pos2 pos_, std::string fileName_) = 0;	//!< ������
	virtual void Update() = 0;									//!< �X�V
	virtual void Draw(std::string fileName_) = 0;				//!< �`��
	virtual void Release() = 0;									//!< ���

	Pos2 GetPos() { return m_state.pos; }						//!< ���W�擾
	void SetPos(Pos2 pos_) { m_state.pos = pos_; }				//!< ���W�ύX

	void SetGrvAccel(float gravity_) { m_state.grav_accel = gravity_; }	//!< �d�͉����x�ύX

	void SetIsJump(bool jump_) { m_state.is_jump = jump_; }		//!< �W�����v�t���O�ύX

protected:
	t_ActorState m_state;		//!< �A�N�^�[�̃X�e�[�^�X
	Drawer2D m_drawer2d;		//!< �`��N���X		
};

