﻿#include "Common.h"
#include <Windows.h>


//=========================================
// 2次元ヘルパー群
//=========================================
Mastumoto::t_Float2::t_Float2(float x_, float y_) {

	this->x = x_;
	this->y = y_;
}

Mastumoto::t_Float2 Mastumoto::t_Float2:: operator + (const t_Float2& r) {
	return { x + r.x,y + r.y };
}

Mastumoto::t_Float2 Mastumoto::t_Float2::operator - (const t_Float2& r) {
	return { x - r.x, y - r.y };
}

Mastumoto::t_Float2 Mastumoto::t_Float2::operator * (const t_Float2& r) {
	return { x*r.x, y*r.y };
}

Mastumoto::t_Float2 Mastumoto::t_Float2::operator * (float r)const {
	return { x*r, y*r };
}

Mastumoto::t_Float2 Mastumoto::t_Float2::operator / (const t_Float2& r) {
	return { x / r.x, y / r.y };
}

Mastumoto::t_Float2 Mastumoto::t_Float2::operator / (float r) const {
	return { x / r, y / r };
}


//=========================================
// ベクトルクラス
//=========================================
Mastumoto::Vec2 Mastumoto::Vec2::operator = (const t_Float2& r) {
	x = r.x;
	y = r.y;
	return { x, y };
}

float Mastumoto::Vec2::Cross(Vec2 v1, Vec2 v2, Vec2 point) {

	//線分を作る
	Vec2 vec1 = { (v1.x - v2.x),(v1.y - v2.y) };
	Vec2 vec2 = { (v1.x - point.x),(v1.y - point.y) };

	float ans = (vec1.x * vec2.y) - (vec2.x * vec1.y);
	return ans;
}