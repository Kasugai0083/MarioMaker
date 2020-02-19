#pragma once

#include "../SceneBase.h"
#include "../../Engine/Graphics/Drawer2D.h"


/**
* @brief
* リザルトシーンの処理
*/

namespace {
	Pos3 pos1(20.f, 50.f, 0.f);
	Pos3 pos2(50.f, 0.f, 0.f);
}

class ResultScene :public SceneBase
{
public:
	//!< コンストラクタ
	ResultScene(){}
	~ResultScene()override;		//!< デストラクタ
private:
	void Init()override;		//!< シーンの初期化
	void Update()override;		//!< シーンの更新
	SceneID End()override;		//!< シーンの解放
	SceneID Control()override;	//!< シーンの制御
	void Draw()override;		//!< シーンの描画
private:
	Drawer2D m_drawer2d;			//!< フォント表示に使用
	

};

