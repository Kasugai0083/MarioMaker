#include "Calculator.h"
#include "..//..//Engine/Device.h"

// ��Â���������@�𐄏�

/**
* �l����
*/
ForceHit Calculator::ForceRectCollision(t_ASta obj1_, t_ASta obj2_)
{
	/**
	* Object1
	*/
	Pos2 obj1_half;
	obj1_half.x = (obj1_.size.width / 2.f);
	obj1_half.y = (obj1_.size.height / 2.f);
	
	Pos2 obj1_center;
	obj1_center.x = obj1_.pos.x + obj1_half.x;
	obj1_center.y = obj1_.pos.y + obj1_half.y;

	Pos2 obj1_top;
	obj1_top.x = obj1_center.x;
	obj1_top.y = obj1_center.y - obj1_half.y;

	Pos2 obj1_bot;
	obj1_bot.x = obj1_center.x;
	obj1_bot.y = obj1_center.y + obj1_half.y;

	Pos2 obj1_left;
	obj1_bot.x = obj1_center.x - obj1_half.x;
	obj1_bot.y = obj1_center.y;

	Pos2 obj1_right;
	obj1_bot.x = obj1_center.x + obj1_half.x;
	obj1_bot.y = obj1_center.y;

	/**
	* Object2
	*/
	Pos2 obj2_half;
	obj2_half.x = (obj1_.size.width / 2.f);
	obj2_half.y = (obj1_.size.height / 2.f);

	Pos2 obj2_center;
	obj2_center.x = obj2_.pos.x + obj2_half.x;
	obj2_center.y = obj2_.pos.y + obj2_half.y;

	Pos2 obj2_top;
	obj2_top.x = obj2_center.x;
	obj2_top.y = obj2_center.y - obj2_half.y;

	Pos2 obj2_bot;
	obj2_bot.x = obj2_center.x;
	obj2_bot.y = obj2_center.y + obj2_half.y;

	Pos2 obj2_left;
	obj2_bot.x = obj2_center.x - obj2_half.x;
	obj2_bot.y = obj2_center.y;

	Pos2 obj2_right;
	obj2_bot.x = obj2_center.x + obj2_half.x;
	obj2_bot.y = obj2_center.y;
	
	if (obj1_.curr_vec.y >= 16) { obj1_.curr_vec.y = 15; }
	if (
		obj1_.curr_vec.y > 0
		&& obj1_center.x >= obj2_left.x
		&& obj1_center.x <= obj2_right.x
		&& obj1_center.y >= obj2_top.y
		&& obj1_center.y <= obj2_center.y
		)
	{

		return ForceHit::UPPER_SIDE;

	}
	return ForceHit::NONE;
}

/**
* �V��������
*/
bool Calculator::UpSideCollision(t_ASta actor1_, t_ASta actor2_)
{
#pragma region Actor1
	Pos2 actor1_center;
	actor1_center.x = actor1_.pos.x + (actor1_.size.width / 2);
	actor1_center.y = actor1_.pos.y + (actor1_.size.height / 2);

	Pos2 actor1_bottom;
	actor1_bottom.x = actor1_center.x;
	actor1_bottom.y = actor1_center.y + (actor1_.size.height / 2);

	Pos2 actor1_top;
	actor1_top.x = actor1_center.x;
	actor1_top.y = actor1_center.y - (actor1_.size.height / 2);

	Pos2 actor1_left;
	actor1_left.x = actor1_center.x - (actor1_.size.width / 2);
	actor1_left.y = actor1_center.y;

	Pos2 actor1_right;
	actor1_right.x = actor1_center.x + (actor1_.size.width / 2);
	actor1_right.y = actor1_center.y;
#pragma endregion

#pragma region Actor2 
	Pos2 actor2_center;
	actor2_center.x = actor2_.pos.x + (actor2_.size.width / 2);
	actor2_center.y = actor2_.pos.y + (actor2_.size.height / 2);

	Pos2 actor2_bottom;
	actor2_bottom.x = actor2_center.x;
	actor2_bottom.y = actor2_center.y + (actor2_.size.height / 2);

	Pos2 actor2_top;
	actor2_top.x = actor2_center.x;
	actor2_top.y = actor2_center.y - (actor2_.size.height / 2);

	Pos2 actor2_left;
	actor2_left.x = actor2_center.x - (actor2_.size.width / 2);
	actor2_left.y = actor2_center.y;

	Pos2 actor2_right;
	actor2_right.x = actor2_center.x + (actor2_.size.width / 2);
	actor2_right.y = actor2_center.y;
#pragma endregion

	if (
		actor1_bottom.y >= actor2_top.y
		&& actor1_bottom.y <= actor2_bottom.y
		&& actor1_right.x > actor2_left.x
		&& actor1_left.x < actor2_right.x
		)
	{
		return true;
	}
	return false;
}

