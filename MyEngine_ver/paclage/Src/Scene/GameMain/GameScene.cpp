#include "GameScene.h"

GameScene::~GameScene()
{
}


void GameScene::Init()
{
	m_drawer2d.LoadTexture("Res/Game/game_main_bg.png");

	//m_map_mgr.Init("Csv/stage01.csv");
	m_map_mgr.Init("Csv/stage_long.csv");
	//m_map_mgr.Init("Csv/stage_small.csv");
	//m_map_mgr.Init("Csv/stage_small2.csv");

	// ÉVÅ[ÉìëJà⁄
	m_state = SceneState::UPDATE;
}

void GameScene::Update() {

	m_map_mgr.Update();

	if (m_map_mgr.GetHasClear()) { m_can_next_scene = true; }
	SwitchEnd();
}

SceneID GameScene::End() {
	m_drawer2d.AllRelease();

	m_map_mgr.Release();

	m_state = SceneState::INIT;
	return SceneID::RESULT;
}

SceneID GameScene::Control() {
	switch (m_state)
	{
	case SceneState::INIT:
		Init();
		break;
	case SceneState::UPDATE:
		Update();
		break;
	case SceneState::END:
		return End();
	}
	return SceneID::GAME;
}

void GameScene::Draw() {
	Pos2 bg_pos(0.f, 0.f);
	//m_drawer2d.DrawTexture(bg_pos, "Res/Game/game_main_bg.png");

	m_map_mgr.Draw();

}

