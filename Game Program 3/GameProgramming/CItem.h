#ifndef CITEM_H
#define CITEM_H
#include"CRectangle.h"


class CItem : public CRectangle {
public:
	int mFx;
	int mFy;
	CItem();
	bool Collision(CRectangle& r);
	void Collision(CRectangle* i, CRectangle* y);
	void Update();
	void Render();
};


#endif
