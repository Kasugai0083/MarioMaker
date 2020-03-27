#include "ResultScene.h"


ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
	m_drawer2d.LoadTexture("Res/Result/result_bg.png");

	m_state = SceneState::UPDATE;
}

void ResultScene::Update() 
{
	if (Device::KeyPress(VK_RETURN)) { m_state = SceneState::END; }
}

SceneID ResultScene::End() {

	m_drawer2d.AllRelease();

	m_state = SceneState::INIT;
	return SceneID::TITLE;
}

SceneID ResultScene::Control() {
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
	return SceneID::RESULT;
}

void ResultScene::Draw()
{

	Pos2 bg_pos(0.f,0.f);
	m_drawer2d.DrawTexture(bg_pos, "Res/Result/result_bg.png");
}