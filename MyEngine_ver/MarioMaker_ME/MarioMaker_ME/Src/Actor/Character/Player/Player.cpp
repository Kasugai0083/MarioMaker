#include "Player.h"
#include "..//..//..//Data/Accessor.h"
#include "../../../Engine/Device.h"

Player::~Player()
{
}

void Player::Init(Pos2 pos_, std::string fileName_)
{
	m_drawer2d.LoadTexture(fileName_);

	// �\���̂�S�� 0 �ŏ�����
	ZeroMemory(&m_state, sizeof(t_ActorState));

	m_state.pos.x = pos_.x;
	m_state.pos.y = pos_.y;

	m_state.size.height = MAP_CHIP_SIZE;
	m_state.size.width = MAP_CHIP_SIZE;

	m_state.weight = 1.f;
	m_state.speed = 0.5f;
	m_state.jump_power = 5.f;

	m_count = 0;
	m_short_jump = false;
}

void Player::Update()
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; }
#if 1
	// �{�ԗp
	// �x�N�g�����̊Ǘ� start
	m_state.old_pos = m_state.pos;
	// �x�N�g�����̊Ǘ� end

	// ���E�̈ړ����� start
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
	// ���E�̈ړ����� end

	// �d�͏��� start
	// �W�����v���� start
	//static int count = 0;
	//static bool short_jump = false;
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


	// �W�����v���� end
	if(m_state.has_on_ground)
	{
		m_state.grav_accel = 0.f;
		m_short_jump = false;
		m_count = 0;

	}
	else 
	{
		m_state.grav_accel += acs->GetCurrGravity() * m_state.weight;
	}
	// �d�͏��� end
	
	// �����x�����W�ɔ��f start
	m_state.pos.x += m_state.accel;
	m_state.pos.y += m_state.grav_accel;
	// �����x�����W�ɔ��f end

	// �x�N�g���̌v�Z start
	m_state.curr_vec = m_state.pos - m_state.old_pos;
	// �x�N�g���̌v�Z end
	m_state.has_on_ground = false;

#else
	// �f�o�b�O�p
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

void Player::Draw(std::string fileName_)
{
	m_drawer2d.DrawTexture(m_state.pos, fileName_);

	// �v���C���[���W��\�� start
	std::string player_posx_txt = "�v���C���[��X���W => ";
	player_posx_txt += std::to_string(m_state.pos.x);
	std::string player_posy_txt = "�v���C���[��Y���W => ";
	player_posy_txt += std::to_string(m_state.pos.y);
	std::string player_grv_txt = "�d�͉����x => ";
	player_grv_txt += std::to_string(m_state.grav_accel);
	std::string player_acs_txt = "�����x => ";
	player_acs_txt += std::to_string(m_state.accel);

	m_drawer2d.DrawFont(Pos2(100.f, 100.f), player_posx_txt);
	m_drawer2d.DrawFont(Pos2(100.f, 150.f), player_posy_txt);
	m_drawer2d.DrawFont(Pos2(100.f, 200.f), player_grv_txt);
	m_drawer2d.DrawFont(Pos2(100.f, 250.f), player_acs_txt);
	// �v���C���[���W��\�� end

}

void Player::Release()
{
	m_drawer2d.AllRelease();
}