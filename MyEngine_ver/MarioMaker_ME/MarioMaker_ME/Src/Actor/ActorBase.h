#pragma once
#include "..//Utility/Vec2.h"
#include "..//Engine/Graphics/Drawer2D.h"

typedef struct t_ActorState {

	Pos2 pos;
	float weight;
	float speed;
	float jump_power;
	float grav_accel;
	bool is_jump;
	t_Vec2 curr_vec;

}t_ASta;

class ActorBase
{
public:
	ActorBase() {};
	virtual ~ActorBase() {};

	virtual void Init(Pos2 pos_, std::string fileName_) = 0;
	virtual void Update() = 0;
	virtual void Draw(std::string fileName_) = 0;
	virtual void Release() = 0;

	Pos2 GetPos() { return m_state.pos; }
	void SetPos(Pos2 pos_) { m_state.pos = pos_; }

	void SetGrvAccel(float gravity_) { m_state.grav_accel = gravity_; }

	void SetIsJump(bool jump_) { m_state.is_jump = jump_; }

protected:
	t_ActorState m_state;
	Drawer2D m_drawer2d;
};

