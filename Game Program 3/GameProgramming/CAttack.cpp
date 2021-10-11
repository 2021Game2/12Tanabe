#include "CAttack.h"
#include "CPlayer.h"

extern CTexture Texture;

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
	if (mEnabled) {

	}
}

void CAttack::Collision(CRectangle* i, CRectangle* y)
{
	if (i->mEnabled && y->mEnabled) {
		if (y->mTag == EBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		if (i->mTag == EATTACK && y->mTag == EENEMY) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EATTACK && y->mTag == EBREAKABLEWALL) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
	}
}