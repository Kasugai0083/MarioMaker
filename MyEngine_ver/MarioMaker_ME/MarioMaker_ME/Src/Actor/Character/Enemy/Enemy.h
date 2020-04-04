#pragma once

#include "../../ActorBase.h"

/**
* @brief
* エネミーを制御するクラス
*/

enum class EnemyType
{
	KURIBO,
	NOKONOKO,
	BOOMMAN,
	ETC
};

class Enemy :
	public ActorBase
{
public:
	/**
	* @brief コンストラクタ\n引数の値に基づいて初期化する
	* @param pos_ 初期化する座標
	* @param fileName_ 設定する画像名
	*/
	Enemy(Pos2 pos_, std::map<std::string, std::string*> nameList_)
	{
		Accessor* acs = Accessor::GetInstance();
		if (!acs) { return; };
		m_camera_ptr = new Camera();
		m_camera_ptr = acs->GetCurrCameraPTR();

		m_name_list = nameList_;
		Init(pos_);
	};
	~Enemy() override;	//!< デストラクタ

	void Init(Pos2 pos_) override;	//!< 初期化
	void Update() override;									//!< 更新
	void Draw()override;	//!< 描画
	void Release() override;								//!< 解放

private:
	EnemyType m_type;
};

