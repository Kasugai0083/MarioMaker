#pragma once

#include "..//Vec2.h"

/**
* @brief
* �v�Z����N���X\n
* Collision�N���X�̕����ǂ��������ȁH
*/
class Calculator
{
public:
	/**
	* @brief obj1_ �� obj2_ �̏�ӂɂ���Ƃ��̔���֐�
	* @param obj1_ ��r�Ώ�(�����炪���)
	* @param obj2_ ��r�Ώ�(�����炪�q��)
	* @return obj1_ �� obj2_�̏�̃Z���ɂ��鎞 => true
	*/
	static bool UpSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);

	static bool LeftSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);

	static bool RightSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_);
private:
	static float x, y;
};

