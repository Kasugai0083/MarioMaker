#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Drawer2D.h"


/**
* @brief
* ゲームメインのシーン処理
*/

class GameScene : public SceneBase
{
public:
	//!< コンストラクタ
	GameScene() {};
	~GameScene()override;		//!< デストラクタ
private:
	void Init()override;		//!< シーンの初期化
	void Update()override;		//!< シーンの更新
	SceneID End()override;		//!< シーンの解放
	SceneID Control()override;	//!< シーンの制御
	void Draw()override;		//!< シーンの描画
private:
	Drawer2D m_drawer2d;			//!< フォント表示に使用
};

