#include "Player.h"
#include "..//..//..//Data/Accessor.h"
#include "../../../Engine/Device.h"

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
	m_state.jump_power = 5.f;
	m_state.grav_accel = 0.f;

	m_state.curr_vec.x = 0.f;
	m_state.curr_vec.y = 0.f;
	
	m_state.is_jump = false;
}

void Player::Update()
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; }

	m_state.pos.y += m_state.grav_accel;

	m_state.grav_accel += acs->GetCurrGravity() * m_state.weight;

	if (Device::KeyOn('D')) { m_state.pos.x += m_state.speed; };
	if (Device::KeyOn('A')) { m_state.pos.x -= m_state.speed; };

	static int count = 0;

	if(!m_state.is_jump)
	{
		m_state.grav_accel = 0.f;
		count = 0;
	}

	if (Device::KeyOn(VK_SPACE)) 
	{
		
		count++;
		
		m_state.is_jump = true;
		
		if (count <= 5) 
		{
			m_state.grav_accel = -m_state.jump_power;
		}
		
	};

}

void Player::Draw(std::string fileName_)
{
	m_drawer2d.DrawTexture(m_state.pos, fileName_);
}

void Player::Release()
{
	m_drawer2d.AllRelease();
}