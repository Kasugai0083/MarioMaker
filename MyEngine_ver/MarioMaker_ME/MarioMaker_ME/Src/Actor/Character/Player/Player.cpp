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
	m_state.old_pos.x = 0.f;
	m_state.old_pos.y = 0.f;
	
	m_state.has_on_ground = false;
}

void Player::Update()
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; }

	// ベクトル情報の管理 start
	m_state.old_pos = m_state.pos;
	// ベクトル情報の管理 end

	// 左右の移動処理 start
	if (Device::KeyOn('D')) 
	{ 
		m_state.pos.x += m_state.speed;
	}
	if (Device::KeyOn('A'))
	{
		m_state.pos.x -= m_state.speed;
	}
	// 左右の移動処理 end

	// 重力処理 start
	// ジャンプ処理 start
	static int count = 0;
	static bool short_jump = false;
	if (Device::KeyOn(VK_SPACE)
		&& m_state.has_on_ground)
	{

		m_state.grav_accel = -m_state.jump_power;
		m_state.has_on_ground = false;
		short_jump = true;

	};

	if (Device::KeyOn(VK_SPACE)
		&& short_jump 
		&& count <= 20)

	{
		count++;
		m_state.grav_accel = -m_state.jump_power;
	}

	if (Device::KeyOff(VK_SPACE)) 
	{
		short_jump = false;
	}
	// ジャンプ処理 end
	if(m_state.has_on_ground)
	{
		m_state.grav_accel = 0.f;
		short_jump = false;
		count = 0;
	}
	else 
	{
		m_state.grav_accel += acs->GetCurrGravity() * m_state.weight;
	}
	m_state.pos.y += m_state.grav_accel;

	// 重力処理 end
	
	// ベクトルの計算 start
	m_state.curr_vec = m_state.pos - m_state.old_pos;
	// ベクトルの計算 end

}

void Player::Draw(std::string fileName_)
{
	m_drawer2d.DrawTexture(m_state.pos, fileName_);

	// プレイヤー座標を表示 start
	std::string player_posx_txt = "プレイヤーのX座標 => ";
	player_posx_txt += std::to_string(m_state.pos.x);
	std::string player_posy_txt = "プレイヤーのY座標 => ";
	player_posy_txt += std::to_string(m_state.pos.y);

	m_drawer2d.DrawFont(Pos2(100.f, 100.f), player_posx_txt);
	m_drawer2d.DrawFont(Pos2(100.f, 150.f), player_posy_txt);
	// プレイヤー座標を表示 end

}

void Player::Release()
{
	m_drawer2d.AllRelease();
}