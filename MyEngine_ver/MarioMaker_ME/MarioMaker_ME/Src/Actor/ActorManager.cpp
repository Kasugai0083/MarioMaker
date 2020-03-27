#include "ActorManager.h"
#include "../FileReader/FileReader.h"
#include "..//Engine/Device.h"
#include "..//Utility/Calculator/Calculator.h"
#include "../Data/Accessor.h"

void ActorManager::Init(std::string map_name_)
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; };

	m_camera_ptr = acs->GetCurrCameraPTR();

	FileReader file_reader;

	file_reader.LoadCSV(map_name_);
	m_camera_ptr->SetMapSize(file_reader.GetMapSize());

	for (int i = 0; i < MAX_MAP_H; i++)
	{
		for (int j = 0; j < MAX_MAP_W; j++)
		{
			m_map[i][j] = new int(0);
		}
	}
	
	file_reader.GetMapCSV(m_map);

	float pos_x = 0.f;
	float pos_y = 0.f;

	for (int i = 0; i < MAX_MAP_H; i++)
	{
		for (int j = 0; j < MAX_MAP_W; j++)
		{
			pos_x = (float)j * MAP_CHIP_SIZE;
			pos_y = (float)i * MAP_CHIP_SIZE;

			Pos2 chip_pos(pos_x, pos_y);

			if (*m_map[i][j] == 1)
			{
				m_actors["�u���b�N"].push_back(new Block(chip_pos, "Res/Game/Mapchip/block.png"));
			}
			if (*m_map[i][j] == 2)
			{
				m_actors["�v���C���["].push_back(new Player(chip_pos, "Res/Game/Mapchip/player.png"));
			}
			if (*m_map[i][j] == 3)
			{
				m_actors["�G�l�~�["].push_back(new Enemy(chip_pos, "Res/Game/Mapchip/enemy.png"));
			}
			if (*m_map[i][j] == 9)
			{
				#pragma region �S�[��
				bool has_min_num = false, has_max_num = false;

				if (i - 1 < 0) { has_min_num = true; }
				else if (i + 1 >= MAX_MAP_H) { has_min_num = true; }

				if ((has_min_num || !has_min_num && *m_map[i - 1][j] != 9) && (has_max_num || !has_max_num && *m_map[i + 1][j] != 9))
				{
					m_actors["��"].push_back(new Goal(chip_pos, "Res/Game/Mapchip/Goal0.png"));
				}
				else if ((has_min_num || !has_min_num && *m_map[i - 1][j] != 9))
				{
					m_actors["��"].push_back(new Goal(chip_pos, "Res/Game/Mapchip/Goal1.png"));
				}
				else if ((has_max_num || !has_max_num && *m_map[i + 1][j] != 9))
				{
					m_actors["��"].push_back(new Goal(chip_pos, "Res/Game/Mapchip/Goal3.png"));
				}
				else 
				{
					m_actors["��"].push_back(new Goal(chip_pos, "Res/Game/Mapchip/Goal2.png"));
				}
				#pragma endregion
			}
		}
	}

}

// �Q�� => �`�F���m�u�C��������
void ActorManager::Draw()
{
	for(auto i : m_actors["�u���b�N"])
	{
		i->Draw("Res/Game/Mapchip/block.png", m_camera_ptr);
	}

	for(auto i : m_actors["�G�l�~�["])
	{
		i->Draw("Res/Game/Mapchip/enemy.png", m_camera_ptr);
	}

	#pragma region �S�[��
	for (auto i : m_actors["��"])
	{
		i->Draw("Res/Game/Mapchip/Goal0.png", m_camera_ptr);
	}
	for (auto i : m_actors["��"])
	{
		i->Draw("Res/Game/Mapchip/Goal1.png", m_camera_ptr);
	}
	for (auto i : m_actors["��"])
	{
		i->Draw("Res/Game/Mapchip/Goal2.png", m_camera_ptr);
	}
	for (auto i : m_actors["��"])
	{
		i->Draw("Res/Game/Mapchip/Goal3.png", m_camera_ptr);
	}
	#pragma endregion

	for (auto i : m_actors["�v���C���["])
	{
		i->Draw("Res/Game/Mapchip/player.png", m_camera_ptr);
	}
}

