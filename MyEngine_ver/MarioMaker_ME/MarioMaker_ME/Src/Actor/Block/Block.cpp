#include "Block.h"
#include "..//..//Data/Accessor.h"

Block::~Block()
{
}

void Block::Init(Pos2 pos_, std::string fileName_)
{
	m_drawer2d.LoadTexture(fileName_);

	ZeroMemory(&m_state, sizeof(t_ActorState));

	m_state.pos.x = pos_.x;
	m_state.pos.y = pos_.y;

	m_state.size.height = MAP_CHIP_SIZE;
	m_state.size.width = MAP_CHIP_SIZE;


	m_state.has_on_ground = false;

	m_reaction = WEIGHT * GRAVITY;
}

void Block::Update()
{
	Accessor* acs = Accessor::GetInstance();

	float gravity_power = acs->GetCurrGravity() * m_state.weight;

	m_state.pos.y += gravity_power;

}
void Block::Draw(std::string fileName_, Camera* camera_) {
	m_drawer2d.DrawTexture(m_state.pos, fileName_, camera_);
}

void Block::Release() {
	m_drawer2d.AllRelease();
}