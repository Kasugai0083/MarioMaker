#pragma once

#include "..//Engine/Device.h"
#include "../Engine/Graphics/DirectX.h"
#include "SceneID.h"

/**
* @brief 
* シーンの基底クラス
*/

class SceneBase {
public:

	//!< コンストラクタ
	SceneBase()
	{
		m_state = SceneState::INIT;
		m_can_next_scene = false;
	}
	virtual ~SceneBase() {}	//!< デストラクタ

	virtual void Init() = 0; //!< 初期化処理

	virtual void Update() = 0; //!< 更新処理

	//!< 終了処理
	virtual SceneID End(){ return SceneID::UNKNOWN; }
	
	virtual void Draw() {}; //!< 描画処理

	/**
	* @brief 状態遷移処理
	* @return 次のシーンIDを返す
	*/
	virtual SceneID Control() { return SceneID::UNKNOWN; }

	void SwitchEnd() 
	{
		if (m_can_next_scene)
		{ 
			m_can_next_scene = false;
			m_state = SceneState::END;
		}
	}
protected:
	SceneState m_state;		//!< 現在のシーン状況を保管
	bool m_can_next_scene;	//!< 次のシーンに移るかどうか
};