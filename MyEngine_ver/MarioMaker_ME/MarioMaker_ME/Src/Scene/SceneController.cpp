#include "SceneController.h"
#include "Title/TitleScene.h"
#include "GameMain//GameScene.h"
#include "Result/ResultScene.h"

void SceneController::Init(SceneID id) {
	m_scene_list.push_back(new TitleScene());
	m_scene_list.push_back(new GameScene());
	m_scene_list.push_back(new ResultScene());

	m_scene_id = id;
	m_curr_scene = m_scene_list[(int)m_scene_id];
}

void SceneController::Update() {
	SceneID id;
	id = m_curr_scene->Control();
	ChanegeScene(id);
}

void SceneController::Draw() {
	m_curr_scene->Draw();
 }

void SceneController::ChanegeScene(SceneID id) {
	if (id != m_scene_id) { m_scene_id = id; }
	m_curr_scene = m_scene_list[(int)m_scene_id];
}

void SceneController::Release() {
	for (auto scene : m_scene_list) 
	{
		SceneBase* base = scene;
		delete base;
	}
	m_scene_list.clear();
}