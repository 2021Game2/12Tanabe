#ifndef CSEARCH_H
#define CSEARCH_H

#include "CRectangle.h"
#include <stdio.h>
#include "glut.h"
#include <string.h>

class CSearch : public CRectangle {
public:
	int mFx;
	int mFy;
	int mCount;
	CSearch();
	void Collision(CRectangle* i, CRectangle* y);
	void Update();//XVˆ—
	void Render();//•`‰æˆ—
};

#endif

