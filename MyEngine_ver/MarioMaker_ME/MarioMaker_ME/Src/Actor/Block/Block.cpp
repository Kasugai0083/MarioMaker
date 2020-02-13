#include "Block.h"
#include "..//..//Data/GameData.h"
#include "..//..//Data/Accessor.h"

Block::~Block()
{
}

void Block::Init(Pos2 pos_, std::string fileName_)
{
	m_drawer2d.LoadTexture(fileName_);

	m_state.pos.x = pos_.x;
	m_state.pos.y = pos_.y;

	m_state.weight = 0.f;
	m_state.speed = 0.f;
	m_state.jump_power = 0.f;
	m_state.grav_accel = 0.f;

	m_state.curr_vec.x = 0.f;
	m_state.curr_vec.y = 0.f;

	m_state.is_jump = false;

	m_reaction = WEIGHT * GRAVITY;
}

void Block::Update()
{
	Accessor* acs = Accessor::GetInstance();

	float gravity_power = acs->GetCurrGravity() * m_state.weight;

	m_state.pos.y += gravity_power;

}


void Block::Draw(std::string fileName_) {
	m_drawer2d.DrawTexture(m_state.pos, fileName_);
}

void Block::Release() {
	m_drawer2d.AllRelease();
}