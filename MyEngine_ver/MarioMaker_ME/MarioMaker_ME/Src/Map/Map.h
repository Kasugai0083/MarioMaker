#pragma once

#include "../Engine/Graphics/Drawer2D.h"
#include "..//Data/GameData.h"
#include "../Actor/ActorManager.h"
#include "../Camera/Camera.h"

#include <vector>

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

	void Init();	//!< 初期化
	void Update();	//!< 更新
	void Draw();	//!< 描画
	void Release();	//!< 解放

private:
	float m_gravity;			//!< マップの重力
	ActorManager m_actor_mgr;	//!< アクターを管理
	Camera m_map_camera;
};

