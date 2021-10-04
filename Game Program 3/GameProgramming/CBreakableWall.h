#ifndef CBREAKABLEWALL_H
#define CBREAKABLEWALL_H

#include"CRectangle.h"

class CBreakableWall : public CRectangle {
public:
	int mFx;
	int mFy;
	CBreakableWall();
	void Updata();
	void Render();
};

#endif