bool SurroundingSurvey(t_ASta actor1_, t_ASta actor2_) 
{
	if (
		actor1_.pos.x >= (actor2_.pos.x - actor2_.size.width)
		&& actor1_.pos.x <= (actor2_.pos.x + (2 * actor2_.size.width))
		&& actor1_.pos.y >= (actor2_.pos.y - actor2_.size.height)
		&& actor1_.pos.y <= (actor2_.pos.y + (2 * actor2_.size.height))
		)
	{
		return true;
	}
	return false;
}

void ActorManager::PlayerAndGoalCollide()
{
	for (auto player : m_actors["�v���C���["])
	{
		std::vector<std::string> type_string;
		type_string.push_back("��");
		type_string.push_back("��");
		type_string.push_back("��");
		type_string.push_back("��");

		for (auto string : type_string)
		{
			for (auto goal : m_actors[string])
			{
				if (SurroundingSurvey(goal->GetState(), player->GetState()))
				{
  					if (Calculator::ForceRectCollision(player->GetState(), goal->GetState()) != ForceHit::NONE)
					{
						*m_clear_ptr = true;
					}
				}
			}
		}

	}
}

void ActorManager::PlayerAndBlockCollide() 
{
	// �u���b�N�ƃv���C���[�̓����� start
	Pos2 curr_block(0.f, 0.f);

	for (auto block : m_actors["�u���b�N"])
	{
		for (auto player : m_actors["�v���C���["])
		{
			// ���Ӓ���
			if (SurroundingSurvey(block->GetState(), player->GetState()))
			{
#if 1		
				/**
				* 4��������
				*/
				if (Calculator::ForceRectCollision(player->GetState(), block->GetState()) == ForceHit::UPPER_SIDE)
				{

					float player_x = player->GetPos().x;
					float player_y = block->GetPos().y - MAP_CHIP_SIZE;

					player->SetPos(Pos2(player_x, player_y));

					player->SetHasOnGround(true);

				}
				else if (Calculator::ForceRectCollision(player->GetState(), block->GetState()) == ForceHit::LEFT_SIDE)
				{

					float player_x = block->GetPos().x - MAP_CHIP_SIZE;
					float player_y = player->GetPos().y;

					player->SetPos(Pos2(player_x, player_y));

					player->SetAccel(0.f);

				}
				else if (Calculator::ForceRectCollision(player->GetState(), block->GetState()) == ForceHit::RIGHT_SIDE)
				{

					float player_x = block->GetPos().x + MAP_CHIP_SIZE;
					float player_y = player->GetPos().y;

					player->SetPos(Pos2(player_x, player_y));

					player->SetAccel(0.f);
				}
				else if (Calculator::ForceRectCollision(player->GetState(), block->GetState()) == ForceHit::UNDER_SIDE)
				{

					float player_x = player->GetPos().x;
					float player_y = block->GetPos().y + MAP_CHIP_SIZE;

					player->SetPos(Pos2(player_x, player_y));
					player->SetGrvAccel(0.f);

				}


#elif 1
				/**
				* �ʏ�̏���
				*/
				// ��������
				if (Calculator::LeftSideCollision(player->GetState(), block->GetState()))
				{

					float player_x = block->GetPos().x - MAP_CHIP_SIZE;
					float player_y = player->GetPos().y;

					player->SetPos(Pos2(player_x, player_y));


				}
				// �E������
				else if (Calculator::RightSideCollision(player->GetState(), block->GetState()))
				{

					float player_x = block->GetPos().x + MAP_CHIP_SIZE;
					float player_y = player->GetPos().y;

					player->SetPos(Pos2(player_x, player_y));

				}
				// ��������
				else if (Calculator::UnderSideCollision(player->GetState(), block->GetState()))
				{

					float player_x = player->GetPos().x;
					float player_y = block->GetPos().y + MAP_CHIP_SIZE;

					player->SetPos(Pos2(player_x, player_y));
					player->SetGrvAccel(0.f);

				}
				// �������
				else if (Calculator::UpSideCollision(player->GetState(), block->GetState()))
				{

					float player_x = player->GetPos().x;
					float player_y = block->GetPos().y - MAP_CHIP_SIZE;

					player->SetPos(Pos2(player_x, player_y));

					player->SetHasOnGround(true);

				}
#else
				/**
				* �Â�����
				*/
				if (Calculator::SerchUpDown(
					player->GetPos(),
					block->GetPos(),
					MAP_CHIP_SIZE,
					player->GetCurrVec()
				) == PowKind::DOWN)
				{
					float player_x = player->GetPos().x;
					float player_y = block->GetPos().y - MAP_CHIP_SIZE;

					player->SetPos(Pos2(player_x, player_y));

					player->SetHasOnGround(true);

				}
				else if (Calculator::SerchUpDown(
					player->GetPos(),
					block->GetPos(),
					MAP_CHIP_SIZE,
					player->GetCurrVec()
				) == PowKind::UP)
				{
					float player_x = player->GetPos().x;
					float player_y = block->GetPos().y + MAP_CHIP_SIZE;

					player->SetPos(Pos2(player_x, player_y));
					player->SetGrvAccel(0.f);
				}
				else if (Calculator::SerchRightLeft(
					player->GetPos(),
					block->GetPos(),
					MAP_CHIP_SIZE,
					player->GetCurrVec()
				) == PowKind::LEFT)
				{
					float player_x = block->GetPos().x + MAP_CHIP_SIZE;
					float player_y = player->GetPos().y;

					player->SetPos(Pos2(player_x, player_y));
				}
				else if (Calculator::SerchRightLeft(
					player->GetPos(),
					block->GetPos(),
					MAP_CHIP_SIZE,
					player->GetCurrVec()
				) == PowKind::RIGHT)
				{
					float player_x = block->GetPos().x - MAP_CHIP_SIZE;
					float player_y = player->GetPos().y;

					player->SetPos(Pos2(player_x, player_y));
				}
#endif
			}
		}
	}
}

