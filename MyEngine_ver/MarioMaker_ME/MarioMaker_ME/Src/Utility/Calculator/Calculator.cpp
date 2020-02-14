#include "Calculator.h"
#include "..//..//Engine/Device.h"

bool Calculator::UpSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_)
{
	if(
		obj1_.y >= obj2_.y - chipSize_		
		&& obj1_.y <= obj2_.y
		&& obj1_.x >= obj2_.x
		&& obj1_.x <= obj2_.x + chipSize_
		)
	{
		return true;
	}
	return false;
}

bool Calculator::LeftSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_)
{
	if (
		Device::KeyOn('D')
		&& obj1_.y >= obj2_.y
		&& obj1_.y <= obj2_.y + chipSize_
		&& obj1_.x + chipSize_ >= obj2_.x
		&& obj1_.x + chipSize_ <= obj2_.x + chipSize_
		)
	{
		return true;
	}
	return false;
}

bool Calculator::RightSideCollision(Pos2 obj1_, Pos2 obj2_, float chipSize_)
{
	if (
		Device::KeyOn('A')
		&& obj1_.y >= obj2_.y
		&& obj1_.y <= obj2_.y + chipSize_
		&& obj1_.x >= obj2_.x
		&& obj1_.x <= obj2_.x + chipSize_
		)
	{
		return true;
	}
	return false;
}
