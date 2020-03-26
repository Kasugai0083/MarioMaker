#include "ActorManager.h"
#include "../FileReader/FileReader.h"
#include "..//Engine/Device.h"
#include "..//Utility/Calculator/Calculator.h"
#include "../Data/Accessor.h"

void ActorManager::Init() 
{
	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; };

	m_camera_ptr = acs->GetCurrCameraPTR();

	FileReader file_reader;

	file_reader.LoadCSV("Csv/stage01.csv");

	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
		{
			m_map[i][j] = new int(0);
		}
	}
	
	file_reader.GetMapCSV(m_map);

	float pos_x = 0.f;
	float pos_y = 0.f;

	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
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
	for(auto i : m_actors["プレイヤー"])
	{
		i->Draw("Res/Game/Mapchip/player.png", m_camera_ptr);
	}
	for(auto i : m_actors["エネミー"])
	{
		i->Draw("Res/Game/Mapchip/enemy.png", m_camera_ptr);
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

					//player->SetHasOnGround(false);

				}
				else if (Calculator::ForceRectCollision(player->GetState(), block->GetState()) == ForceHit::RIGHT_SIDE)
				{

					float player_x = block->GetPos().x + MAP_CHIP_SIZE;
					float player_y = player->GetPos().y;

					player->SetPos(Pos2(player_x, player_y));

					player->SetAccel(0.f);

					//player->SetHasOnGround(false);

				}
				else if (Calculator::ForceRectCollision(player->GetState(), block->GetState()) == ForceHit::UNDER_SIDE)
				{

					float player_x = player->GetPos().x;
					float player_y = block->GetPos().y + MAP_CHIP_SIZE;

					player->SetPos(Pos2(player_x, player_y));
					player->SetGrvAccel(0.f);

					//player->SetHasOnGround(false);
				}
				// 上方処理

				//else if (Calculator::ForceRectCollision(player->GetState(), block->GetState()) == ForceHit::NONE)
				//{

				//	player->SetHasOnGround(false);

				//}


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
		// ブロックとプレイヤーの当たり end
	}
	//// アクター全体の更新処理 start
	//for (auto i : m_actors)
	//{
	//	for (auto j : m_actors[i.first])
	//	{
	//		j->Update();
	//	}
	//}
	//// アクター全体の更新処理 end
}

void ActorManager::Release()
{
	// m_mapの解放
	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
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