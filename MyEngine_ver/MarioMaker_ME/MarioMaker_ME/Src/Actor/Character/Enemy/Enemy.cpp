#include "Enemy.h"


Enemy::~Enemy()
{
}

void Enemy::Init(Pos2 pos_, std::string fileName_)
{
	m_drawer2d.LoadTexture(fileName_);

	m_state.pos.x = pos_.x;
	m_state.pos.y = pos_.y;

	m_state.weight = 1.f;
	m_state.speed = 1.f;
	m_state.jump_power = 0.f;

	m_state.curr_vec.x = 0.f;
	m_state.curr_vec.y = 0.f;


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