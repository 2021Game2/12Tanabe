#ifndef CKEYITEM_H
#define CKEYITEM_H
#include"CRectangle.h"


class CKeyItem : public CRectangle {
public:
	int mFx;
	int mFy;
	CKeyItem();
	bool Collision(CRectangle& r);
	void Collision(CRectangle* i, CRectangle* y);
	void Update();
	void Render();
};


#endif