void ActorManager::CheckPlayerDeath()
{
	for (auto player : m_actors["�v���C���["])
	{
		if (!player->GetState().is_death) { continue; }
		*m_clear_ptr = true;
	}
}

// �Q�� => �`�F���m�u�C��������
void ActorManager::Update()
{
	// �J�����̃A�b�v�f�[�g start
	int count = 0;
	t_Vec2 sum_pos = t_Vec2(0.f, 0.f);
	for (auto player : m_actors["�v���C���["])
	{
		count++;
		sum_pos += player->GetState().pos;
	}
	t_Vec2 camera_pos;
	camera_pos.x = sum_pos.x / (float)count;
	camera_pos.y = sum_pos.y / (float)count;

	m_camera_ptr->Update(camera_pos);
	// �J�����̃A�b�v�f�[�g end

	// �A�N�^�[�S�̂̍X�V���� start
	for (auto i : m_actors)
	{
		for (auto j : m_actors[i.first])
		{
			j->Update();
		}
	}
	// �A�N�^�[�S�̂̍X�V���� end

	// �u���b�N�ƃv���C���[�̓�����
	PlayerAndBlockCollide();
	
	// �S�[���ƃv���C���[�̓�����
	PlayerAndGoalCollide();

	// �v���C���[���S������ł邩����
	CheckPlayerDeath();


}

void ActorManager::Release()
{
	// m_map�̉��
	for (int i = 0; i < MAX_MAP_H; i++)
	{
		for (int j = 0; j < MAX_MAP_W; j++)
		{
			delete m_map[i][j];
			m_map[i][j] = nullptr;
		}
	}

	for (auto i : m_actors)
	{
		for (auto j : m_actors[i.first])
		{
			j->Release();
		}
	}
	m_actors.clear();
}