bool Calculator::LeftSideCollision(t_ASta actor1_, t_ASta actor2_)
{
#pragma region Actor1
	Pos2 actor1_center;
	actor1_center.x = actor1_.pos.x + (actor1_.size.width / 2);
	actor1_center.y = actor1_.pos.y + (actor1_.size.height / 2);

	Pos2 actor1_bottom;
	actor1_bottom.x = actor1_center.x;
	actor1_bottom.y = actor1_center.y + (actor1_.size.height / 2);

	Pos2 actor1_top;
	actor1_top.x = actor1_center.x;
	actor1_top.y = actor1_center.y - (actor1_.size.height / 2);

	Pos2 actor1_left;
	actor1_left.x = actor1_center.x - (actor1_.size.width / 2);
	actor1_left.y = actor1_center.y;

	Pos2 actor1_right;
	actor1_right.x = actor1_center.x + (actor1_.size.width / 2);
	actor1_right.y = actor1_center.y;
#pragma endregion

#pragma region Actor2 
	Pos2 actor2_center;
	actor2_center.x = actor2_.pos.x + (actor2_.size.width / 2);
	actor2_center.y = actor2_.pos.y + (actor2_.size.height / 2);

	Pos2 actor2_bottom;
	actor2_bottom.x = actor2_center.x;
	actor2_bottom.y = actor2_center.y + (actor2_.size.height / 2);

	Pos2 actor2_top;
	actor2_top.x = actor2_center.x;
	actor2_top.y = actor2_center.y - (actor2_.size.height / 2);

	Pos2 actor2_left;
	actor2_left.x = actor2_center.x - (actor2_.size.width / 2);
	actor2_left.y = actor2_center.y;

	Pos2 actor2_right;
	actor2_right.x = actor2_center.x + (actor2_.size.width / 2);
	actor2_right.y = actor2_center.y;
#pragma endregion
	if (
		actor1_top.y >= actor2_top.y
		&& actor1_bottom.y <= actor2_bottom.y
		&& actor1_right.x >= actor2_left.x
		&& actor1_right.x <= actor2_right.x
		)
	{
		return true;
	}
	return false;
}

bool Calculator::RightSideCollision(t_ASta actor1_, t_ASta actor2_)
{
#pragma region Actor1
	Pos2 actor1_center;
	actor1_center.x = actor1_.pos.x + (actor1_.size.width / 2);
	actor1_center.y = actor1_.pos.y + (actor1_.size.height / 2);

	Pos2 actor1_bottom;
	actor1_bottom.x = actor1_center.x;
	actor1_bottom.y = actor1_center.y + (actor1_.size.height / 2);

	Pos2 actor1_top;
	actor1_top.x = actor1_center.x;
	actor1_top.y = actor1_center.y - (actor1_.size.height / 2);

	Pos2 actor1_left;
	actor1_left.x = actor1_center.x - (actor1_.size.width / 2);
	actor1_left.y = actor1_center.y;

	Pos2 actor1_right;
	actor1_right.x = actor1_center.x + (actor1_.size.width / 2);
	actor1_right.y = actor1_center.y;
#pragma endregion

#pragma region Actor2 
	Pos2 actor2_center;
	actor2_center.x = actor2_.pos.x + (actor2_.size.width / 2);
	actor2_center.y = actor2_.pos.y + (actor2_.size.height / 2);

	Pos2 actor2_bottom;
	actor2_bottom.x = actor2_center.x;
	actor2_bottom.y = actor2_center.y + (actor2_.size.height / 2);

	Pos2 actor2_top;
	actor2_top.x = actor2_center.x;
	actor2_top.y = actor2_center.y - (actor2_.size.height / 2);

	Pos2 actor2_left;
	actor2_left.x = actor2_center.x - (actor2_.size.width / 2);
	actor2_left.y = actor2_center.y;

	Pos2 actor2_right;
	actor2_right.x = actor2_center.x + (actor2_.size.width / 2);
	actor2_right.y = actor2_center.y;
#pragma endregion
	if (
		actor1_top.y >= actor2_top.y
		&& actor1_bottom.y <= actor2_bottom.y
		&& actor1_left.x >= actor2_left.x
		&& actor1_left.x <= actor2_right.x
		)
	{
		return true;
	}
	return false;
}

