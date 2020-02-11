#include "Map.h"
#include "../FileReader/FileReader.h"
#include "..//Data/Accessor.h"

MapManager::~MapManager()
{
	Release();
}

void MapManager::Init() {

	FileReader m_reader;

	m_gravity = GRAVITY;

	m_reader.LoadCSV("Csv/stage01.csv");

	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
		{
			m_map[i][j] = new int(0);
		}
	}

	m_reader.GetMapCSV(m_map);

	float pos_x = 0.f;
	float pos_y = 0.f;

	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
		{
			pos_x = (float)j * MAP_CHIP_SIZE;
			pos_y = (float)i * MAP_CHIP_SIZE;
			
			if (*m_map[i][j] == 1)
			{
				Pos2 chip_pos(pos_x, pos_y);

				m_blocks.push_back(new Block(chip_pos, "Res/Game/Mapchip/block.png"));
			}

			if (*m_map[i][j] == 2)
			{
				Pos2 player_pos(pos_x, pos_y);

				m_player.push_back(new Player(player_pos, "Res/Game/Mapchip/player.png"));
			}
			if (*m_map[i][j] == 3)
			{
				Pos2 enemy_pos(pos_x, pos_y);

				m_enemy.push_back(new Enemy(enemy_pos, "Res/Game/Mapchip/enemy.png"));
			}
		}
	}

}

void MapManager::Draw() {

	for(auto i : m_blocks)
	{
		i->Draw("Res/Game/Mapchip/block.png");
	}

	for(auto i : m_player)
	{
		i->Draw("Res/Game/Mapchip/player.png");
	}

	for(auto i : m_enemy)
	{
		i->Draw("Res/Game/Mapchip/enemy.png");
	}


}

void MapManager::Update() {

	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; };
	acs->SetGravity(m_gravity);

}

void MapManager::Release() {
	
	m_drawer2d.AllRelease();

	// m_map‚Ì‰ð•ú
	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++) 
		{
			delete m_map[i][j];
			m_map[i][j] = nullptr;
		}
	}

	// m_block‚Ì‰ð•ú
	for(auto i : m_blocks)
	{
		delete i;
		i = nullptr;
	}
	m_blocks.clear();

	// m_player‚Ì‰ð•ú
	for(auto i : m_player)
	{
		delete i;
		i = nullptr;
	}
	m_player.clear();

	// m_enemy‚Ì‰ð•ú
	for(auto i : m_enemy)
	{
		delete i;
		i = nullptr;
	}
	m_enemy.clear();

}