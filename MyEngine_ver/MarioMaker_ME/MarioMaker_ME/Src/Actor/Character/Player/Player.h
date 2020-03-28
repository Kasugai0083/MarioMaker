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
		
		m_name_list = nameList_;
		Init(pos_);
		m_camera_ptr = new Camera();
		m_camera_ptr = acs->GetCurrCameraPTR();
	};
	//Player(Pos2 pos_, std::string fileName_) 
	//{ 
	//	Accessor* acs = Accessor::GetInstance();
	//	if (!acs) { return; };

	//	Init(pos_, fileName_);
	//	m_camera_ptr = new Camera();
	//	m_camera_ptr = acs->GetCurrCameraPTR();
	//};
	~Player() override;		//!< デストラクタ	

	void Init(Pos2 pos__) override;	//!< 初期化
	void Init(Pos2 pos_, std::string fileName_) override;	//!< 初期化
	void Update() override;									//!< 更新
	void Draw() override;				//!< 描画
	void Draw(std::string fileName_, Camera* camera_) override;				//!< 描画
	void Release() override;								//!< 解放

private:
	int m_count;
	bool m_short_jump;

	Camera* m_camera_ptr;

	// 試験中
	std::map<std::string, std::string*> m_name_list;
};

