#include "CAttack.h"

CAttack::CAttack()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = EATTACK;
	mEnabled = false;
	w = 10;	//幅設定
	h = 10;	//高さ設定
}

void CAttack::Update()
{
	if (mEnabled) {

	}
}

void CAttack::Render()
{
}
