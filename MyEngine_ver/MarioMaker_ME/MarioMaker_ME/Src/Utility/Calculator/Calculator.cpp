#include "Calculator.h"
#include "..//..//Engine/Device.h"

// ˆê‚Â‚Ã‚Â”»’è‚ðŽæ‚é•û–@‚ð„§

bool Calculator::RectCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_)
{
	Pos2 obj1_center;
	obj1_center.x = obj1_.x / 2.f;
	obj1_center.y = obj1_.y / 2.f;

	Pos2 obj2_center;
	obj2_center.x = obj2_.x / 2.f;
	obj2_center.y = obj2_.y / 2.f;

	if(
		obj1_center.y >= obj2_center.y - (chipSize_ / 2.f)
		&& obj1_center.y <= obj2_center.y + (chipSize_ / 2.f)
		&& obj1_center.x <= obj2_center.x + (chipSize_ / 2.f)
		&& obj1_center.x >= obj2_center.x - (chipSize_ / 2.f)
		)
	{

		return true;
		
	}
	return false;
}

PowKind Calculator::SerchUpDown(Pos2 obj1_, Pos2 obj2_, float chipSize_, t_Vec2 vec_)
{
	if(RectCollision(obj1_, obj2_, chipSize_))
	{
		if (vec_.y < 0)
		{
			return PowKind::UP;
		}
		else if (vec_.y > 0)
		{
			return PowKind::DOWN;
		}
	}
	return PowKind::NONE;
}

PowKind Calculator::SerchRightLeft(Pos2 obj1_, Pos2 obj2_, float chipSize_, t_Vec2 vec_)
{
	if(RectCollision(obj1_, obj2_, chipSize_))
	{
		if (vec_.x < 0)
		{
			return PowKind::LEFT;
		}
		else if (vec_.x > 0)
		{
			return PowKind::RIGHT;
		}
	}
	return PowKind::NONE;
}