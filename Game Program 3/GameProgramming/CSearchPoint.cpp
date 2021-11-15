#include "CSearchPoint.h"
#include "CTexture.h"

CTexture TextureSearchPoint;

CSearchPoint::CSearchPoint()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = ESEARCHPOINT;
	w = 50;
	h = 50;
}


void CSearchPoint::Update()
{

}

void CSearchPoint::Render()
{

}
void CSearchPoint::Collision(CRectangle* i, CRectangle* y)
{
	if (i->mEnabled && y->mEnabled) {
		if (y->mTag == ESEARCH) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
	}
}
