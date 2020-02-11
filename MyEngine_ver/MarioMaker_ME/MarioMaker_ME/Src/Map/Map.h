#pragma once

#include "../Engine/Graphics/Drawer2D.h"
#include "..//Data/GameData.h"
#include "..//Actor/Block/Block.h"
#include "..//Actor/Character/Player/Player.h"
#include "..//Actor/Character/Enemy/Enemy.h"
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
	float m_gravity;

	int* m_map[23][40];
	Drawer2D m_drawer2d;

	std::vector<Block*> m_blocks;
	std::vector<Player*> m_player;
	std::vector<Enemy*> m_enemy;
};

