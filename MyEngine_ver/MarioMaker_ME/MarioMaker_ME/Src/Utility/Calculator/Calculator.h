#pragma once

#include "..//Vec2.h"
#include "../../Actor/ActorBase.h"

/**
* @brief
* 計算するクラス\n
* Collisionクラスの方が良かったかな？
*/

// 試験実装 四分割処理 start
enum class ForceHit 
{
	UPPER_SIDE,
	RIGHT_SIDE,
	LEFT_SIDE,
	DOWN_SIDE,
	NONE
};
// 試験実装 四分割処理 end

enum class PowKind {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	NONE
};

struct t_Rect
{
	float top;
	float bottom;
	float right;
	float left;
};

class Calculator
{
public:
	/**
	* 四分割
	*/
	static ForceHit ForceRectCollision(t_ASta obj1_, t_ASta obj2_);
public:
	/**
	* 新しい処理
	*/
	static bool UpSideCollision(t_ASta actor1_, t_ASta actor2_);
	static bool LeftSideCollision(t_ASta actor1_, t_ASta actor2_);
	static bool RightSideCollision(t_ASta actor1_, t_ASta actor2_);
	static bool UnderSideCollision(t_ASta actor1_, t_ASta actor2_);

public:
	/**
	* 古い処理
	*/

	/**
	* @brief obj1_ が obj2_ の上辺にいるときの判定関数
	* @param obj1_ 比較対象(こちらが主体)
	* @param obj2_ 比較対象(こちらが客体)
	* @return obj1_ が obj2_の上のセルにいる時 => true
	*/
	static bool RectCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);

	static PowKind SerchUpDown(Pos2 obj1_, Pos2 obj2_, float chipSize_, t_Vec2 vec_);
	static PowKind SerchRightLeft(Pos2 obj1_, Pos2 obj2_, float chipSize_, t_Vec2 vec_);

private:
	static float x, y;
};
