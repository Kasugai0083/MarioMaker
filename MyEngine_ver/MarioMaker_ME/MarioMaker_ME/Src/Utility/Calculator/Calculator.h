#pragma once

#include "..//Vec2.h"
#include "../../Actor/ActorBase.h"

/**
* @brief
* ŒvŽZ‚·‚éƒNƒ‰ƒX\n
* CollisionƒNƒ‰ƒX‚Ì•û‚ª—Ç‚©‚Á‚½‚©‚ÈH
*/

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
	* V‚µ‚¢ˆ—
	*/
	static bool UpSideCollision(t_ASta actor1_, t_ASta actor2_);
	static bool LeftSideCollision(t_ASta actor1_, t_ASta actor2_);
	static bool RightSideCollision(t_ASta actor1_, t_ASta actor2_);
	static bool UnderSideCollision(t_ASta actor1_, t_ASta actor2_);


public:
	/**
	* ŒÃ‚¢ˆ—
	*/

	/**
	* @brief obj1_ ‚ª obj2_ ‚Ìã•Ó‚É‚¢‚é‚Æ‚«‚Ì”»’èŠÖ”
	* @param obj1_ ”äŠr‘ÎÛ(‚±‚¿‚ç‚ªŽå‘Ì)
	* @param obj2_ ”äŠr‘ÎÛ(‚±‚¿‚ç‚ª‹q‘Ì)
	* @return obj1_ ‚ª obj2_‚Ìã‚ÌƒZƒ‹‚É‚¢‚éŽž => true
	*/
	static bool RectCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);

	static PowKind SerchUpDown(Pos2 obj1_, Pos2 obj2_, float chipSize_, t_Vec2 vec_);
	static PowKind SerchRightLeft(Pos2 obj1_, Pos2 obj2_, float chipSize_, t_Vec2 vec_);

private:
	static float x, y;
};

