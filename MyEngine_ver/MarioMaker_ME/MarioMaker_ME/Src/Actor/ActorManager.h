#pragma once

#include "ActorBase.h"
#include "Block/Block.h"
#include "Goal/Goal.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Player.h"
#include "../Camera/Camera.h"

/**
* @brief
* ゲームシーンで登場する(プレイヤー・エネミー・ブロック)を\n
* 制御するクラス
*/
class ActorManager
{
public:
	ActorManager()	//!< コンストラクタ
	{
		m_camera_ptr = new Camera();
	}
	~ActorManager() //!< デストラクタ
	{
		Release();
	}

	void Init(std::string map_name_);	//!< 初期化
	void Update();	//!< 更新
	void Draw();	//!< 描画
	void Release();	//!< 解放

	void GetCameraPTR(Camera* camera_) { m_camera_ptr = camera_; } //!< カメラ情報を取得
	void GetClearPTR(bool* clear_) { m_clear_ptr = clear_; } //!< カメラ情報を取得
private:
	/**
	* 外部で使用しない関数群
	*/

	void PlayerAndBlockCollide();
	void PlayerAndGoalCollide();

private:
	int* m_map[MAX_MAP_H][MAX_MAP_W];	//!< Csvの情報を読み込み用
	std::map<std::string, std::vector<ActorBase*>> m_actors;	//!< アクターの実体を管理

	Camera* m_camera_ptr; //!< マップのカメラ情報を取得
	bool* m_clear_ptr;	  //!< マップのクリア情報を取得
};