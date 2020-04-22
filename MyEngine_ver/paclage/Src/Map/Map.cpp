#include "Map.h"
#include "../FileReader/FileReader.h"
#include "..//Data/Accessor.h"

MapManager::~MapManager()
{
}

void MapManager::Init(std::string map_name_)
{
	m_gravity = GRAVITY;
	
	m_map_name = map_name_;
	m_has_clear = false;

	m_actor_mgr.Init(m_map_name);
	m_actor_mgr.GetClearPTR(&m_has_clear);

}

void MapManager::Draw()
{

	m_actor_mgr.Draw();

}

void MapManager::Update() {

	Accessor* acs = Accessor::GetInstance();
	if (!acs) { return; };

	acs->SetCurrGravity(m_gravity);
	acs->UpdateCameraPTR(&m_map_camera);

	m_actor_mgr.Update();

}

void MapManager::Release() 
{
	m_actor_mgr.Release();

}