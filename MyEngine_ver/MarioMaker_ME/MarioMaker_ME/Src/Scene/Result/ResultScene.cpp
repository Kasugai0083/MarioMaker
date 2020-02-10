#include "ResultScene.h"


ResultScene::~ResultScene()
{
}

void ResultScene::Init() {
	m_drawer2d.LoadTexture("Res/bomb.png");


	m_state = SceneState::UPDATE;
}

void ResultScene::Update() {


	if (Device::KeyPress('A')) { m_state = SceneState::END; }
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

void ResultScene::Draw() {
	{
		t_VertexPos v{ Pos2(WIN_W / 2,WIN_H / 2),Pos2(0.f,0.f),Pos2(256.f, 256.f) };
		m_drawer2d.DrawTexture(v, "Res/bomb.png");

		t_Vec2 font_pos(50.f, 50.f);
		m_drawer2d.DrawFont(font_pos, "2Dƒ|ƒŠƒSƒ“‚ð•\Ž¦");

	}

}