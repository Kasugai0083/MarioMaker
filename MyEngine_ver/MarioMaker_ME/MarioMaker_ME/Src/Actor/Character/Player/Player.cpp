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
	
	m_state.has_on_ground = false;
}

void Player::Update()
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; }


	// 左右の移動処理 start
	if (Device::KeyOn('D')) { m_state.pos.x += m_state.speed; };
	if (Device::KeyOn('A')) { m_state.pos.x -= m_state.speed; };
	// 左右の移動処理 end

	// ジャンプ処理 start
	static int count = 0;
	if (Device::KeyOn(VK_SPACE)
		&& m_state.has_on_ground)
	{


		m_state.grav_accel = -m_state.jump_power;
		m_state.has_on_ground = false;


	};
	if(m_state.has_on_ground)
	{
		m_state.grav_accel = 0.f;
		count = 0;
	}
	else {
		m_state.pos.y += m_state.grav_accel;
		m_state.grav_accel += acs->GetCurrGravity() * m_state.weight;
	}


	// ジャンプ処理 end
 
}

void Player::Draw(std::string fileName_)
{
	m_drawer2d.DrawTexture(m_state.pos, fileName_);
}

void Player::Release()
{
	m_drawer2d.AllRelease();
}