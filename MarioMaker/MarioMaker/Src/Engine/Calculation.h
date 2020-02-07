#ifndef CALCULATION_H_
#define CALCULATION_H_

#include "../Texture/Texture.h"

struct Position {
	float m_X;
	float m_Y;
};

Position GetPosition(float x_, float y_);

#define PI 3.141592

//画像の比率を算出する
//a => 描画する画像サイズ
//b => 全体の画像サイズ
float GetImageRatio(float a_, float b_);
//統合画像の比率を算出する
//a => 描画する画像サイズ
//b => 統合画像の枚数
float GetIntegratedImageRatio(float a_, float b_);

//点と矩形の当たり判定
//X1, Y1 => GetMousPos()など利用
//X2 - X3 => 矩形の範囲を指定(横)
//Y2 - Y3 => 矩形の範囲を指定(縦)
bool HasRectangleHit(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_);
//画像サイズをtexture_dataからとる場合、座標の指定だけでOK
bool HasRectangleHit(Texture* textureData_, float x1_, float x2_, float y1_, float y2_);

//二点間のラジアンを計算
double GetRadian(double startX_, double startY_, double endX_, double endY_);
//ラジアンを度数法に変換する
double GetDegree(double rad_);

//矩形と矩形の当たり判定
//X1, Y1 => 1つ目の座標を指定
//wide1, hight1 => 1つ目の矩形のサイズを指定
//X2, Y2 => ２つ目の座標を指定
//wide2, hight2 => ２つ目の矩形のサイズを指定
bool HasAdvRectangleHit(float x1_, float x2_, float y1_, float y2_, float wide1_, float wide2_, float height1_, float height2_);

#endif