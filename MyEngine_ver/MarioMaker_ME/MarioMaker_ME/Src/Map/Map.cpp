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

	m_actor_mgr.Init(m_map_name);

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
	// テスト中
	//m_map_camera.Update();
	// テスト中ここまで

	m_actor_mgr.Update();

}

void MapManager::Release() 
{
	m_actor_mgr.Release();

}