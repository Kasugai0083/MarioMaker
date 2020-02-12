#pragma once

#include "../Engine/Graphics/Drawer2D.h"
#include "..//Data/GameData.h"
#include "../Actor/ActorManager.h"

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

	ActorManager m_actor_mgr;
};

