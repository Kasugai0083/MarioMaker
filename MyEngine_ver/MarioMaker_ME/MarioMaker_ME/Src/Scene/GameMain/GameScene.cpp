#include "GameScene.h"

GameScene::~GameScene()
{
}


void GameScene::Init()
{
	m_drawer2d.LoadTexture("Res/Game/game_main_bg.png");

	m_map_mgr.Init();

	// ÉVÅ[ÉìëJà⁄
	m_state = SceneState::UPDATE;
}

void GameScene::Update() {

	if (Device::KeyPress(VK_SPACE)) { m_state = SceneState::END; }
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

