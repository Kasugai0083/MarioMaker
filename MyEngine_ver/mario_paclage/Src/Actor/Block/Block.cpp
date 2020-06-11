#include "Block.h"
#include "..//..//Data/Accessor.h"

Block::~Block()
{
}

void Block::Init(Pos2 pos_)
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

	m_state.has_on_ground = false;

	m_reaction = WEIGHT * GRAVITY;
}

void Block::Update()
{
	Accessor* acs = Accessor::GetInstance();

	float gravity_power = acs->GetCurrGravity() * m_state.weight;

	m_state.pos.y += gravity_power;

}
void Block::Draw()
{
	switch (m_type)
	{
	case BlockType::NORMAL:
		m_drawer2d.DrawTexture(m_state.pos, *m_name_list["ブロック"], m_camera_ptr);
		break;
	case BlockType::ICE:
		m_drawer2d.DrawTexture(m_state.pos, *m_name_list["アイスブロック"], m_camera_ptr);
		break;
	case BlockType::ETC:
		break;
	default:
		break;
	}
}

void Block::Release() {
	m_drawer2d.AllRelease();
}