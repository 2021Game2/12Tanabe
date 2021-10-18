#ifndef CDAMAGEBLOCK_H
#define CDAMAGEBLOCK_H
#include"CRectangle.h"


class CDamageBlock : public CRectangle{
public:
	int mFx;
	int mFy;
	CDamageBlock();
	bool Collision(CRectangle &r);
	void Collision(CRectangle *i, CRectangle *y);
	void Render();
};


#endif