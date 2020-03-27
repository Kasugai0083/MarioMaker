#pragma once

#include "../Engine/Graphics/Drawer2D.h"
#include "..//Data/GameData.h"
#include "../Actor/ActorManager.h"
#include "../Camera/Camera.h"

#include <vector>
#include <string>

/**
* @brief
* マップと登場するアクターを制御するクラス
*/



class MapManager
{
public:
	MapManager() 	//!< コンストラクタ
	{
	};
	~MapManager();	//!< デストラクタ

	void Init(std::string name_);	//!< 初期化
	void Update();	//!< 更新
	void Draw();	//!< 描画
	void Release();	//!< 解放

	bool GetHasClear() { return m_has_clear; }
private:
	std::string m_map_name;		//!< マップの名前
	float m_gravity;			//!< マップの重力
	ActorManager m_actor_mgr;	//!< アクターを管理
	Camera m_map_camera;		//!< マップのカメラ情報
	bool m_has_clear;			//!< マップのクリア情報
};

