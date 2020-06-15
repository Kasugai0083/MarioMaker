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

			#pragma region �v���C���[�摜�ǂݍ���
			std::map<std::string, std::string*> player_grp_list;

			player_grp_list["�ړ�"] = new std::string("Res/Game/Mapchip/player.png");
			player_grp_list["���S"] = new std::string("Res/Game/Mapchip/player_death.png");

			#pragma endregion

			#pragma region �S�[���摜�ǂݍ���
			std::map<std::string, std::string*> goal_grp_list;

			goal_grp_list["��"] = new std::string("Res/Game/Mapchip/Goal0.png");
			goal_grp_list["��"] = new std::string("Res/Game/Mapchip/Goal1.png");
			goal_grp_list["��"] = new std::string("Res/Game/Mapchip/Goal2.png");
			goal_grp_list["��"] = new std::string("Res/Game/Mapchip/Goal3.png");

			#pragma endregion

			#pragma region �u���b�N�摜�ǂݍ���
			std::map<std::string, std::string*> block_grp_list;

			block_grp_list["�u���b�N"] = new std::string("Res/Game/Mapchip/block.png");
			block_grp_list["�A�C�X�u���b�N"] = new std::string("Res/Game/Mapchip/block.png");

			#pragma endregion

			#pragma region �G�l�~�[�摜�ǂݍ���
			std::map<std::string, std::string*> enemy_grp_list;

			enemy_grp_list["�N���{�["] = new std::string("Res/Game/Mapchip/enemy.png");
			enemy_grp_list["�m�R�m�R"] = new std::string("Res/Game/Mapchip/enemy.png");
			enemy_grp_list["�{����"] = new std::string("Res/Game/Mapchip/enemy.png");

			#pragma endregion

			if (*m_map[i][j] == 1)
			{
				m_actors["�u���b�N"].push_back(new Block(chip_pos, block_grp_list));
			}
			if (*m_map[i][j] == 2)
			{
				m_actors["�v���C���["].push_back(new Player(chip_pos, player_grp_list));
			}
			if (*m_map[i][j] == 3)
			{
				m_actors["�G�l�~�["].push_back(new Enemy(chip_pos, enemy_grp_list));
			}
			if (*m_map[i][j] == 9)
			{
				#pragma region �S�[��
				bool has_min_num = false, has_max_num = false;

				if (i - 1 < 0) { has_min_num = true; }
				else if (i + 1 >= MAX_MAP_H) { has_min_num = true; }

				if ((has_min_num || !has_min_num && *m_map[i - 1][j] != 9) && (has_max_num || !has_max_num && *m_map[i + 1][j] != 9))
				{
					m_actors["�S�[��"].push_back(new Goal(chip_pos, GoalType::INDIVIDUAL, goal_grp_list));
				}
				else if ((has_min_num || !has_min_num && *m_map[i - 1][j] != 9))
				{
					m_actors["�S�[��"].push_back(new Goal(chip_pos, GoalType::UP, goal_grp_list));
				}
				else if ((has_max_num || !has_max_num && *m_map[i + 1][j] != 9))
				{
					m_actors["�S�[��"].push_back(new Goal(chip_pos, GoalType::DOWN, goal_grp_list));
				}
				else 
				{
					m_actors["�S�[��"].push_back(new Goal(chip_pos, GoalType::MIDDLE, goal_grp_list));
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
		i->Draw();
	}

	for(auto i : m_actors["�G�l�~�["])
	{
		i->Draw();
	}

	#pragma region �S�[��
	for (auto i : m_actors["�S�[��"])
	{
		i->Draw();
	}
	#pragma endregion

	for (auto i : m_actors["�v���C���["])
	{
		i->Draw();
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
			if (player->GetState().is_death) { return; }
			// ���Ӓ���
			if (SurroundingSurvey(block->GetState(), player->GetState()))
			{	
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

			}
		}
	}
}

void ActorManager::CheckPlayerDeath()
{
	for (auto player : m_actors["�v���C���["])
	{
		if (player->GetState().can_next_scene) { *m_clear_ptr = true; }
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