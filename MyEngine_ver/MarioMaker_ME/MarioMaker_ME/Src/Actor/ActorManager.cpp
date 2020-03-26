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
				m_actors["ブロック"].push_back(new Block(chip_pos, "Res/Game/Mapchip/block.png"));
			}
			if (*m_map[i][j] == 2)
			{
				m_actors["プレイヤー"].push_back(new Player(chip_pos, "Res/Game/Mapchip/player.png"));
			}
			if (*m_map[i][j] == 3)
			{
				m_actors["エネミー"].push_back(new Enemy(chip_pos, "Res/Game/Mapchip/enemy.png"));
			}
			if (*m_map[i][j] == 9)
			{
				if (i - 1 < 0) { return; }

				if (*m_map[i - 1][j] != 9) 
				{
					m_actors["上"].push_back(new Goal(chip_pos, "Res/Game/Mapchip/Goal1.png"));
				}
				else if ( *m_map[i + 1][j] != 9)
				{
					m_actors["下"].push_back(new Goal(chip_pos, "Res/Game/Mapchip/Goal3.png"));
				}
				else 
				{
					m_actors["中"].push_back(new Goal(chip_pos, "Res/Game/Mapchip/Goal2.png"));
				}
			}
		}
	}

}

// 参照 => チェルノブイリ実験場
void ActorManager::Draw()
{
	for(auto i : m_actors["ブロック"])
	{
		i->Draw("Res/Game/Mapchip/block.png", m_camera_ptr);
	}

	for(auto i : m_actors["エネミー"])
	{
		i->Draw("Res/Game/Mapchip/enemy.png", m_camera_ptr);
	}
	for(auto i : m_actors["上"])
	{
		i->Draw("Res/Game/Mapchip/Goal1.png", m_camera_ptr);
	}
	for(auto i : m_actors["中"])
	{
		i->Draw("Res/Game/Mapchip/Goal2.png", m_camera_ptr);
	}
	for(auto i : m_actors["下"])
	{
		i->Draw("Res/Game/Mapchip/Goal3.png", m_camera_ptr);
	}
	for (auto i : m_actors["プレイヤー"])
	{
		i->Draw("Res/Game/Mapchip/player.png", m_camera_ptr);
	}
}

void ActorManager::PlayerAndBlockCollide() 
{
	// ブロックとプレイヤーの当たり start
	Pos2 curr_block(0.f, 0.f);

	for (auto block : m_actors["ブロック"])
	{
		for (auto player : m_actors["プレイヤー"])
		{
			// 周辺調査
			if (
				block->GetState().pos.x >= (player->GetState().pos.x - player->GetState().size.width)
				&& block->GetState().pos.x <= (player->GetState().pos.x + (2 * player->GetState().size.width))
				&& block->GetState().pos.y >= (player->GetState().pos.y - player->GetState().size.height)
				&& block->GetState().pos.y <= (player->GetState().pos.y + (2 * player->GetState().size.height))
				)
			{

#if 1		
				/**
				* 4分割処理
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
				* 通常の処理
				*/
				// 左方処理
				if (Calculator::LeftSideCollision(player->GetState(), block->GetState()))
				{

					float player_x = block->GetPos().x - MAP_CHIP_SIZE;
					float player_y = player->GetPos().y;

					player->SetPos(Pos2(player_x, player_y));


				}
				// 右方処理
				else if (Calculator::RightSideCollision(player->GetState(), block->GetState()))
				{

					float player_x = block->GetPos().x + MAP_CHIP_SIZE;
					float player_y = player->GetPos().y;

					player->SetPos(Pos2(player_x, player_y));

				}
				// 下方処理
				else if (Calculator::UnderSideCollision(player->GetState(), block->GetState()))
				{

					float player_x = player->GetPos().x;
					float player_y = block->GetPos().y + MAP_CHIP_SIZE;

					player->SetPos(Pos2(player_x, player_y));
					player->SetGrvAccel(0.f);

				}
				// 上方処理
				else if (Calculator::UpSideCollision(player->GetState(), block->GetState()))
				{

					float player_x = player->GetPos().x;
					float player_y = block->GetPos().y - MAP_CHIP_SIZE;

					player->SetPos(Pos2(player_x, player_y));

					player->SetHasOnGround(true);

				}
#else
				/**
				* 古い処理
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

// 参照 => チェルノブイリ実験場
void ActorManager::Update()
{
	// アクター全体の更新処理 start
	for (auto i : m_actors)
	{
		for (auto j : m_actors[i.first])
		{
			j->Update();
		}
	}
	// アクター全体の更新処理 end

	// ブロックとプレイヤーの当たり
	PlayerAndBlockCollide();
	
	int count = 0;
	t_Vec2 sum_pos = t_Vec2(0.f,0.f);
	for (auto player : m_actors["プレイヤー"]) 
	{
		count++;
		sum_pos += player->GetState().pos;
	}
	t_Vec2 camera_pos;
	camera_pos.x = sum_pos.x / (float)count;
	camera_pos.y = sum_pos.y / (float)count;

	m_camera_ptr->Update(camera_pos);
}

void ActorManager::Release()
{
	// m_mapの解放
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