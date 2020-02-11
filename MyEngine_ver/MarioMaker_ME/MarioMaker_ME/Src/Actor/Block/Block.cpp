#include "Block.h"
#include "..//..//Data/GameData.h"

Block::~Block()
{
}

void Block::Init(Pos2 pos_, std::string fileName_)
{
	m_drawer2d.LoadTexture(fileName_);
	m_pos.x = pos_.x;
	m_pos.y = pos_.y;
	m_reaction = WEIGHT * GRAVITY;
}

void Block::Draw(std::string fileName_) {
	m_drawer2d.DrawTexture(m_pos, fileName_);
}

void Block::Release() {
	m_drawer2d.AllRelease();
}