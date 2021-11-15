#ifndef CSEARCHPOINT_H
#define CSEARCHPOINT_H
#include"CRectangle.h"

class CSearchPoint : public CRectangle {
public:
	int mFx;
	int mFy;
	CSearchPoint();
	void Collision(CRectangle* i, CRectangle* y);
	void Update();
	void Render();
};
#endif
