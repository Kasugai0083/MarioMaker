#pragma once

#include "../Engine/Graphics/Drawer2D.h"
#include "..//Data/GameData.h"
#include "..//Actor/Block/Block.h"
#include <vector>

class MapManager
{
public:
	MapManager()
	{
		Init();
	};
	~MapManager();
	void Init();

	void Update();

	void Draw();

	void Release();
private:
	int* m_map[23][40];
	Drawer2D m_drawer2d;

	std::vector<Block*> m_blocks;
};

