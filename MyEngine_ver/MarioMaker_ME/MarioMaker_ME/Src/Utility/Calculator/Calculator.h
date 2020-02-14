#pragma once

#include "..//Vec2.h"

/**
* @brief
* 計算するクラス\n
* Collisionクラスの方が良かったかな？
*/
class Calculator
{
public:
	/**
	* @brief obj1_ が obj2_ の上辺にいるときの判定関数
	* @param obj1_ 比較対象(こちらが主体)
	* @param obj2_ 比較対象(こちらが客体)
	* @return obj1_ が obj2_の上のセルにいる時 => true
	*/
	static bool UpSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);

	static bool LeftSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);

	static bool RightSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);
private:
	static float x, y;
};

