#pragma once

#include "../../ActorBase.h"

/**
* @brief
* エネミーを制御するクラス
*/

class Enemy :
	public ActorBase
{
public:
	/**
	* @brief コンストラクタ\n引数の値に基づいて初期化する
	* @param pos_ 初期化する座標
	* @param fileName_ 設定する画像名
	*/
	Enemy(Pos2 pos_, std::string fileName_) { Init(pos_, fileName_); };
	~Enemy() override;	//!< デストラクタ

	void Init(Pos2 pos_, std::string fileName_) override;	//!< 初期化
	void Update() override;									//!< 更新
	void Draw(std::string fileName_, Camera* camera_)override;	//!< 描画
	void Release() override;								//!< 解放

private:

};

