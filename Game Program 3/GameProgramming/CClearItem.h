#ifndef CCLEARITEM_H
#define CCLEARITEM_H
#include"CRectangle.h"


class CClearItem : public CRectangle {
public:
	int mFx;
	int mFy;
	CClearItem();
	bool Collision(CRectangle& r);
	void Collision(CRectangle* i, CRectangle* y);
	void Update();
	void Render();
};


#endif
