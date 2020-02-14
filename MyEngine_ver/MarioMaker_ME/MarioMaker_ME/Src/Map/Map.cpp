#include "Map.h"
#include "../FileReader/FileReader.h"
#include "..//Data/Accessor.h"

MapManager::~MapManager()
{
}

void MapManager::Init() 
{
	m_gravity = GRAVITY;
	
	m_actor_mgr.Init();
}

void MapManager::Draw()
{

	m_actor_mgr.Draw();

}

void MapManager::Update() {

	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; };
	acs->SetCurrGravity(m_gravity);

	m_actor_mgr.Update();

}

void MapManager::Release() 
{
	m_actor_mgr.Release();

}