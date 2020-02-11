#include "Player.h"
#include "..//..//..//Data/Accessor.h"

Player::~Player()
{
}

void Player::Init(Pos2 pos_, std::string fileName_)
{
	m_drawer2d.LoadTexture(fileName_);

	m_state.pos.x = pos_.x;
	m_state.pos.y = pos_.y;

	m_state.weight = 1.f;
	m_state.speed = 3.f;
	m_state.jump_power = 10.f;

	m_state.curr_vec.x = 0.f;
	m_state.curr_vec.y = 0.f;
	

}

void Player::Update()
{
	Accessor* acs = Accessor::GetInstance();

	float gravity_power = acs->GetGravity() * m_state.weight;

	m_state.pos.y += gravity_power;

}

void Player::Draw(std::string fileName_)
{
	m_drawer2d.DrawTexture(m_state.pos, fileName_);
}

void Player::Release()
{
	m_drawer2d.AllRelease();
}