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
	CAttack();
	void Update();
	void Render();
};
#endif

