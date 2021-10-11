#include "CBreakableWall.h"
#include"CTexture.h"
#include "CPlayer.h"

extern CTexture Texture;

CBreakableWall::CBreakableWall()
	:mFx(1.0f)
	, mFy(0.0f)
{
	mTag = EBREAKABLEWALL;
	w = 50;
	h = 50;

}

void CBreakableWall::Updata()
{

	if (mEnabled) {

	}

}

void CBreakableWall::Render()
{
	if (mEnabled) {

	}
}

