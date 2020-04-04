#include "Player.h"
#include "..//..//..//Data/Accessor.h"
#include "../../../Engine/Device.h"

Player::~Player()
{
}

void Player::Init(Pos2 pos_)
{
	
	for(auto i : m_name_list)
	{
		m_drawer2d.LoadTexture(*i.second);
	}

	// 構造体を全て 0 で初期化
	ZeroMemory(&m_state, sizeof(t_ActorState));

	m_state.pos.x = pos_.x;
	m_state.pos.y = pos_.y;

	m_state.size.height = MAP_CHIP_SIZE;
	m_state.size.width = MAP_CHIP_SIZE;

	m_state.weight = 1.f;
	m_state.speed = 0.5f;
	m_state.jump_power = 5.f;
	m_state.is_death = true;

	m_count = 0;
	m_short_jump = false;
}

bool Player::DeathAnimation()
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return false; }

	if (m_state.is_death)
	{
		static int count = 0;

		if (count == DEATH_WAIT)
		{
			m_state.grav_accel -= m_state.jump_power;
		}
		else if (count >= DEATH_ANIMATION_TIME)
		{
			count = 0;
			m_state.can_next_scene = true;
		}
		else if (count > DEATH_WAIT)
		{
			m_state.grav_accel += acs->GetCurrGravity() * m_state.weight;

			m_state.pos.y += m_state.grav_accel;
		}

		count++;

		return true;
	}
	return false;
}

void Player::Update()
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; }

	if (DeathAnimation()) { return; }

#if 1
	// 本番用
	// ベクトル情報の管理 start
	m_state.old_pos = m_state.pos;
	// ベクトル情報の管理 end

	// 左右の移動処理 start
	if (Device::KeyOn('D'))
	{
		m_state.accel += m_state.speed;
	}
	if (Device::KeyOn('A'))
	{
		m_state.accel -= m_state.speed;
	}

	if (m_state.accel >= MAX_SPEED) { m_state.accel = MAX_SPEED; }
	if (m_state.accel <= -MAX_SPEED) { m_state.accel = -MAX_SPEED; }

	if (m_state.has_on_ground && m_state.accel > 0.0f)
	{
		m_state.accel -= FRICTION;
		if (m_state.accel < 0.f)
		{
			m_state.accel = 0.f;
		}
	}
	else if (m_state.has_on_ground && m_state.accel < 0.0f)
	{
		m_state.accel += FRICTION;
		if (m_state.accel > 0.f)
		{
			m_state.accel = 0.f;
		}
	}
	// 左右の移動処理 end

	// 重力処理 start

		// ジャンプ処理 start
	if (Device::KeyOn(VK_SPACE)
		&& m_state.has_on_ground)
	{

		m_state.grav_accel = -m_state.jump_power;
		m_state.has_on_ground = false;
		m_short_jump = true;

	};

	if (Device::KeyOn(VK_SPACE)
		&& m_short_jump
		&& m_count <= 20)

	{
		m_count++;
		m_state.grav_accel = -m_state.jump_power;
	}

	if (Device::KeyOff(VK_SPACE))
	{
		m_short_jump = false;
	}
	// ジャンプ処理 end


	if (m_state.has_on_ground)
	{
		m_state.grav_accel = 0.f;
		m_short_jump = false;
		m_count = 0;
	}

	m_state.grav_accel += acs->GetCurrGravity() * m_state.weight;

	// 重力処理 end

	// 加速度を座標に反映 start
	m_state.pos.x += m_state.accel;
	m_state.pos.y += m_state.grav_accel;
	// 加速度を座標に反映 end

	// フィールド外に出た場合死亡処理 start
	if(m_state.pos.y >= m_camera_ptr->GetFieldSize().y)
	{
		m_state.is_death = true;
	}
	// フィールド外に出た場合死亡処理 end

	// ベクトルの計算 start
	m_state.curr_vec = m_state.pos - m_state.old_pos;
	if (m_state.curr_vec.y > 0)
	{
		m_state.has_on_ground = false;
	}
	// ベクトルの計算 end


#else
	// デバッグ用
	if (Device::KeyOn('D'))
	{
		m_state.pos.x += m_state.speed;
	}
	if (Device::KeyOn('A'))
	{
		m_state.pos.x -= m_state.speed;
	}
	if (Device::KeyOn('W'))
	{
		m_state.pos.y -= m_state.speed;
	}
	if (Device::KeyOn('S'))
	{
		m_state.pos.y += m_state.speed;
	}
	m_state.curr_vec = m_state.pos - m_state.old_pos;

#endif
}


void Player::Draw()
{

	if(m_state.is_death)
	{
		m_drawer2d.DrawTexture(m_state.pos, *m_name_list["死亡"], m_camera_ptr);
	}
	else
	{
		m_drawer2d.DrawTexture(m_state.pos, *m_name_list["移動"], m_camera_ptr);
	}

	// プレイヤー座標を表示 start
	std::string player_posx_txt = "プレイヤーのX座標 => ";
	player_posx_txt += std::to_string(m_state.pos.x);
	std::string player_posy_txt = "プレイヤーのY座標 => ";
	player_posy_txt += std::to_string(m_state.pos.y);
	std::string player_grv_txt = "重力加速度 => ";
	player_grv_txt += std::to_string(m_state.grav_accel);
	std::string player_acs_txt = "加速度 => ";
	player_acs_txt += std::to_string(m_state.accel);
	std::string player_ground_txt = "プレイヤーの着地状況 => ";

	std::string ground_txt;
	if (m_state.has_on_ground)
	{
		ground_txt = "着地";
	}
	else
	{
		ground_txt = "空中";
	}

	player_ground_txt += ground_txt;

	m_drawer2d.DrawFont(Pos2(100.f, 50.f), player_posx_txt);
	m_drawer2d.DrawFont(Pos2(100.f, 100.f), player_posy_txt);
	m_drawer2d.DrawFont(Pos2(100.f, 150.f), player_grv_txt);
	m_drawer2d.DrawFont(Pos2(100.f, 200.f), player_acs_txt);
	m_drawer2d.DrawFont(Pos2(100.f, 250.f), player_ground_txt);
	// プレイヤー座標を表示 end

}

void Player::Release()
{
	m_drawer2d.AllRelease();
}