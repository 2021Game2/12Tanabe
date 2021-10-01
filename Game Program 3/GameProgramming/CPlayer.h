#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"

class CPlayer : public CRectangle {
public:
	int mFx, mFy;
	int FireCount;
	int mJump;
	int mVj;
	CPlayer();
	void Update();
	void Render();

	void Collision(CRectangle *i, CRectangle *y);
};

#endif
