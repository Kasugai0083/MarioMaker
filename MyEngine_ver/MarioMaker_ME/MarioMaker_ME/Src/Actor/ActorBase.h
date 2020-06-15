#pragma once
#include "..//Utility/Vec2.h"
#include "..//Engine/Graphics/Drawer2D.h"
#include "../Data/GameData.h"
#include "../Camera/Camera.h"
#include "../Data/Accessor.h"
/**
* @brief 
* �Q�[���ɓo�ꂷ��(�v���C���[�E�G�l�~�[�E�u���b�N)�̊��N���X
*/

typedef struct t_ActorState {

	Pos2 pos;			//!< ���W
	Pos2 old_pos;		//!< �Â����W���(�v�Z�p)
	t_Size size;		//!< �T�C�Y
	float weight;		//!< �d��
	float speed;			//!< ���x
	float jump_power;		//!< �W�����v��
	float accel;			//!< �����x
	float grav_accel;		//!< �d�͉����x
	bool has_on_ground;	//!< ���n���Ă��邩�ǂ���
	t_Vec2 curr_vec;	//!< ���݂̃x�N�g�����
	bool is_death;		//!< ���S����(������)
	bool can_next_scene; //!< ���Âꂩ�̃A�N�^�[�� true �ɂȂ�Ύ��̃V�[����

}t_ASta;

class ActorBase
{
public:
	ActorBase() {};				//!< �R���X�g���N�^
	virtual ~ActorBase() {};	//!< �f�X�g���N�^	

	virtual void Init(Pos2 pos_) = 0;	//!< ������
	virtual void Update() = 0;									//!< �X�V
	virtual void Draw() = 0;				//!< �`��
	virtual void Release() = 0;									//!< ���

	Pos2 GetPos() { return m_state.pos; }						//!< ���W�擾
	void SetPos(Pos2 pos_) { m_state.pos = pos_; }				//!< ���W�ύX

	void SetAccel(float accel_) { m_state.accel = accel_; }	//!< �����x�ύX

	void SetGrvAccel(float gravity_) { m_state.grav_accel = gravity_; }	//!< �d�͉����x�ύX
	float GetGrvAccel() { return m_state.grav_accel; }					//!< �d�͉����x�̎擾

	void SetHasOnGround(bool has_) { m_state.has_on_ground = has_; }	//!< �W�����v�t���O�ύX
	bool GetHasOnGround() { return m_state.has_on_ground; }			//!< �W�����v�t���O�̎擾

	void SetCurrVec(t_Vec2 vec_)	//!< �x�N�g���̕ύX 
	{ 
		if (vec_.x != 0.f) { m_state.curr_vec.x = vec_.x; }
		if (vec_.y != 0.f) { m_state.curr_vec.y = vec_.y; }
	}

	void SetIsDeath(bool death_) { m_state.is_death = death_; }

	t_Vec2 GetCurrVec() { return m_state.curr_vec; }			//!< �W�����v�t���O�̎擾

	t_ASta GetState() { return m_state; }			//!< �W�����v�t���O�̎擾

protected:

	t_ActorState m_state;		//!< �A�N�^�[�̃X�e�[�^�X
	Drawer2D m_drawer2d;		//!< �`��N���X		
	// ������
	std::map<std::string, std::string*> m_name_list;
	Camera* m_camera_ptr;

};

