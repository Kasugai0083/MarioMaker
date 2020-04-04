#pragma once

#include "../../ActorBase.h"

/**
* @brief
* プレイヤーを制御するクラス
*/

class Player :
	public ActorBase
{
public:
	/**
	* @brief コンストラクタ\n引数の値に基づいて初期化する
	* @param pos_ 初期化する座標
	* @param fileName_ 設定する画像名
	*/
	Player(Pos2 pos_, std::map<std::string, std::string*> nameList_)
	{ 
		Accessor* acs = Accessor::GetInstance();
		if (!acs) { return; };
		m_camera_ptr = new Camera();
		m_camera_ptr = acs->GetCurrCameraPTR();

		m_name_list = nameList_;
		Init(pos_);
	};

	~Player() override;		//!< デストラクタ	

	void Init(Pos2 pos__) override;	//!< 初期化
	void Update() override;									//!< 更新
	void Draw() override;				//!< 描画
	void Release() override;								//!< 解放

private:	//!< クラス内関数
	/**
	* @brief 死亡時のアニメーション,シーン遷移に必要なパラメータを変更
	*/
	bool DeathAnimation();

private:
	int m_count;
	bool m_short_jump;

};

