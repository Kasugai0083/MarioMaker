#ifndef CALCULATION_H_
#define CALCULATION_H_

#include "../Texture/Texture.h"

struct Position {
	float m_X;
	float m_Y;
};

Position GetPosition(float x_, float y_);

#define PI 3.141592

//�摜�̔䗦���Z�o����
//a => �`�悷��摜�T�C�Y
//b => �S�̂̉摜�T�C�Y
float GetImageRatio(float a_, float b_);
//�����摜�̔䗦���Z�o����
//a => �`�悷��摜�T�C�Y
//b => �����摜�̖���
float GetIntegratedImageRatio(float a_, float b_);

//�_�Ƌ�`�̓����蔻��
//X1, Y1 => GetMousPos()�ȂǗ��p
//X2 - X3 => ��`�͈̔͂��w��(��)
//Y2 - Y3 => ��`�͈̔͂��w��(�c)
bool HasRectangleHit(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_);
//�摜�T�C�Y��texture_data����Ƃ�ꍇ�A���W�̎w�肾����OK
bool HasRectangleHit(Texture* textureData_, float x1_, float x2_, float y1_, float y2_);

//��_�Ԃ̃��W�A�����v�Z
double GetRadian(double startX_, double startY_, double endX_, double endY_);
//���W�A����x���@�ɕϊ�����
double GetDegree(double rad_);

//��`�Ƌ�`�̓����蔻��
//X1, Y1 => 1�ڂ̍��W���w��
//wide1, hight1 => 1�ڂ̋�`�̃T�C�Y���w��
//X2, Y2 => �Q�ڂ̍��W���w��
//wide2, hight2 => �Q�ڂ̋�`�̃T�C�Y���w��
bool HasAdvRectangleHit(float x1_, float x2_, float y1_, float y2_, float wide1_, float wide2_, float height1_, float height2_);

#endif