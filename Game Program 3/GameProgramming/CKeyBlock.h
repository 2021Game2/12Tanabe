#ifndef CKEYBLOCK_H
#define CKEYBLOCK_H
#include"CRectangle.h"


class CKeyBlock : public CRectangle {
public:
	int mFx;
	int mFy;
	CKeyBlock();
	bool Collision(CRectangle& r);
	void Collision(CRectangle* i, CRectangle* y);
	void Update();
	void Render();
};


#endif