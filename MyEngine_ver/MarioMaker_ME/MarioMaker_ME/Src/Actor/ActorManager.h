#pragma once

#include "ActorBase.h"
#include "Block/Block.h"
#include "Character/Enemy/Enemy.h"
#include "Character/Player/Player.h"

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
		Init();
	}
	~ActorManager() //!< デストラクタ
	{
		Release();
	}

	void Init();	//!< 初期化
	void Update();	//!< 更新
	void Draw();	//!< 描画
	void Release();	//!< 解放

private:
	int* m_map[23][40];	//!< Csvの情報を読み込み用
	std::map<std::string, std::vector<ActorBase*>> m_actors;	//!< アクターの実体を管理
};