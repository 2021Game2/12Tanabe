#ifndef CKEYENEMY_H
#define CKEYENEMY_H

#include "CRectangle.h"
#include "CBullet.h"



class CKeyEnemy : public CRectangle {
public:
	int mFx; //X�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:�E�ֈړ�
	int mFy; //Y�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:��ֈړ�
	int mFireCount;
	int mAniCnt;
	int mEKLife;
	CKeyEnemy();
	void Update();
	bool Collision(CRectangle &r);
	void Render();
	void Collision(CRectangle *i, CRectangle *y);
};

#endif