#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"



class CEnemy : public CRectangle {
public:
	int mFx; //X軸方向の移動 -1:左 0:移動しない 1:右へ移動
	int mFy; //Y軸方向の移動 -1:下 0:移動しない 1:上へ移動
	int mFireCount;
	int mAniCnt;
	CEnemy();
	void Update();
	bool Collision(CRectangle& r);
	void Render();
	void Collision(CRectangle* i, CRectangle* y);
};

#endif

