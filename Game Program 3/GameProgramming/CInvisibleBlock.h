#ifndef CINVISIBLEBLOCK_H
#define CINVISIBLEBLOCK_H
#include"CRectangle.h"


class CInvisibleBlock : public CRectangle {
public:
	int mFx;
	int mFy;
	CInvisibleBlock();
	void Render();
};


#endif
