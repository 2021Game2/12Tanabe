#ifndef CRESTART_H
#define CRESTART_H

#include "CRectangle.h"

class CReStart : public CRectangle {
public:
	int mFx;
	int mFy;
	int mCount;
	CReStart();
	void Collision(CRectangle* i, CRectangle* y);
	void Update();
	void Render();
};
#endif
