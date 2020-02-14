#pragma once

#include "..//Vec2.h"

/**
* @brief
* ŒvŽZ‚·‚éƒNƒ‰ƒX\n
* CollisionƒNƒ‰ƒX‚Ì•û‚ª—Ç‚©‚Á‚½‚©‚ÈH
*/
class Calculator
{
public:
	/**
	* @brief obj1_ ‚ª obj2_ ‚Ìã•Ó‚É‚¢‚é‚Æ‚«‚Ì”»’èŠÖ”
	* @param obj1_ ”äŠr‘ÎÛ(‚±‚¿‚ç‚ªŽå‘Ì)
	* @param obj2_ ”äŠr‘ÎÛ(‚±‚¿‚ç‚ª‹q‘Ì)
	* @return obj1_ ‚ª obj2_‚Ìã‚ÌƒZƒ‹‚É‚¢‚éŽž => true
	*/
	static bool UpSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);

	static bool LeftSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);

	static bool RightSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);
private:
	static float x, y;
};