bool Calculator::UnderSideCollision(t_ASta actor1_, t_ASta actor2_)
{
#pragma region Actor1
	Pos2 actor1_center;
	actor1_center.x = actor1_.pos.x + (actor1_.size.width / 2);
	actor1_center.y = actor1_.pos.y + (actor1_.size.height / 2);

	Pos2 actor1_bottom;
	actor1_bottom.x = actor1_center.x;
	actor1_bottom.y = actor1_center.y + (actor1_.size.height / 2);

	Pos2 actor1_top;
	actor1_top.x = actor1_center.x;
	actor1_top.y = actor1_center.y - (actor1_.size.height / 2);

	Pos2 actor1_left;
	actor1_left.x = actor1_center.x - (actor1_.size.width / 2);
	actor1_left.y = actor1_center.y;

	Pos2 actor1_right;
	actor1_right.x = actor1_center.x + (actor1_.size.width / 2);
	actor1_right.y = actor1_center.y;
#pragma endregion

#pragma region Actor2 
	Pos2 actor2_center;
	actor2_center.x = actor2_.pos.x + (actor2_.size.width / 2);
	actor2_center.y = actor2_.pos.y + (actor2_.size.height / 2);

	Pos2 actor2_bottom;
	actor2_bottom.x = actor2_center.x;
	actor2_bottom.y = actor2_center.y + (actor2_.size.height / 2);

	Pos2 actor2_top;
	actor2_top.x = actor2_center.x;
	actor2_top.y = actor2_center.y - (actor2_.size.height / 2);

	Pos2 actor2_left;
	actor2_left.x = actor2_center.x - (actor2_.size.width / 2);
	actor2_left.y = actor2_center.y;

	Pos2 actor2_right;
	actor2_right.x = actor2_center.x + (actor2_.size.width / 2);
	actor2_right.y = actor2_center.y;
#pragma endregion
	if (
		actor1_top.y >= actor2_top.y
		&& actor1_top.y <= actor2_bottom.y
		&& actor1_right.x > actor2_left.x
		&& actor1_left.x < actor2_right.x
		)
	{
		return true;
	}
	return false;
}


/**
* �Â�����
*/
bool Calculator::RectCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_)
{
	Pos2 obj1_center;
	obj1_center.x = obj1_.x + (chipSize_ / 2.f);
	obj1_center.y = obj1_.y + (chipSize_ / 2.f);

	Pos2 obj2_center;
	obj2_center.x = obj2_.x + (chipSize_ / 2.f);
	obj2_center.y = obj2_.y + (chipSize_ / 2.f);

	if(
		obj1_center.y + (chipSize_ / 2.f) >= obj2_center.y - (chipSize_ / 2.f)
		&& obj1_center.y - (chipSize_ / 2.f) <= obj2_center.y + (chipSize_ / 2.f)
		&& obj1_center.x - (chipSize_ / 2.f) <= obj2_center.x + (chipSize_ / 2.f)
		&& obj1_center.x + (chipSize_ / 2.f) >= obj2_center.x - (chipSize_ / 2.f)
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
		//else if (vec_.x < 0)
		//{
		//	return PowKind::LEFT;
		//}
		//else if (vec_.x > 0)
		//{
		//	return PowKind::RIGHT;
		//}
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