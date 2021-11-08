#ifndef CATTACK_H
#define CATTACK_H

#include "CRectangle.h"
#include <stdio.h>
#include "glut.h"
#include <string.h>

class CAttack : public CRectangle {
public:
	int mFx;
	int mFy;
	int mCount;
	CAttack();
	void Collision(CRectangle* i, CRectangle* y);
	void Update();
	void Render();
};
#endif

