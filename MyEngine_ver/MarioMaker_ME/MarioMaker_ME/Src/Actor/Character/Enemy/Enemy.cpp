#include "Enemy.h"

Enemy::~Enemy()
{
}

void Enemy::Init(Pos2 pos_)
{
	for (auto i : m_name_list)
	{
		m_drawer2d.LoadTexture(*i.second);
	}

	ZeroMemory(&m_state, sizeof(t_ActorState));

	m_state.pos.x = pos_.x;
	m_state.pos.y = pos_.y;

	m_state.size.height = MAP_CHIP_SIZE;
	m_state.size.width = MAP_CHIP_SIZE;

	m_state.weight = 1.f;
	m_state.speed = 1.f;

	m_state.is_death = false;

	m_state.curr_vec.x = -1.f;
}

void Enemy::Update()
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; }

	// ベクトル情報の管理 start
	m_state.old_pos = m_state.pos;
	// ベクトル情報の管理 end


	// 加速処理 start
	if (m_state.curr_vec.x > 0)
	{
		m_state.accel += m_state.speed;
	}
	else
	{
		m_state.accel -= m_state.speed;
	}

	if (m_state.accel >= ENEMY_MAX_SPEED) { m_state.accel = ENEMY_MAX_SPEED; }
	if (m_state.accel <= -ENEMY_MAX_SPEED) { m_state.accel = -ENEMY_MAX_SPEED; }
	// 加速処理 end

	if (m_state.has_on_ground)
	{
		m_state.grav_accel = 0.f;
	}
	m_state.grav_accel += acs->GetCurrGravity() * m_state.weight;

	// 加速度を座標に反映 start
	m_state.pos.x += m_state.accel;
	m_state.pos.y += m_state.grav_accel;
	// 加速度を座標に反映 end

	// ベクトルの計算 start
	m_state.curr_vec = m_state.pos - m_state.old_pos;
	if (m_state.curr_vec.y > 0)
	{
		m_state.has_on_ground = false;
	}
	// ベクトルの計算 end

}

void Enemy::Draw()
{
	switch (m_type)
	{
	case EnemyType::KURIBO:
		m_drawer2d.DrawTexture(m_state.pos, *m_name_list["クリボー"], m_camera_ptr);
		break;
	case EnemyType::NOKONOKO:
		m_drawer2d.DrawTexture(m_state.pos, *m_name_list["ノコノコ"], m_camera_ptr);
		break;
	case EnemyType::BOOMMAN:
		m_drawer2d.DrawTexture(m_state.pos, *m_name_list["ボム兵"], m_camera_ptr);
		break;
	case EnemyType::ETC:
		break;
	default:
		break;
	}
}

void Enemy::Release()
{
	m_drawer2d.AllRelease();
}