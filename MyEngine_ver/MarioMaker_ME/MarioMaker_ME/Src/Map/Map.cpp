#include "Map.h"
#include "../FileReader/FileReader.h"


MapManager::~MapManager()
{
	Release();
}

void MapManager::Init() {

	FileReader m_reader;

	for (int i = 0; i < MAP_H; i++) 
	{
		for (int j = 0; j < MAP_W; j++) 
		{
			m_map[i][j] = new int;
		}
	}

	m_reader.LoadCSV("Csv/stage01.csv");
	m_reader.GetMapCSV(m_map);
	m_drawer2d.LoadTexture("Res/bomb.png");

	float pos_x = 0.f;
	float pos_y = 0.f;

	for (int i = 0; i < MAP_H; i++)
	{
		for (int j = 0; j < MAP_W; j++)
		{
			if (*m_map[i][j] == 1)
			{
				pos_x = (float)j * MAP_CHIP_SIZE;
				pos_y = (float)i * MAP_CHIP_SIZE;

				Pos2 chip_pos(pos_x, pos_y);

				m_blocks.push_back(new Block(chip_pos, "Res/Game/Mapchip/block.png"));
			}
		}
	}

}

void MapManager::Draw() {

	for(auto i : m_blocks)
	{
		i->Draw("Res/Game/Mapchip/block.png");
	}

	Pos2 test_pos(100.f, 100.f);

	m_drawer2d.DrawTexture(test_pos, "Res/bomb.png");

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

}