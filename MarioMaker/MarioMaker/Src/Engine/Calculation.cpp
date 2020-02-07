#include "../Utility/Vec.h"
#include "../Texture/Texture.h"
#include "Calculation.h"
#include "..//Engine/Input.h"
#include <math.h>

Texture* g_pWallTex;
Texture* g_pPlayerTex;

Position GetPosition(float x_, float y_) {
	Position PositionTmp;	

	PositionTmp.m_X = x_;
	PositionTmp.m_Y = y_;

	return PositionTmp;
}

float GetImageRatio(float a_, float b_) {
	return (a_ / b_);
}

//2048まで対応
float GetIntegratedImageRatio(float a_, float b_) {

	a_ *= b_;

	if (a_ > 1024 && a_ <= 2048) {
		return (a_ / 2048.0f) / b_;
	}
	else if (a_ > 512 && a_ <= 1024) {
		return (a_ / 1024) / b_;
	}
	else if (a_ > 256 && a_ <= 512) {
		return (a_ / 512) / b_;
	}
	else if (a_ > 128 && a_ <= 256) {
		return (a_ / 256) / b_;
	}
	else if (a_ > 64 && a_ <= 128) {
		return (a_ / 128) / b_;
	}
	else if (a_ > 32 && a_ <= 64) {
		return (a_ / 64) / b_;
	}
	else if (a_ > 16 && a_ <= 32) {
		return (a_ / 32) / b_;
	}
	else if (a_ > 8 && a_ <= 16) {
		return (a_ / 16) / b_;
	}
	else if (a_ > 4 && a_ <= 8) {
		return (a_ / 8) / b_;
	}
	else if (a_ > 2 && a_ <= 4) {
		return (a_ / 4) / b_;
	}
}

//二点間のラジアンを計算
double GetRadian(double startX_, double startY_, double endX_, double endY_) {

	//double radian = atan2(startY - endY, startX - endX);
	double radian = atan2(endY_ - startY_, endX_ - startX_);

	return radian;

}

//ラジアンを度数に変換
double GetDegree(double rad_) {

	double degree = rad_ * 180 / PI;

	return degree;

}

float GetVecLong(float x_, float y_) {

	float VecLong = sqrt(pow(x_, 2) + pow(y_, 2));

	return VecLong;
}



bool HasRectangleHit(Texture* texture_data_, float x1_, float x2_, float y1_, float y2_) {

	if (x1_ >= x2_ && x1_ <= x2_ + texture_data_->Width) {
		if (y1_ >= y2_ && y1_ <= y2_ + texture_data_->Height) {
			return true;
		}
	}

	return false;

}

bool HasRectangleHit(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_) {

	if (x1_ >= x2_  && x1_ <= x3_) {
		if (y1_ >= y2_ && y1_ <= y3_)  {
			return true;
		}
	}

	return false;

}

bool HasAdvRectangleHit(float x1_, float x2_, float y1_, float y2_, float wide1_, float wide2_, float height1_, float height2_) {

	float fCenterX1 = x1_ + (wide1_ / 2);
	float fCenterY1 = y1_ + (height1_ / 2);
	float fCenterX2 = x2_ + (wide2_ / 2);
	float fCenterY2 = y2_ + (height2_ / 2);

	if (fabsf(fCenterX1 - fCenterX2) < ((wide1_ / 2)) + (wide2_ / 2)) {
		if (fabsf(fCenterY1 - fCenterY2 ) < ((height1_ / 2)) + (height2_ / 2) ) {
			return true;
		}
	}

	return false;

}


