#pragma once

#include "SceneBase.h"
#include "../Utility/SingletonTemplate.h"
#include <vector>

class SceneController : public Singleton<SceneController> {
public:
	void Init(SceneID id);

	void Update();

	void Draw();

	void ChanegeScene(SceneID id);

	void Release();
private:
	std::vector<SceneBase*> m_scene_list;
	SceneBase* m_curr_scene;
	SceneID m_scene_id;
private:
	friend Singleton<SceneController>;

	SceneController() 
	{ 
		m_scene_list.clear();
		m_curr_scene = nullptr;
		m_scene_id = SceneID::UNKNOWN;
	};
	virtual ~SceneController() {};

	SceneController(const SceneController&) = delete;
	SceneController& operator=(const SceneController&) = delete;
	SceneController(const SceneController&&) = delete;
	SceneController& operator=(const SceneController&&) = delete;

};