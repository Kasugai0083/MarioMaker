#pragma once
#include "..//Utility/Vec2.h"
#include "..//Engine/Graphics/Drawer2D.h"

typedef struct t_ActorState {

	Pos2 pos;
	float weight;
	float speed;
	float jump_power;
	float grav_accel;
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

protected:
	t_ActorState m_state;
	Drawer2D m_drawer2d;
};

