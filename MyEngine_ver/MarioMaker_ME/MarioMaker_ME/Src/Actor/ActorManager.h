#pragma once

#include "ActorBase.h"
#include "Block/Block.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Player.h"


class ActorManager
{
public:
	ActorManager()
	{
		Init();
	}
	~ActorManager() 
	{
		Release();
	}

	void Init();
	void Update();
	void Draw();
	void Release();

private:
	int* m_map[23][40];
	std::map<std::string, std::vector<ActorBase*>> m_actors;
};