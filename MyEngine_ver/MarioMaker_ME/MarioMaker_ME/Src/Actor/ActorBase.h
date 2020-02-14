#pragma once
#include "..//Utility/Vec2.h"
#include "..//Engine/Graphics/Drawer2D.h"

/**
* @brief 
* ゲームに登場する(プレイヤー・エネミー・ブロック)の基底クラス
*/

typedef struct t_ActorState {

	Pos2 pos;			//!< 座標
	float weight;		//!< 重さ
	float speed;		//!< 速度
	float jump_power;	//!< ジャンプ力
	float grav_accel;	//!< 重力加速度
	bool has_on_ground;		//!< ジャンプフラグ？
	t_Vec2 curr_vec;	//!< 現在のベクトル情報

}t_ASta;

class ActorBase
{
public:
	ActorBase() {};				//!< コンストラクタ
	virtual ~ActorBase() {};	//!< デストラクタ	

	virtual void Init(Pos2 pos_, std::string fileName_) = 0;	//!< 初期化
	virtual void Update() = 0;									//!< 更新
	virtual void Draw(std::string fileName_) = 0;				//!< 描画
	virtual void Release() = 0;									//!< 解放

	Pos2 GetPos() { return m_state.pos; }						//!< 座標取得
	void SetPos(Pos2 pos_) { m_state.pos = pos_; }				//!< 座標変更

	void SetGrvAccel(float gravity_) { m_state.grav_accel = gravity_; }	//!< 重力加速度変更
	float GetGrvAccel() { return m_state.grav_accel; }					//!< 重力加速度の取得

	void SetHasOnGround(bool has_) { m_state.has_on_ground = has_; }	//!< ジャンプフラグ変更
	float GetHasOnGround() { return m_state.has_on_ground; }			//!< ジャンプフラグの取得

protected:
	t_ActorState m_state;		//!< アクターのステータス
	Drawer2D m_drawer2d;		//!< 描画クラス		
};

