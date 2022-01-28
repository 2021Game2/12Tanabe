#include "CReStart.h"
#include "CTexture.h"
#include "CPlayer.h"

CTexture TextureReStart;
extern int Score;

CReStart::CReStart()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = ERESTART;
	w = 25;
	h = 25;

	if (TextureReStart.mId == 0) {
		TextureReStart.Load("ReStart.tga");
	}

}

void CReStart::Collision(CRectangle* i, CRectangle* y)
{

}

void CReStart::Update()
{

}

void CReStart::Render()
{

	if (mEnabled) {
		CRectangle::Render(TextureReStart, 0, 32, 32, 0);
	}
}
