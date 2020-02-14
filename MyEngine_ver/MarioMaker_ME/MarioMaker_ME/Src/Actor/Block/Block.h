#pragma once

#include "..//ActorBase.h"

/**
* @brief
* ブロックを制御するクラス
*/

class Block : public ActorBase
{
public:
	/**
	* @brief コンストラクタ\n引数の値に基づいて初期化する
	* @param pos_ 初期化する座標
	* @param fileName_ 設定する画像名
	*/
	Block(Pos2 pos_, std::string fileName_) 
	{
		Init(pos_,fileName_);
	};
	~Block() override;	//!< デストラクタ	

	void Init(Pos2 pos_, std::string fileName_)override;	//!< 初期化
	void Update()override;									//!< 更新
	void Draw(std::string fileName_)override;				//!< 描画
	void Release()override;									//!< 解放

private:

	float m_reaction; //!< @brief 反作用の力

};

