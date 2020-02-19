#include "TitleScene.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init() {
	m_drawer2d.LoadTexture("Res/Title/title_bg.png");
	m_state = SceneState::UPDATE;
}

void TitleScene::Update() {

	if (Device::KeyPress(VK_RETURN)) { m_state = SceneState::END; }
}

SceneID TitleScene::End() {
	m_drawer2d.AllRelease();

	m_state = SceneState::INIT;
	return SceneID::GAME;
}

SceneID TitleScene::Control() {
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
	return SceneID::TITLE;
}

void TitleScene::Draw() {
	t_Vec2 bg_pos(0.f, 0.f);

	m_drawer2d.DrawTexture(bg_pos, "Res/Title/title_bg.png");

}