#include "CSearchPoint.h"
#include "CTexture.h"
#include "CPlayer.h"

CTexture TextureSearchPoint;
extern int Score;

CSearchPoint::CSearchPoint()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = ESEARCHPOINT;
	w = 25;
	h = 25;

	if (TextureSearchPoint.mId == 0) {
		TextureSearchPoint.Load("SearchPoint.tga");
	}
}


void CSearchPoint::Update()
{
	if (!mEnabled) return;

	if (CPlayer::spInstance->mGameover) {
		Score = 0;
	}

	if (CPlayer::spInstance->mGameclear) {
		Score = 0;
	}

}

void CSearchPoint::Render()
{
	if (mEnabled) {
		CRectangle::Render(TextureSearchPoint, 64, 96, 32, 0);
	}

}
void CSearchPoint::Collision(CRectangle* i, CRectangle* y)
{
	if (i->mEnabled && y->mEnabled) {
		if (y->mTag == ESEARCH) {
			if (i->Collision(*y)) {
				Score += 200;
				mEnabled = false;
				return;
			}
		}
	}
}
