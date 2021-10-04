#include "CAttack.h"

CAttack::CAttack()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = EATTACK;
	mEnabled = false;
	w = 10;	//•İ’è
	h = 10;	//‚‚³İ’è
}

void CAttack::Update()
{
	if (mEnabled) {

	}
}

void CAttack::Render()
{
}
