#include "ActorManager.h"
#include "../FileReader/FileReader.h"
#include "..//Engine/Device.h"

void ActorManager::Init() 
{
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
		i->Draw("Res/Game/Mapchip/block.png");
	}
	for(auto i : m_actors["プレイヤー"])
	{
		i->Draw("Res/Game/Mapchip/player.png");
	}
	for(auto i : m_actors["エネミー"])
	{
		i->Draw("Res/Game/Mapchip/enemy.png");
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
	float player_x = 0.f;
	float player_y = 0.f;

	for(auto block : m_actors["ブロック"])
	{
		for(auto player : m_actors["プレイヤー"])
		{
			if (
				player->GetPos().y >= block->GetPos().y - 32.f
				&& player->GetPos().x >= block->GetPos().x
				&& player->GetPos().x <= block->GetPos().x + 32.f
				) 
			{
				
				player_x = player->GetPos().x;
				player_y = block->GetPos().y - 32.f;
				
				Pos2 test_pos(player_x, player_y);
				player->SetPos(test_pos);

				
				player->SetHasOnGround(true);
				
			}
		}
	}

	// ブロックとプレイヤーの当たり end


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