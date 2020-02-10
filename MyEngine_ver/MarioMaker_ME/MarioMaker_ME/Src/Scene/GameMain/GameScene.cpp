#include "GameScene.h"

GameScene::~GameScene()
{
}


void GameScene::Init()
{
		
	// シーン遷移
	m_state = SceneState::UPDATE;
}

void GameScene::Update() {

	if (Device::KeyPress('A')) { m_state = SceneState::END; }
}

SceneID GameScene::End() {
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
	t_Vec2 font_pos(0.f, 0.f);
	m_drawer2d.DrawFont(font_pos, "ゲームシーンを表示");

}

