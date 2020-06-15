#pragma once
#include "..//Utility/Vec2.h"
#include "..//Engine/Graphics/Drawer2D.h"
#include "../Data/GameData.h"
#include "../Camera/Camera.h"
#include "../Data/Accessor.h"
/**
* @brief 
* ゲームに登場する(プレイヤー・エネミー・ブロック)の基底クラス
*/

typedef struct t_ActorState {

	Pos2 pos;			//!< 座標
	Pos2 old_pos;		//!< 古い座標情報(計算用)
	t_Size size;		//!< サイズ
	float weight;		//!< 重さ
	float speed;			//!< 速度
	float jump_power;		//!< ジャンプ力
	float accel;			//!< 加速度
	float grav_accel;		//!< 重力加速度
	bool has_on_ground;	//!< 着地しているかどうか
	t_Vec2 curr_vec;	//!< 現在のベクトル情報
	bool is_death;		//!< 死亡判定(試験中)
	bool can_next_scene; //!< いづれかのアクターが true になれば次のシーンへ

}t_ASta;

class ActorBase
{
public:
	ActorBase() {};				//!< コンストラクタ
	virtual ~ActorBase() {};	//!< デストラクタ	

	virtual void Init(Pos2 pos_) = 0;	//!< 初期化
	virtual void Update() = 0;									//!< 更新
	virtual void Draw() = 0;				//!< 描画
	virtual void Release() = 0;									//!< 解放

	Pos2 GetPos() { return m_state.pos; }						//!< 座標取得
	void SetPos(Pos2 pos_) { m_state.pos = pos_; }				//!< 座標変更

	void SetAccel(float accel_) { m_state.accel = accel_; }	//!< 加速度変更

	void SetGrvAccel(float gravity_) { m_state.grav_accel = gravity_; }	//!< 重力加速度変更
	float GetGrvAccel() { return m_state.grav_accel; }					//!< 重力加速度の取得

	void SetHasOnGround(bool has_) { m_state.has_on_ground = has_; }	//!< ジャンプフラグ変更
	bool GetHasOnGround() { return m_state.has_on_ground; }			//!< ジャンプフラグの取得

	void SetCurrVec(t_Vec2 vec_)	//!< ベクトルの変更 
	{ 
		if (vec_.x != 0.f) { m_state.curr_vec.x = vec_.x; }
		if (vec_.y != 0.f) { m_state.curr_vec.y = vec_.y; }
	}

	void SetIsDeath(bool death_) { m_state.is_death = death_; }

	t_Vec2 GetCurrVec() { return m_state.curr_vec; }			//!< ジャンプフラグの取得

	t_ASta GetState() { return m_state; }			//!< ジャンプフラグの取得

protected:

	t_ActorState m_state;		//!< アクターのステータス
	Drawer2D m_drawer2d;		//!< 描画クラス		
	// 試験中
	std::map<std::string, std::string*> m_name_list;
	Camera* m_camera_ptr;

};

