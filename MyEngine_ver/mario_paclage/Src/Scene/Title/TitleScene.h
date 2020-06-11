#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Drawer2D.h"


/**
* @brief
* タイトルシーンの処理
*/

class TitleScene :public SceneBase
{
public:
	TitleScene();			//!< コンストラクタ
	~TitleScene()override;	//!< デストラクタ

private:
	void Init()override;	//!< シーンの初期化
	void Update()override;	//!< シーンの更新
	SceneID End()override;	//!< シーンの解放
	SceneID Control();		//!< シーンの制御
	void Draw()override;	//!< シーンの描画
private:

	Drawer2D m_drawer2d;		//!< フォント表示に使用
};

