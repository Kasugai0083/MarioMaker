#include "Enemy.h"

Enemy::~Enemy()
{
}

void Enemy::Init(Pos2 pos_, std::string fileName_)
{
	m_drawer2d.LoadTexture(fileName_);

	m_state.pos.x = pos_.x;
	m_state.pos.y = pos_.y;
	m_state.old_pos.x = 0.f;
	m_state.old_pos.y = 0.f;

	m_state.size.height = MAP_CHIP_SIZE;
	m_state.size.width = MAP_CHIP_SIZE;

	m_state.weight = 1.f;
	m_state.speed = 1.f;
	m_state.jump_power = 0.f;
	m_state.grav_accel = 0.f;

	m_state.curr_vec.x = 0.f;
	m_state.curr_vec.y = 0.f;


	m_state.has_on_ground = true;
}

void Enemy::Update()
{

}

void Enemy::Draw(std::string fileName_)
{
	m_drawer2d.DrawTexture(m_state.pos, fileName_);
}

void Enemy::Release()
{
	m_drawer2d.AllRelease();
}