#pragma once

#include "..//Vec2.h"

/**
* @brief
* �v�Z����N���X\n
* Collision�N���X�̕����ǂ��������ȁH
*/

enum class PowKind {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	NONE
};

class Calculator
{
public:
	/**
	* @brief obj1_ �� obj2_ �̏�ӂɂ���Ƃ��̔���֐�
	* @param obj1_ ��r�Ώ�(�����炪���)
	* @param obj2_ ��r�Ώ�(�����炪�q��)
	* @return obj1_ �� obj2_�̏�̃Z���ɂ��鎞 => true
	*/
	static bool RectCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);

	static PowKind SerchUpDown(Pos2 obj1_, Pos2 obj2_, float chipSize_, t_Vec2 vec_);
	static PowKind SerchRightLeft(Pos2 obj1_, Pos2 obj2_, float chipSize_, t_Vec2 vec_);

private:
	static float x, y;
};

