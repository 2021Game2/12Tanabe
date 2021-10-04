#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"

class CPlayer : public CRectangle {
public:
	bool mGameover;
	bool mGameclear;
	int mFx, mFy;
	//ƒWƒƒƒ“ƒv
	int mJump;
	int mVj;
	int FireCount;
	int mAniCnt;
	int mLife;
	int mMuteki;
	CPlayer();
	static CPlayer* spInstance;
	void Update();
	void Render();
	bool CPlayer::Collision(CRectangle& r);
	void Collision(CRectangle* i, CRectangle* y);
};

#endif
