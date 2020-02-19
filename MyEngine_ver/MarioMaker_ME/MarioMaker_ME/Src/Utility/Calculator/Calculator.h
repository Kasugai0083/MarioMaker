#pragma once

#include "..//Vec2.h"
#include "../../Actor/ActorBase.h"

/**
* @brief
* �v�Z����N���X\n
* Collision�N���X�̕����ǂ��������ȁH
*/

// �������� �l�������� start
enum class ForceHit 
{
	UPPER_SIDE,
	RIGHT_SIDE,
	LEFT_SIDE,
	DOWN_SIDE,
	NONE
};
// �������� �l�������� end

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
	* �l����
	*/
	static ForceHit ForceRectCollision(t_ASta obj1_, t_ASta obj2_);
public:
	/**
	* �V��������
	*/
	static bool UpSideCollision(t_ASta actor1_, t_ASta actor2_);
	static bool LeftSideCollision(t_ASta actor1_, t_ASta actor2_);
	static bool RightSideCollision(t_ASta actor1_, t_ASta actor2_);
	static bool UnderSideCollision(t_ASta actor1_, t_ASta actor2_);

public:
	/**
	* �Â�����
	*/

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
